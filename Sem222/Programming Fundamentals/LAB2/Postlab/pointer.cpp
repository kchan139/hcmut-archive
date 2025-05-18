#include <iostream>
using namespace std;

bool isSymmetry (int * head, int * tail)
{
    int arrSize = tail - head + 1;
    for (int i = 0; i < arrSize; i++)
        if (head[i] != head[arrSize - i - 1])
            return false;
    return true;
}

int ** insertCol (int **&matrix, int & r, int & c, int * colArr, int col)
{

    for (int i = 0; i < r; i++) 
    {
        for (int j = 0; j < c; j++) 
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    int ** newMatrix = new int * [r];
    for (int row = 0; row < r; row++)
        newMatrix[row] = new int [c + 1];

    for (int row = 0; row < r; row++)
    {
        for (int cl = 0; cl < c + 1; cl++)
        {
            if (cl < col)
                newMatrix[row][cl] = matrix[row][cl];
            else if (cl == col)
                newMatrix[row][cl] = colArr[row];
            else
                newMatrix[row][cl] = matrix[row][cl - 1];
        }
    }

    for (int i = 0; i < r; i++)
        delete [] matrix[i];
    delete [] matrix;

    c++;
    return newMatrix;
}

bool deleteRow (int **& matrix, int & r, int & c, int row)
{
    int ** newMatrix = new int * [r - 1];
    for (int cl = 0; cl < c; cl++)
        newMatrix[cl] = new int[cl];

    for (int rw = 0; rw < r - 1; rw++)
    {
        for (int cl = 0; cl < c; cl++)
        {
            if (rw >= row)
                newMatrix[rw][cl] = matrix[rw + 1][cl];
            else    
                newMatrix[rw][cl] = matrix[rw][cl];
        }
    }

    for (int i = 0; i < r; i++)
        delete [] matrix[i];
    delete [] matrix;

    matrix = newMatrix; r--;
    return true;
}

bool deleteColumn (int **& matrix, int & r, int & c, int col)
{
    int ** newMatrix = new int * [r];
    for (int cl = 0; cl < c - 1; cl++)
        newMatrix[cl] = new int [cl];

    for (int rw = 0; rw < r; rw++)
    {
        for (int cl = 0; cl < c - 1; cl++)
        {
            if (cl >= col)
                newMatrix[rw][cl] = matrix[rw][cl + 1];
            else 
                newMatrix[rw][cl] = matrix[rw][cl];
        }
    }

    for (int i = 0; i < r; i++)
        delete [] matrix[i];
    delete[] matrix;

    matrix = newMatrix; c--;
    return true;
}

int main ()
{
    int array[] = {1, 2, 1};
    cout << isSymmetry (array, array + (sizeof(array) / sizeof(int)) - 1) << endl;

    int r, c;
    cin >> r >> c;
    int **arr = new int*[r];
    for (int i = 0; i < r; i++)
        arr[i] = new int[c];

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> arr[i][j];
            
    int col;
    cin >> col;
    int * colArr = new int[r];
    for (int i = 0; i < r; i++) 
        cin >> colArr[i];

    arr = insertCol(arr, r, c, colArr, col);
    for (int i = 0; i < r; i++) 
    {
        for (int j = 0; j < c; j++) 
            cout << arr[i][j] << " ";
        cout << endl;
    }

    deleteRow(arr, r, c, 1);
    for (int i = 0; i < r; i++) 
    {
        for (int j = 0; j < c; j++) 
            cout << arr[i][j] << " ";
        cout << endl;
    }

    deleteColumn(arr, r, c, 1);
    for (int i = 0; i < r; i++) 
    {
        for (int j = 0; j < c; j++) 
            cout << arr[i][j] << " ";
        cout << endl;
    }

    return 0;
}