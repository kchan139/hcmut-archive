#include <iostream>
#include <string>
#include <tuple>
using namespace std;

void process (char *);
void mostFrequentCharacter (char *, char &, int &);

int convertToBaseM (int, int base = 2);

int main ()
{
    int n; cin >> n;
    char * str = new char[n+1];

    for (size_t c = 0; c < n; c++)
        cin >> str[c];
    str[n] = '\0';

    char res = 0;
    int freq = 0;

    mostFrequentCharacter (str, res, freq);
    cout << res << ' ' << freq << endl << endl;
    delete [] str;


    int num; cin >> num;
	cout << convertToBaseM(n, 4) << '\n';
	cout << convertToBaseM(n, 8) << '\n';
	cout << convertToBaseM(n);


}

void mostFrequentCharacter (char * str, char & res, int & freq)
{
    process (str);
    int cache[26] = {0};
    int index;

    while (*str)
    {
        cache[*str - 'a']++;
        str++;
    }
    for (size_t i = 0; i < 26; i++)
    {
        if (cache[i] > freq)
        {
            freq  = cache[i];
            index = i;
        }
    }
    res = (char)(index + 'a');
}

void process (char * str)
{
    while (*str)
    {
        while (*str >= 'a' && *str <= 'z')
            str++;
        if (*str >= 'A' && *str <= 'Z')
            { *str += 32; str++; }
    }
}

int convertToBaseM (int n, int m)
{
    if (!n) return 0;
    return n % m  +  10 * convertToBaseM(n / m, m);
}