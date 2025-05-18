#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

float squareArea (float side)
{
    return side * side;
}

float rectangleArea (float length, float width) 
{
    return length * width;
}

float circleArea (float radius) 
{
    return M_PI * radius * radius;
}

float triangleArea (float base, float height) 
{
    return 0.5 * base * height;
}

int main() 
{
    int choice;
    float param1, param2;

    cout << "Task 2: Geometry Calculator" << endl;

    while (true)
    {
        cout << "\nChoose a shape:" << endl;
        cout << "1. Square"         << endl;
        cout << "2. Rectangle"      << endl;
        cout << "3. Circle"         << endl;
        cout << "4. Triangle"       << endl;
        cout << "Enter your choice (or -1 to quit): ";
        cin  >> choice;

        if (choice == -1)
            break;

        switch (choice) 
        {
            case 1:
                cout << "Enter the side length of the square: ";
                cin >> param1;
                cout << "Area of the square: " << squareArea (param1) << endl;
                break;

            case 2:
                cout << "Enter the length and width of the rectangle: ";
                cin >> param1 >> param2;
                cout << "Area of the rectangle: " << rectangleArea (param1, param2) << endl;
                break;

            case 3:
                cout << "Enter the radius of the circle: ";
                cin >> param1;
                cout << fixed << setprecision(2);
                cout << "Area of the circle: " << circleArea (param1) << endl;
                break;

            case 4:
                cout << "Enter the base and height of the triangle: ";
                cin >> param1 >> param2;
                cout << "Area of the triangle: " << triangleArea (param1, param2) << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
