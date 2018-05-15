// GROUP:   2
// ID:      20150071
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Aya Ahmed Abdel Moneim
// UVA Username: ayaaayaa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m)
{
    if(n == 0) return m;
    if(m == 0) return n;
    if(a[m-1] == b[n-1]) return EditDist1(m-1, n-1);
    else
    {
        int Insert = 99999999, Delete = 99999999, Replace = 99999999;
        Delete = 1 + EditDist1(n, m-1);
        Insert = 1 + EditDist1(n-1, m);
        if(a[n-1] != b[m-1])
        {
            Replace = 1 + EditDist1(n-1, m-1);
        }
        else
        {
            Replace = EditDist1(n-1, m-1);
        }
        T1[n][m] = min(Delete, min(Insert,Replace));
        return T1[n][m];
    }
}

int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
    for (int i = 0; i < 81 ;i++)
        for (int j = 0; j < 81 ;j++)
            T1[i][j] = -1;
    return EditDist1(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    for (int i = 0; i < 81 ;i++)
    {
        for (int j = 0; j < 81 ;j++)
        {
            T2[i][j] = -1;
        }
    }
    for (int n = 0; n <= N ;n++)
    {
        for (int m = 0; m <= M ;m++)
        {
            int Insert = 99999999, Delete = 99999999, Replace = 99999999;
            if(n == 0 && m == 0)
            {
                T2[n][m] = 0;
                D[n][m] = -1;
                continue;
            }
            if(n > 0)
            {
                Delete = 1 + T2[n-1][m];
                D[n][m] = 2;
            }
            if(n > 0 && m > 0)
            {
                if(a[n-1] != b[m-1])
                {
                    Replace = 1 + T2[n-1][m-1];
                }
                else
                {
                    Replace = T2[n-1][m-1];
                }
                D[n][m] = 1;
            }
            if(m > 0)
            {
                Insert = 1 + T2[n][m-1];
                D[n][m] = 3;
            }
            else
            {
                D[n][m] = 0;
            }
            T2[n][m] = min(Insert, min(Delete, Replace));
        }
    }
    return T2[N][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<81; j++)
        {
            T3[i][j] =- 1;
        }
    }

    int cur = 0;
    for (int n = 0; n <= N ;n++)
    {
        for (int m = 0; m <= M ;m++)
        {
            int Insert = 99999999, Delete = 99999999, Replace = 99999999;
            if(n == 0 && m == 0)
            {
                T3[cur][m] = 0;
                D[n][m] = -1;
                continue;
            }
            if(n > 0)
            {
                Delete = 1 + T3[1-cur][m];
                D[n][m] = 2;
            }
            if(n > 0 && m > 0)
            {
                if(a[n-1] != b[m-1])
                {
                    Replace = 1 + T3[1-cur][m-1];
                }
                else
                {
                    Replace = T3[1-cur][m-1];
                }
                D[n][m] = 1;
            }
            if(m > 0)
            {
                Insert = 1 + T3[cur][m-1];
                D[n][m] = 3;
            }
            else
            {
                D[n][m] = 0;
            }
            T3[cur][m] = min(Insert, min(Delete, Replace));
        }
        cur = 1 - cur;
    }
    return T3[1-cur][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
    for(int i=0; i<81; i++) T4[i]=-1;

    for(int n=0; n <= N; n++)
    {
        for(int m = M; m >= 0; m--)
        {
            int Insert = 99999999, Delete = 99999999, Replace = 99999999;
            if(n == 0 && m == 0)
            {
                T4[m] = 0;
                D[n][m] = -1;
                continue;
            }
            if(n > 0)
            {
                Delete = 1 + T4[m-1];
                D[n][m] = 2;
            }
            if(n > 0 && m > 0)
            {
                if(a[n-1] != b[m-1])
                {
                    Replace = 1 + T4[m-1];
                }
                else
                {
                    Replace = T4[n-1];
                }
                D[n][m] = 1;
            }
            if(m > 0)
            {
                Insert = 1 + T4[m];
                D[n][m] = 3;
            }
            else
            {
                D[n][m] = 0;
            }
            T4[m] = min(Insert, min(Delete, Replace));
        }
    }
    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
	int n,m;
	int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
    for(int n=N; n>=0 ; n--)
    {
        for(int m=M; m>=0 ;m--)
        {
            if(D[n][m] == 2)
            {
                n--;
            }
            else if(D[n][m] == 1)
            {
                n--;
                m--;
            }
            else if(D[n][m] == 3)
            {
                m--;
            }
            //cout << D[n][m] << "   ";
        }
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
	//return ComputeEditDist1(N,M);
	//return ComputeEditDist2(N,M);
	//return ComputeEditDist3(N,M);
	return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
	int cas=0;
	while(true)
	{
		a[0]=0; b[0]=0;
		if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
		a[strlen(a)-1]=0;
		b[strlen(b)-1]=0;
		if(cas) cout<<endl; // print an empty line between test cases
		int N=strlen(a), M=strlen(b);
		ComputeEditDist(N,M);
		EditDistSol(N,M);
		cas++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign11_00526.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
