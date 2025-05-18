#include <iostream>
using namespace std;

template <typename T>
class AList
{
    const static int MAXSIZE = 20; //the maximum members of the list
    T * data; // keep the list
    int cursor = 0; // keep the position of the cursor
    int listSize; // the real size of the list

    public:
        AList() { data = new T[MAXSIZE];}
        void print() const 
        {
            for (int i = 0; i < listSize; ++i)
                cout << data[i] << ' ';
            cout << endl;
        }

        void insert (const T & v)
        {
            for (int i = listSize++; i > cursor; i--)
                data[i] = data[i-1];
            data[cursor] = v;
        }

        void insertBefore (const T & v, const T & k)
        {
            if (listSize == MAXSIZE)
                throw out_of_range("out of range");
                
            for (int i = 0; i < listSize; i++) 
            {
                if (data[i] == k) 
                {
                    for (int j = listSize++; j > i; j--)
                        data[j] = data[j - 1];
                    
                    data[i] = v;
                    cursor = i;
                    return;
                }
            }
        }
};

int main ()
{
    AList<int> arr;
    for (int i = 5; i > 0; i--)
        arr.insert(i);
    
    arr.print();

    try 
        { arr.insertBefore (0, 1); }
    catch (out_of_range)
        { cout << "out of range" << endl; }
    
    arr.print();

    return 0;
}