#include <iostream>
using namespace std;

int main ()
{
    cout << "Enter the amount in VND: ";

    double vnd;
    cin >> vnd;

    cout << "Convert to (1: AUD, 2: USD): ";
    int userChoice;
    cin >> userChoice;

    if (userChoice == 1)
        cout << vnd << " VND is equal to " << vnd * 0.000061 << " AUD. (as of Feburary 2024)" << endl;
    else if (userChoice == 2)
        cout << vnd << " VND is equal to " << vnd * 0.000041 << " USD. (as of Feburary 2024)" << endl;
    else cout << "Invalid choice!" << endl;

    return 0;
}