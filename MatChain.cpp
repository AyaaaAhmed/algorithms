// GROUP:   2
// ID:      20150071
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Aya Ahmed Abd Elmonem
//Username :ayaaayaa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b) // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
{
    if (T[a][b] >= 0) return T[a][b];
    if (a + 1 == b)
    {
        T[a][b] =0;
        return 0;
    }
    int k;
    T[a][b] = 9999999999;
    for (k = a + 1; k < b; k++)
    {
        int v = MatChain(a,k) + MatChain(k,b)+ p[a] * p[k] * p[b];
        if ( v < T[a][b])
        {
            T[a][b] = v;
            D[a][b] = k;
        }
    }
    return T[a][b];
}
void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
    for (int i=0 ; i<11; i++)
    {
        for (int j=0 ; j<11; j++)
        {
            T[i][j] = -1;
        }
    }
    MatChain(0,n);
}

// BottomUp version
void MatChainBottomUp(int n)
{
    for (int i=0; i<11 ; i++)
    {
        for (int j=0; j<11 ; j++)
        {
            T[i][j] = -1;
        }
    }

    for (int s=1; s<=n ; s++)
    {
        for (int i=0; i+s<=n ; i++)
        {
            int j = i+s;
            MatChain(i,j);
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    int k = D[a][b];
    if (a+1 == b)
    {
        cout << "A" << b;
        return;
    }

    cout<<"(";
    MatChainSol(a,k);
    cout<<" x ";
    MatChainSol(k,b);
    cout<<")";

}

void Compute()
{
    int nOfArrays,counter = 0, num = 0;
    while (true)
    {
        cin >> nOfArrays;
        if (nOfArrays == 0) break;
        for (int i=0; i<nOfArrays ; i++)
        {
            int r,c;
            cin >> r >> c;
            p[counter++] = r;
            if (i+1 == nOfArrays)
            {
                p[counter] = c;
            }
        }
        MatChainBottomUp(nOfArrays);
        cout << "Case "<< num + 1 <<": ";
        num++;
        MatChainSol(0,nOfArrays);
        counter =0 ;
        cout<<endl;

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
