// matrix_3x3_ops.cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int r = (int)sqrt(n);
    for (int i = 3; i <= r; i += 2) if (n % i == 0) return false;
    return true;
}

bool isPalindrome(int n) {
    if (n < 0) return false;
    int orig = n, rev = 0;
    if (n == 0) return true;
    while (n) { rev = rev * 10 + (n % 10); n /= 10; }
    return rev == orig;
}

bool isArmstrong(int n) {
    if (n < 0) return false;
    int orig = n, t = n, digits = 0, sum = 0;
    if (n == 0) digits = 1;
    while (t) { ++digits; t /= 10; }
    t = n;
    while (t) { int d = t % 10; sum += (int)pow(d, digits); t /= 10; }
    return sum == orig;
}

int main() {
    int m[3][3];
    cout << "Enter 9 integers (3x3 matrix row-wise):\n";
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) cin >> m[i][j];

    cout << "\nMatrix:\n";
    int totalSum = 0, pos = 0, neg = 0, primeCnt = 0;
    for (int i = 0; i < 3; ++i) {
        int rowSum = 0;
        for (int j = 0; j < 3; ++j) {
            cout << m[i][j] << " ";
            totalSum += m[i][j];
            rowSum += m[i][j];
            if (m[i][j] > 0) ++pos;
            else if (m[i][j] < 0) ++neg;
            if (isPrime(m[i][j])) ++primeCnt;
        }
        cout << "   | row sum = " << rowSum << "\n";
    }
    cout << "\nTotal sum of elements = " << totalSum << "\n";
    cout << "Positive count = " << pos << ", Negative count = " << neg << "\n";
    cout << "Prime count in matrix = " << primeCnt << "\n\n";

    // Palindrome and Armstrong checks
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            int val = m[i][j];
            cout << val << ": " << (isPalindrome(val) ? "Palindrome, " : "Not Palindrome, ");
            cout << (isArmstrong(val) ? "Armstrong\n" : "Not Armstrong\n");
        }

    // Diagonal sums (main + secondary)
    int mainDiag = 0, secDiag = 0;
    for (int i = 0; i < 3; ++i) {
        mainDiag += m[i][i];
        secDiag += m[i][2 - i];
    }
    int diagSum = mainDiag + secDiag;
    if ((3 % 2) == 1) diagSum -= m[1][1]; // center counted twice
    cout << "\nMain diagonal sum = " << mainDiag << ", Secondary diag sum = " << secDiag
         << ", Combined (no double count) = " << diagSum << "\n";

    // Transpose
    cout << "\nTranspose:\n";
    int t[3][3];
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) t[j][i] = m[i][j];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) cout << t[i][j] << " ";
        cout << "\n";
    }

    // Sort ascending: flatten, sort, refill row-major
    int flat[9], idx = 0;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) flat[idx++] = m[i][j];
    sort(flat, flat + 9);
    cout << "\nSorted ascending (3x3):\n";
    idx = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) cout << flat[idx++] << " ";
        cout << "\n";
    }

    return 0;
}

