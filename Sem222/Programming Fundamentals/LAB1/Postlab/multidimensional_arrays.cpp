#include <iostream>
#include <vector>
using namespace std;

bool isPrime (int);
int specialCells(int [][1000], int, int);
int subMatrix(int [][1000], int, int);

int main() 
{
	int arr1[][1000] = { {37, 53, 74}, {12, 37, 60}, {98, 13, 15} };
	cout << specialCells(arr1,3,3) << endl;

    int arr2[][1000] = {{66,16,71},{25,81,61},{2,10,34}};
	cout << subMatrix (arr2, 3, 3);
}

int specialCells (int arr[][1000], int row, int col)
{
    int rowSum = 0, colSum = 0;
    vector<int> primeRow, primeCol;

    // check for prime rowsum
    for (size_t r = 0; r < row; r++)
    {
        for (size_t c = 0; c < col; c++)
            rowSum += arr[r][c];
        if (isPrime(rowSum))
            primeRow.push_back(r);
        rowSum = 0;
    }

    // check for prime colsum
    for (size_t c = 0; c < col; c++)
    {
        for (size_t r = 0; r < row; r++)
            colSum += arr[r][c];
        if (isPrime(colSum))
            primeCol.push_back(c);
        colSum = 0;
    }

    return primeRow.size() * primeCol.size();
}

int subMatrix (int arr[][1000], int row, int col)
{
    int count = 0, sum = 0;
    for (size_t r = 0; r < row - 1; r++)
    {
        for (size_t c = 0; c < col - 1; c++)
        {
            sum = arr[r][c]     + arr[r][c + 1] +
                  arr[r + 1][c] + arr[r + 1][c + 1];
            if (sum % 2) count++;
        }
    }
    return count;
}

bool isPrime (int n)
{
    if (n < 2) return false;
    for (size_t i = 2; i * i <= n; i++)
        if (!(n % i)) return false;
    return true;
}
