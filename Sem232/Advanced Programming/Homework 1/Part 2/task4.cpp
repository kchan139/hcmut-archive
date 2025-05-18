// SIMPLE SOFTWARE THAT DISPLAYS BASIC INFORMATION 
// OF A STUDENT

#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
    string name, dob, hometown, major, favorite_animal;

    cout << "Enter full name: ";
    getline (cin, name);
    cout << "Enter date of birth (dd/mm/yy): ";
    getline (cin, dob);
    cout << "Hometown: ";
    getline (cin, hometown);
    cout << "Favorite animal: ";
    getline (cin, favorite_animal);

    cout << endl;
    cout << "=================================" << endl;
    cout << "      STUDENT'S INFORMATION" << endl;
    cout << "---------------------------------" << endl;
    cout << "Name: " << name << endl;
    cout << "Birthday: " << dob << endl;
    cout << "From: " << hometown << endl;
    cout << "Favorite animal: " << favorite_animal << endl;
    cout << "=================================" << endl << endl;

    return 0;
}