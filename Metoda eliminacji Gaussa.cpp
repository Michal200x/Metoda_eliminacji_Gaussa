#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <cstddef>

using namespace std;
const double eps = 1e-12; // stała przybliżenia zera

bool gauss(int n, double** AB, double* X)// za pomocą tej funkcji wykonuje się cały algorytm eliminacji gaussa
{
    double m, s;

    // przy pomocy poniższych forów eliminuje współczynniki 
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(AB[i][i]) < eps)
            {
                return false;
            }
            m = -AB[j][i] / AB[i][i];
            AB[j][i] = 0;
            for (int k = i + 1; k <= n; k++)
            {
                AB[j][k] += m * AB[i][k];
            }
        }
    }

    // przy pomocy poniższych forów wyliczam niewiadome

    for (int i = n - 1; i >= 0; i--)
    {
        s = AB[i][n];

        for (int j = n - 1; j >= i + 1; j--)
        {
            s -= AB[i][j] * X[j];
        }
        if (fabs(AB[i][i]) < eps)
        {
            return false;
        }

        X[i] = s / AB[i][i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cout << AB[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "--------------------------------------------------------------------------------" << endl;

    return true;
}


//------------------------------------------------------------------------------------------------------

int main()
{
    double* X;

    fstream file;
    file.open("in.txt", ios::in);

    int n;
    file >> n;

    // tworzenie tablicy dynamicznej dla macierzy dowolnej wielkości
    double** AB = new double* [n + 1];
    for (int i = 0; i < n + 1; i++) 
    {
        AB[i] = new double[n+1];
    }

    // wpisywanie danych z pliku do tablicy
    for (int x = 0; x < n; x++) 
    {
        for (int y = 0; y < n + 1; y++) 
        {
            double k;
            file >> k;
            AB[x][y] = k;
        }
    }
    file.close();

    X = new double[n];

    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            cout << AB[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "--------------------------------------------------------------------------------" << endl;
    
    if (gauss(n, AB, X)) // uruchamiamy naszą funkcję liczącą (eliminację gaussa)
    {
        for (int i = 0; i < n; i++)
        {
            cout << "x" << i + 1 << " = " << X[i] << endl; // wypisanie wyników
        }
    }
    else
    {
        cout << "DZIELNIK ZERO" << endl; // jeśli będziemy dzielić przez 0 kompilator to wypisze
    }

    for (int i = 0; i < n; i++)
    {
        delete[] AB[i];
    }
    delete[] AB;
    delete[] X;

    return 0;
}