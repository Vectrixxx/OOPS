import cv2
import numpy as np
import mediapipe as mp
import time
from collections import deque
import math

# ==============================================================================
# DEFAULT CONFIGURATION & PARAMETERS
# ==============================================================================
# This section contains all the tuneable parameters from the spec.
# They are grouped for easy modification.

class Config:
    # Vision & Scoring Weights
    W_HEAD = 0.40
    W_GAZE = 0.35
    W_EYE = 0.15
    W_HAND = 0.10

    # Head Pose Thresholds
    MAX_YAW = 45.0  # degrees
    MAX_PITCH = 15.0  # degrees
    
    # Eye & Blink Thresholds
    EAR_CLOSED_TH = 0.20
    CLOSED_SECONDS_FOR_SLEEP = 2.0

    # Gaze Thresholds
    MAX_GAZE_OFFSET = 0.60  # Normalized offset

    # Hand Interaction Thresholds
    HAND_NEAR_FACE_DIST = 0.6  # normalized by face width
    HAND_NEAR_FACE_WINDOW = 3  # seconds
    HAND_DURATION_TH = 2  # seconds

    # Attention Score & Buffering
    FRAME_FOCUS_THRESHOLD = 0.60
    EMA_ALPHA = 0.30
    FPS = 15
    
    # 5-Minute Alert System
    ALERT_CHECK_INTERVAL = 300  # seconds (5 minutes)
    ALERT_THRESHOLD_PCT = 50.0  # %
    FACE_PRESENCE_MIN_PCT = 0.80  # %
    CONSECUTIVE_ALERT_WINDOWS_REQUIRED = 1

    # Visualization
    RED_BOX_DURATION = 30  # seconds after alert


# ==============================================================================
# DATA MODEL & TRACKING
# ==============================================================================

class PersonTrack:
    """Stores all per-person data, scores, and temporal buffers."""
    def __init__(self, person_id, last_seen_ts):
        self.person_id = person_id
        self.face_bbox = None
        self.last_seen_ts = last_seen_ts
        self.alert_flag = False
        self.alert_history = []
        self.alert_count = 0  # for consecutive alerts

        # Frame-level scores
        self.head_pose = {'yaw': 0.0, 'pitch': 0.0, 'roll': 0.0}
        self.eye_open_score = 0.0
        self.gaze_offset = {'x_norm': 0.0, 'y_norm': 0.0}
        self.hand_near_face_count = 0
        self.hand_near_face_duration = 0.0
        self.frame_attention = 0.0

        # Temporal buffers & smoothing
        self.ema_attention = 0.0
        self.last_alert_check = time.time()
        
        # Sliding windows (stores tuples of (timestamp, score, face_present))
        self.window_1s = deque(maxlen=int(Config.FPS * 1))
        self.window_30s = deque(maxlen=int(Config.FPS * 30))
        self.window_5m = deque(maxlen=int(Config.FPS * 300))

    def update_buffers(self, frame_attention, face_present, ts):
        """Appends current frame data to all sliding windows."""
        data = (ts, frame_attention, face_present)
        self.window_1s.append(data)
        self.window_30s.append(data)
        self.window_5m.append(data)

    def get_window_stats(self, window_name):
        """Computes stats for a given sliding window."""
        window = getattr(self, f'window_{window_name}')
        if not window:
            return {'avg_attention': 0.0, 'presence_pct': 0.0}

        total_frames = len(window)
        valid_attention_scores = [d[1] for d in window if d[2]]
        face_present_count = len([d for d in window if d[2]])

        avg_attention = sum(valid_attention_scores) / len(valid_attention_scores) if valid_attention_scores else 0.0
        presence_pct = face_present_count / total_frames

        return {'avg_attention': avg_attention, 'presence_pct': presence_pct}


# ==============================================================================
# CORE ATTENTION SCORING LOGIC
# ==============================================================================

class AttentionScorer:
    """Encapsulates the logic for calculating all sub-scores."""
    def __init__(self):
        # MediaPipe models
        self.mp_face_mesh = mp.solutions.face_mesh
        self.mp_hands = mp.solutions.hands
        self.face_mesh = self.mp_face_mesh.FaceMesh(
            static_image_mode=False,
            max_num_faces=1,
            refine_landmarks=True,
            min_detection_confidence=0.5,
            min_tracking_confidence=0.5
        )
        self.hands = self.mp_hands.Hands(
            static_image_mode=False,
            max_num_hands=2,
            min_detection_confidence=0.5,
            min_tracking_confidence=0.5
        )

        # 3D model points for solvePnP
        self.face_model_3d = np.array([
            (0.0, 0.0, 0.0),            # Nose tip
            (0.0, -330.0, -65.0),       # Chin
            (-225.0, 170.0, -135.0),    # Left eye corner
            (225.0, 170.0, -135.0),     # Right eye corner
            (-150.0, -150.0, -125.0),   # Left mouth corner
            (150.0, -150.0, -125.0)     # Right mouth corner
        ], dtype=np.float64)

        self.focal_length = 1.0
        self.cam_matrix = None
        self.dist_coeffs = np.zeros((4, 1))

    def _get_head_pose_score(self, landmarks, frame_size):
        """Calculates head pose (yaw, pitch, roll) and returns a score."""
        if not self.cam_matrix:
            h, w, _ = frame_size
            self.focal_length = w
            self.cam_matrix = np.array([
                [self.focal_length, 0, w / 2],
                [0, self.focal_length, h / 2],
                [0, 0, 1]
            ])

        # Extract 2D points from landmarks
        p_nose = landmarks[1]
        p_chin = landmarks[152]
        p_l_eye = landmarks[226]
        p_r_eye = landmarks[446]
        p_l_mouth = landmarks[78]
        p_r_mouth = landmarks[308]

        face_2d = np.array([
            (p_nose.x, p_nose.y),
            (p_chin.x, p_chin.y),
            (p_l_eye.x, p_l_eye.y),
            (p_r_eye.x, p_r_eye.y),
            (p_l_mouth.x, p_l_mouth.y),
            (p_r_mouth.x, p_r_mouth.y)
        ], dtype=np.float64)

        face_2d[:, 0] *= frame_size[1]
        face_2d[:, 1] *= frame_size[0]

        _, rot_vec, trans_vec = cv2.solvePnP(self.face_model_3d, face_2d, self.cam_matrix, self.dist_coeffs)
        rot_matrix, _ = cv2.Rodrigues(rot_vec)
        proj_matrix = np.hstack((rot_matrix, trans_vec))
        _, _, _, _, _, _, euler_angles = cv2.decomposeProjectionMatrix(proj_matrix)

        yaw, pitch, roll = euler_angles.flatten()
        
        # Clamp to 0..1 based on yaw/pitch
        score = 1 - np.clip(abs(yaw) / Config.MAX_YAW, 0, 1)
        
        return {'yaw': yaw, 'pitch': pitch, 'roll': roll}, score

    def _get_ear(self, eye_landmarks):
        """Calculates the Eye Aspect Ratio (EAR)."""
        p_2, p_3, p_5, p_6 = eye_landmarks[1], eye_landmarks[2], eye_landmarks[4], eye_landmarks[5]
        p_1, p_4 = eye_landmarks[0], eye_landmarks[3]
        
        A = np.linalg.norm(np.array([p_2.x, p_2.y]) - np.array([p_6.x, p_6.y]))
        B = np.linalg.norm(np.array([p_3.x, p_3.y]) - np.array([p_5.x, p_5.y]))
        C = np.linalg.norm(np.array([p_1.x, p_1.y]) - np.array([p_4.x, p_4.y]))
        
        ear = (A + B) / (2.0 * C)
        return ear

    def _get_ear_score(self, ear):
        """Maps EAR to an eye-open score."""
        if ear >= 0.25:
            return 1.0
        elif ear < Config.EAR_CLOSED_TH:
            return 0.0
        else:
            return (ear - Config.EAR_CLOSED_TH) / (0.25 - Config.EAR_CLOSED_TH)

    def _get_gaze_score(self, iris_landmarks, eye_landmarks, head_pose):
        """Calculates gaze offset and maps to a score, combining with head pose."""
        if not iris_landmarks or abs(head_pose['yaw']) > 15:
            return 1.0, {'x_norm': 0.0, 'y_norm': 0.0}

        # Left iris
        iris_l = iris_landmarks[0]
        eye_l_bbox = [
            min(p.x for p in eye_landmarks[:6]), min(p.y for p in eye_landmarks[:6]),
            max(p.x for p in eye_landmarks[:6]), max(p.y for p in eye_landmarks[:6])
        ]
        
        # Right iris
        iris_r = iris_landmarks[1]
        eye_r_bbox = [
            min(p.x for p in eye_landmarks[6:]), min(p.y for p in eye_landmarks[6:]),
            max(p.x for p in eye_landmarks[6:]), max(p.y for p in eye_landmarks[6:])
        ]

        x_rel_l = (iris_l.x - eye_l_bbox[0]) / (eye_l_bbox[2] - eye_l_bbox[0])
        x_norm_l = (x_rel_l - 0.5) * 2

        y_rel_l = (iris_l.y - eye_l_bbox[1]) / (eye_l_bbox[3] - eye_l_bbox[1])
        y_norm_l = (y_rel_l - 0.5) * 2
        
        gaze_magnitude = math.sqrt(x_norm_l**2 + y_norm_l**2) # using just one eye for simplicity
        
        score = np.clip(1 - (gaze_magnitude / Config.MAX_GAZE_OFFSET), 0, 1)
        
        return score, {'x_norm': x_norm_l, 'y_norm': y_norm_l}

    def _get_hand_score(self, person, hand_landmarks, frame_size):
        """Calculates hand proximity to face and returns a score."""
        face_center_x = person.face_bbox[0] + person.face_bbox[2] / 2
        face_center_y = person.face_bbox[1] + person.face_bbox[3] / 2
        face_width = person.face_bbox[2]

        is_hand_near = False
        if hand_landmarks:
            for hand_lm in hand_landmarks:
                hand_center_x = np.mean([lm.x for lm in hand_lm.landmark]) * frame_size[1]
                hand_center_y = np.mean([lm.y for lm in hand_lm.landmark]) * frame_size[0]
                dist_norm = np.linalg.norm(np.array([face_center_x, face_center_y]) - np.array([hand_center_x, hand_center_y])) / face_width
                if dist_norm < Config.HAND_NEAR_FACE_DIST:
                    is_hand_near = True
                    break

        # Update hand proximity duration
        if is_hand_near:
            person.hand_near_face_duration += 1.0 / Config.FPS
        else:
            person.hand_near_face_duration = max(0, person.hand_near_face_duration - 1.0 / Config.FPS)

        # Map duration to score
        score = 1.0 - np.clip(person.hand_near_face_duration / Config.HAND_DURATION_TH, 0, 1)
        return score


    def fuse_scores(self, head_score, gaze_score, eye_score, hand_score):
        """Combines all sub-scores into a single attention score."""
        return (Config.W_HEAD * head_score +
                Config.W_GAZE * gaze_score +
                Config.W_EYE * eye_score +
                Config.W_HAND * hand_score)


# ==============================================================================
# MAIN APPLICATION LOOP
# ==============================================================================

def main():
    """Main function to run the student engagement detection system."""
    cap = cv2.VideoCapture(0) # Using your Logitech camera at default index 0
    if not cap.isOpened():
        print("Error: Could not open video stream. Make sure camera is connected.")
        return

    scorer = AttentionScorer()
    persons = {}
    person_id_counter = 0
    last_alert_check = time.time()
    
    # 5-minute red box display timer per person
    red_box_timers = {}

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        frame = cv2.flip(frame, 1)
        h, w, _ = frame.shape
        ts = time.time()
        
        # Convert the BGR image to RGB
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        
        # Process with MediaPipe
        face_results = scorer.face_mesh.process(rgb_frame)
        hand_results = scorer.hands.process(rgb_frame)
        
        # ======================================================================
        # FACE TRACKING & DATA PROCESSING
        # ======================================================================
        detected_person_ids = set()
        if face_results.multi_face_landmarks:
            for face_landmarks in face_results.multi_face_landmarks:
                # A simple tracker using a single face and counter
                if not persons:
                    person_id_counter += 1
                    persons[person_id_counter] = PersonTrack(person_id_counter, ts)
                
                pid = next(iter(persons))  # Get the only person ID
                person = persons[pid]
                detected_person_ids.add(pid)
                person.last_seen_ts = ts
                
                # Bounding box
                x_min = min([lm.x for lm in face_landmarks.landmark])
                y_min = min([lm.y for lm in face_landmarks.landmark])
                x_max = max([lm.x for lm in face_landmarks.landmark])
                y_max = max([lm.y for lm in face_landmarks.landmark])
                bbox = (int(x_min * w), int(y_min * h), int((x_max - x_min) * w), int((y_max - y_min) * h))
                person.face_bbox = bbox
                
                # Head pose
                pose, head_score = scorer._get_head_pose_score(face_landmarks.landmark, frame.shape)
                person.head_pose = pose
                
                # Eye landmarks for EAR
                l_eye_lm_indices = [33, 160, 158, 133, 153, 144]
                r_eye_lm_indices = [362, 385, 387, 263, 373, 380]
                l_eye_lm = [face_landmarks.landmark[i] for i in l_eye_lm_indices]
                r_eye_lm = [face_landmarks.landmark[i] for i in r_eye_lm_indices]
                ear = (scorer._get_ear(l_eye_lm) + scorer._get_ear(r_eye_lm)) / 2
                eye_score = scorer._get_ear_score(ear)
                person.eye_open_score = eye_score
                
                # Iris landmarks for gaze
                iris_lm_indices = [474, 475, 476, 477, 469, 470, 471, 472] # left, then right
                iris_lm = [face_landmarks.landmark[i] for i in iris_lm_indices]
                gaze_score, gaze_offset = scorer._get_gaze_score(iris_lm, l_eye_lm + r_eye_lm, pose)
                person.gaze_offset = gaze_offset
                
                # Hand proximity
                hand_score = scorer._get_hand_score(person, hand_results.multi_hand_landmarks, frame.shape)
                
                # Fusion
                frame_attention = scorer.fuse_scores(head_score, gaze_score, eye_score, hand_score)
                person.frame_attention = frame_attention

                # Update buffers
                person.ema_attention = (Config.EMA_ALPHA * frame_attention +
                                        (1 - Config.EMA_ALPHA) * person.ema_attention)
                person.update_buffers(frame_attention, True, ts)

        # ======================================================================
        # ALERT CHECK & VISUALIZATION
        # ======================================================================
        
        # Periodic 5-minute alert check
        if ts - last_alert_check >= Config.ALERT_CHECK_INTERVAL:
            print("--- Running 5-minute alert check ---")
            for pid, person in list(persons.items()): # Use list to avoid issues if persons dict changes
                stats = person.get_window_stats('5m')
                attention_pct = stats['avg_attention'] * 100
                presence_pct = stats['presence_pct'] * 100
                
                if presence_pct < Config.FACE_PRESENCE_MIN_PCT:
                    print(f"Person {pid}: Insufficient data ({presence_pct:.1f}% presence).")
                    person.alert_flag = False
                    person.alert_count = 0
                elif attention_pct < Config.ALERT_THRESHOLD_PCT:
                    person.alert_count += 1
                    if person.alert_count >= Config.CONSECUTIVE_ALERT_WINDOWS_REQUIRED:
                        person.alert_flag = True
                        print(f"ALERT for Person {pid}! 5-min attention: {attention_pct:.1f}%")
                        person.alert_history.append({
                            "timestamp": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime(ts)),
                            "person_id": pid,
                            "avg_attention_5m": stats['avg_attention'],
                            "presence_pct": stats['presence_pct'],
                            "reason": f"5min avg < threshold ({Config.ALERT_THRESHOLD_PCT}%)"
                        })
                        red_box_timers[pid] = ts + Config.RED_BOX_DURATION
                else:
                    person.alert_flag = False
                    person.alert_count = 0
            
            last_alert_check = ts

        # Visualization
        for pid, person in list(persons.items()):
            if person.face_bbox:
                x, y, w, h = person.face_bbox
                color = (0, 255, 0) # Green for focused
                
                if person.alert_flag or (pid in red_box_timers and time.time() < red_box_timers[pid]):
                    color = (0, 0, 255) # Red for distracted alert
                    person.alert_flag = True # Keep flag true for persistent box

                # Draw bounding box
                cv2.rectangle(frame, (x, y), (x + w, y + h), color, 2)
                
                # Display scores
                score_text = f"Attn: {int(person.ema_attention*100)}%"
                cv2.putText(frame, score_text, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
                
                # Display alert reason if active
                if person.alert_flag:
                    cv2.putText(frame, "DISTRACTION ALERT", (x, y + h + 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2)
                    
        cv2.imshow('Student Engagement Monitor', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Clean up
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    # Ensure all required libraries are installed
    # pip install opencv-python mediapipe numpy
    
    print("Initializing components...")
    main()