#include <iostream>
using namespace std;

int main ()
{
    cout << "Enter your age: ";
    int age;
    cin >> age;

    cout << "Ticket price: ";
    if (age < 5)
        cout << "Free";
    else if (age <= 10)
        cout << "10 dollars";
    else if (age <= 16)
        cout << "20 dollars";
    else 
        cout << "25 dollars";
    cout << endl;

    return 0;
}