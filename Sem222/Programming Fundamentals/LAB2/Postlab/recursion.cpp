#include <iostream>
#include <string>
#include <math.h>
using namespace std;

bool palindromeRecursion (string);
int countWaySumOfSquare (int);
int countSumS (int, int);

int main ()
{
    string input [256];
    int n = 0;
    while (true)
    {
        cin >> input[n];
        if (input[n][0] == '*') break;
        n++;

        for (int i = 0; i < n; i++)
        {
            if (palindromeRecursion(input[i]))
                cout << "true";
            else cout << "false";

            cout << endl;
        }
    }
    cout << countWaySumOfSquare(100) << endl;

    return 0;
}

bool palindromeRecursion (string str)
{
    int strlen = str.length();
    if (strlen <= 1) return true;

    if (str[0] == str[strlen - 1])
        return palindromeRecursion (str.substr(1, strlen - 2));
    else return false;
}

int countWaySumOfSquare (int x)
{
    return countSumS (x, 1);
}

int countSumS (int x, int n)
{
    int value = x - n * n;
    if (!value) return 1; if (value < 0) return 0;
    return countSumS (value, n + 1) + countSumS (x, n + 1);
}