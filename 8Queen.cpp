// GROUP:   2
// ID:      20150071
// Assign:  14
// Assign:  8Queen
// UVA:     11195
// Name:    Aya Ahmed Abdel Moneim
// UVA Username: ayaaayaa

#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_COMPUTERS 16

////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int		n, numberOfSolutions; // number of computers (input)
int		s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.
int     Forword[MAX_COMPUTERS*2];
int     Backword[MAX_COMPUTERS*2];
char    queenTable[MAX_COMPUTERS][MAX_COMPUTERS];


////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dancing Links:

int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
	int i;
	for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
	for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack2(int i)
{
    if (i == n)
    {
        bool chk = false;
        for ( int i = 0; i < n ; i++ )
        {
            if (queenTable[i][s[i]]=='*')
            {
                chk = false;
                break;
            }
            if(i+1 == n)
            {
                chk = true;
            }
        }

        if(chk == true)
        {
            numberOfSolutions += 1;
        }
        return;
    }

    for ( int j = F[0]; j != 0 ; j = F[j] )
    {
        if (!Forword[(j - i) + 7] && !Backword[j + i])
        {
            Forword[(j - i) + 7] = 1;
            Backword[j + i] = 1;

            s[i] = j - 1;
            Remove(j);
            Backtrack2(i + 1);
            Restore(j);

            Forword[(j - i) + 7] = 0;
            Backword[j + i] = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute2() // do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);
    Backtrack2(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void compute()
{
    int testCases = 1;
    while(true)
    {
        cin>>n;
        if(!cin || n==0) break;

        for (int i = 0; i<n ;i++)
        {
            for (int j = 0; j<n ;j++)
            {
                cin >> queenTable[i][j];
            }
        }

        Compute2();
        cout << "Case "<< testCases << ": " << numberOfSolutions << endl;
        testCases++;
        numberOfSolutions = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign13_00216.txt", "r", stdin);
    compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
