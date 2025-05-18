#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void studentGrading (string);
void calMoney (string, string);
void manage (string, string, string);

int main ()
{
    string fileName = "path/to/file.txt";
	studentGrading(fileName);

    string price = "path/to/file.txt";
	string buy   = "path/to/file.txt";
	calMoney(price,buy);

    string library = "path/to/file.txt";
	string book    = "path/to/file.txt";
	string author  = "path/to/file.txt";
	manage(library, book, author);

    return 0;
}

void studentGrading (string filename)
{
    int n; float m, avg = 0;
    float grade[4]      = {0};
    bool flag           = true;

    ifstream myFile (filename);
    if (myFile.is_open())
    {
        myFile >> n;
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < 4; j++)
            {
                myFile >> m;
                if (m < 5) flag = false;
                avg += m;
            }
            avg /= 4;
            if (avg >= 8 && flag) 
                grade[0]++;
			else if (avg >= 6.5 && avg < 8 && flag) 
                grade[1]++;
			else if (avg >= 5 && avg < 6.5 && flag) 
                grade[2]++;
			else 
                grade[3]++;

			avg  = 0;
			flag = true;
        }
        for (size_t i = 0; i < 4; i++)
            cout << (char) (i + 'A') << " " << grade[i] << endl;
    }

    myFile.close();
}

void calMoney (string price, string buy)
{
    // PRICE
    string input;
    ifstream priceFile (price);
    getline (priceFile, input);
    int n = stoi (input);

    vector<pair<int, int>> priceList (n);
    for (size_t i = 0; i < n; i++)
        priceFile >> priceList[i].first >> priceList[i].second;

    // BUY
    ifstream buyFile (buy);
    getline (buyFile, input);
    int m = stoi (input);
    string str;

    vector<pair<string, int>> buyList(m);
    for (size_t i = 0; i < m; i++)
    {
        getline(buyFile, str);
        stringstream ss;
        if (str[str.length()] == '\r')
            str.resize(str.length() - 1);
        ss << str;
        ss >> buyList[i].first;
        while (!ss.eof())
        {
            int a, b;
            ss >> a >> b;
            for (size_t i = 0; i < priceList.size(); i++)
            {
                if (a == priceList[i].first)
                {
                    buyList[i].second += priceList[i].second * b;
                    break;
                }
            }
        }
    }
    for (pair<string, int> x: buyList)
        cout << x.first << " " << x.second << endl;
}

void manage (string library, string book ,string author)
{
    bool flag = false; string str;

    string chosenLib, chosenAuthor;
    getline (cin, str);
    int found    = str.find (' ');
    chosenLib    = str.substr(0, found);
    chosenAuthor = str.substr (found + 1);

    string input, libID;
    ifstream libFile (library);
    getline(libFile, input);
    int n = stoi (input);

    vector<int> bookID;
    for (size_t i = 0; i < n; i++)
    {
        getline (libFile, input);
        stringstream ss;
        ss << input; ss >> libID;
        if (chosenLib == libID)
        {
            int id; while (ss >> id)
                bookID.push_back(id);
        }
    }

    ifstream authorFile (author);
    getline (authorFile, input);
    n = stoi (input);

    string authorName;
    vector<int> authorID;
    for (size_t i = 0; i < n; i++)
    {
        getline(libFile, input);
        stringstream ss;
        ss << input; ss >> authorName;
        if (chosenAuthor == authorName)
        {
            int id; while (ss >> id)
                authorID.push_back(id);
        }
    }
    for (size_t x : authorID)
        for (size_t y : bookID)
            if (x == y) flag = true;
    if (flag) cout << "True";
        else  cout << "False";    
}