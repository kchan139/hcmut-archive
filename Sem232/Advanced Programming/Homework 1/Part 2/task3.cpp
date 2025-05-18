// SIMPLE CALCULATOR THAT TAKES A NUMBER AND
// DISPLAY ITS MATH FUNCTION VALUES

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main ()
{
    cout << "Enter a number: ";

    double num;
    cin >> num;

    cout << "abs("   << num << ")   = "  << abs (num)   << endl;
    cout << "sin("   << num << ")   = "  << sin (num)   << endl;
    cout << "cos("   << num << ")   = "  << cos (num)   << endl;
    cout << "tan("   << num << ")   = "  << tan (num)   << endl;
    cout << "ln("    << num << ")    = " << log (num)   << endl;
    cout << "log10(" << num << ") = "    << log10 (num) << endl;
    cout << "sqrt("  << num << ")  = "   << sqrt (num)  << endl;
    cout << "exp("   << num << ")   = "  << exp (num)   << endl;

    return 0;
}