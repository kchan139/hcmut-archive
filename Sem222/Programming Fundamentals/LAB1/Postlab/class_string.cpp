#include <iostream>
#include <cstring>
using namespace std;

bool check (string &, int, int);

int main ()
{
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    int size = s.length();

    int starting_index = 0;
    int max_length     = INT8_MIN;

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i; j < size; j++)
        {
            if (check(s, i, j))
            {
                int length = j - i + 1;
                if (length > max_length)
                {
                    max_length = length;
                    starting_index = i;
                }
            }
        }
    }
    cout << s.substr(starting_index, max_length);

    return 0;
}

bool check (string & s, int i, int j)
{
    while (i < j)
    {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}
    