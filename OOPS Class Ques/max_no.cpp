#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, b, c;
    cout << "Enter coefficients a, b, c for parabola y = ax^2 + bx + c: ";
    cin >> a >> b >> c;

    int width = 60;   // width of the console grid
    int height = 20;  // height of the console grid
    char graph[20][60];

    // initialize grid with spaces
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            graph[i][j] = ' ';
        }
    }

    // plot parabola
    for(int x = -30; x < 30; x++) {
        int y = a*x*x + b*x + c;

        // scale and shift to fit in grid
        int gx = x + width/2;
        int gy = height/2 - y;

        if(gx >= 0 && gx < width && gy >= 0 && gy < height) {
            graph[gy][gx] = '*';
        }
    }

    // print the graph
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cout << graph[i][j];
        }
        cout << endl;
    }

    return 0;
}
