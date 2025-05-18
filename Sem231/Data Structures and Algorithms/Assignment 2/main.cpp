#include "main.h"
#include "restaurant.cpp"

int main (int argc, char * argv[]) 
{
    string fileName = (argc > 1) ? argv[1] : "test2.txt";
    simulate (fileName);

    return 0;
}