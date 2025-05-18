// SIMPLE PROGRAM TO CALCULATE AND DISPLAY
// X PERCENTAGE OF Y

#include <iostream>
using namespace std;

int main ()
{
    cout << "Enter x, y: ";

    float x, y;
    cin >> x >> y;

    cout << x << "% of " << y << ": " << x * y / 100 << endl;

    return 0;
}