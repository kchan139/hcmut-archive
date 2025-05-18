#include <iostream>
using namespace std;

int main () 
{
    const int secretNumber = 12;
    int guess;

    cout << "Welcome to the number guessing game!" << endl;

    do 
    {
        cout << "Make a guess between 0 and 20: ";
        cin >> guess;

        if (guess < secretNumber)
            cout << "Too small! Try again." << endl;
        else if (guess > secretNumber)
            cout << "Too large! Try again." << endl;
        else
            cout << "Congratulations! You guessed the secret number." << endl;
            
    } while (guess != secretNumber);

    return 0;
}
