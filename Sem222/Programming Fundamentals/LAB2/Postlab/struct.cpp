#include <iostream>
#include <string>
using namespace std;

struct SCP 
{
    int      id;
    int      objClass;
    string   speConProcedures;
    string   description;
    string * addendums;
    int      numAddendums;

    SCP (int id, int objClass, string specC, string des)
    {
        this->id               = id;
        this->objClass         = objClass;
        this->speConProcedures = specC;
        this->description      = des;
        this->addendums        = nullptr;
        this->numAddendums     = 0;
    }
};

void swap (SCP & x, SCP & y)
{
    SCP tmp = x;
          x = y;
          y = tmp;
}

SCP ** sortDatabase (SCP ** data, int n) 
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (data[i]->id >= data[j]->id)
                swap (*data[i], *data[j]);

    return data;
}

int main()
{
    int n = 3;
    SCP ** data = new SCP * [n];
    data[0] = new SCP (2, 1, "SCP-002 is to remain connected to a suitable power supply at all times.", "SCP-002 resembles a tumorous, fleshy growth with a volume of roughly 60 cubed meter.");
    data[1] = new SCP (55, 2, "Object is kept within a five (5) by five (5) by two point five (2.5) meter square room.", "All known information about the object is that it is not round.");
    data[2] = new SCP (49, 1, "SCP-049 is contained within a Standard Secure Humanoid Containment Cell in Research Sector-02 at Site-19.", "SCP-049 is a humanoid entity, roughly 1.9 meters in height, which bears the appearance of a medieval plague doctor.");

    data = sortDatabase(data, n);

    for (int i = 0; i < n; i++) 
        cout << data[i]->id << " ";

    for (int i = 0; i < n; i++) 
    {
        delete [] data[i]->addendums;
        delete data[i];
    }


    delete [] data;
    return 0;
}