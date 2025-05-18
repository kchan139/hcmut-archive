// SIMPLE SOFTWARE TO CONVERT USD INTO VND

#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
    cout << "Enter the amount in USD: ";

    double usd;
    cin >> usd;

    double vnd = usd * 24640;

    cout << fixed << setprecision (0);
    cout << usd << " USD is equal to " << vnd << " VND. (as of Feburary 2024)" << endl;

    return 0;
}