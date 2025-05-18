#include <iostream>
using namespace std;

const int MATRIX_SIZE = 4;

int main() 
{
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    cout << "Task 2: Enter elements of a 4x4 square matrix:" << endl;

    for (int i = 0; i < MATRIX_SIZE; i++) 
    {
        for (int j = 0; j < MATRIX_SIZE; j++) 
        {
            cout << "Enter element at position (" << i << "," << j << "): ";
            cin >> matrix[i][j];
        }
    }

    cout << "\nMatrix:" << endl;
    for (int i = 0; i < MATRIX_SIZE; i++) 
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            cout << matrix[i][j] << "\t";
        cout << endl;
    }

    int totalSum = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            totalSum += matrix[i][j];

    cout << "\nSum of all elements in the matrix: " << totalSum << endl;

    cout << "Sum of all elements in each row:" << endl;
    for (int i = 0; i < MATRIX_SIZE; i++) 
    {
        int rowSum = 0;
        for (int j = 0; j < MATRIX_SIZE; j++)
            rowSum += matrix[i][j];
            
        cout << "Row " << i + 1 << ": " << rowSum << endl;
    }

    cout << "\nSum of all elements in each column:" << endl;
    for (int j = 0; j < MATRIX_SIZE; j++) 
    {
        int colSum = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
            colSum += matrix[i][j];

        cout << "Column " << j + 1 << ": " << colSum << endl;
    }

    int mainDiagonalSum = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
        mainDiagonalSum += matrix[i][i];
        
    cout << "\nSum of all elements in the main diagonal: " << mainDiagonalSum << endl;

    int secondaryDiagonalSum = 0;
    for (int i = 0; i < MATRIX_SIZE; i++)
        secondaryDiagonalSum += matrix[i][MATRIX_SIZE - 1 - i];

    cout << "Sum of all elements in the secondary diagonal: " << secondaryDiagonalSum << endl;

    return 0;
}
