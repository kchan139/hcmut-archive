#include <iostream>
#include <string>
using namespace std;

void findAllIndex (string, string);
void cutString    (string, int);

int main ()
{
    string s = " - - - - ";
    cutString(s, 4);
    cout << '.' << endl;

    string s1 = "Truong Dai hoc Bach khoa";
    string s2 = "o";
    findAllIndex(s1, s2);

    return 0;
}

void cutString (string s, int index)
{
    int strlen = s.length();
    if (index < strlen)
    {
        string tmp = s;
        s = tmp.substr(index, strlen - index);
        cout << s;
    }
}

void findAllIndex (string s1, string s2)
{
    int strlen1 = s1.length();
    int found   = -1;
    string s3   = "";

    for (size_t i = 0; i < strlen1; i++)
    {
        found = s1.find(s2, found + 1);
        if (found != -1)
            s3 += to_string(found) + ' ';
        else  i = strlen1;
    }
    if (!s3.length())
        cout << -1;
    else cout << s3;
}