// SIMPLE SOFTWARE THAT TAKES THE RADIUS AND THE HEIGHT
// OF A CYLINDER AND CALCULATE ITS VOLUME

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main ()
{
    cout << "Enter radius, height: ";
    
    double r, h;
    cin >> r >> h;

    cout << fixed << setprecision (3);
    cout << "Volume of the cylinder: " << M_PI * r*r*h << endl;

    return 0;
}