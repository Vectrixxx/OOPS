// matrix_interchange.cpp
#include <iostream>
using namespace std;
int main() {
    int A[3][3], B[3][3];
    cout << "Enter 9 integers for matrix A:\n";
    for (int i=0;i<3;++i) for (int j=0;j<3;++j) cin >> A[i][j];
    cout << "Enter 9 integers for matrix B:\n";
    for (int i=0;i<3;++i) for (int j=0;j<3;++j) cin >> B[i][j];
    // swap
    for (int i=0;i<3;++i) for (int j=0;j<3;++j) {
        int tmp = A[i][j];
        A[i][j] = B[i][j];
        B[i][j] = tmp;
    }
    cout << "\nAfter interchange, matrix A:\n";
    for (int i=0;i<3;++i){ for (int j=0;j<3;++j) cout << A[i][j] << " "; cout << "\n"; }
    cout << "\nAfter interchange, matrix B:\n";
    for (int i=0;i<3;++i){ for (int j=0;j<3;++j) cout << B[i][j] << " "; cout << "\n"; }
    return 0;
}

