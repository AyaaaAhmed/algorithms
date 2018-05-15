// GROUP:   2
// ID:      20150071
// Assign:  09
// Assign:  Knapsack
// UVA:     ayaaayaa
// Name:    Aya Ahmed Abd Elmonem
// UVA Username:

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w)
{
    if(n == 0)
    {
        T1[n][w] = 0;
        return 0;
    }

    if(T1[n][w] >= 0) return T1[n][w];

    int ret = Knapsack1(n-1, w);
    int cv = a[n-1].v,cw = a[n-1].w;
    if(cw <= w)
    {

        int r = cv + Knapsack1(n-1, w-cw);
        if(r > ret) ret=r;
    }
    T1[n][w] = ret;
    return ret;
}

int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    for (int i = 0; i < 1001; i++)
        for (int j =0; j < 31; j++)
            T1[i][j] = -1;
    return Knapsack1(N,W);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
    for(int i=0; i<1001; i++)
    {
        for(int j=0; j<31; j++)
        {
            T2[i][j]=-1;
        }
    }
    for(int n = 0; n <= N; n++)
        for(int w = 0; w <= W; w++)
        {
            if (n == 0)
            {
                T2[n][w] = 0;
                continue;
            }
            int ret = T2[n-1][w];
            int cv = a[n-1].v, cw = a[n-1].w;
            if (cw <= w)
            {
                int r = cv + T2[n-1][w-cw];
                if (r > ret)
                    ret = r;
            }
            T2[n][w] = ret;
        }
     return T2[N][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<31; j++)
        {
            T3[i][j]=-1;
        }
    }

    int cur = 0;
    for(int n=0; n<=N ;n++)
    {
        for(int w=0; w<=W ;w++)
        {
            if(n == 0)
            {
                T3[cur][w] = 0;
                continue;
            }
            T3[cur][w] = T3[1-cur][w];
            int cw = a[n-1].w, cv = a[n-1].v;
            if(cw <= w)
            {
                int r = cv + T3[1-cur][w-cw];
                if(r > T3[cur][w])
                {
                    T3[cur][w] = r;
                }
            }
        }
        cur = 1-cur;
    }
    return T3[1-cur][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    for(int i=0; i<31; i++) T4[i]=-1;
    for(int n=0; n <= N; n++)
    {
        for(int w = W; w >= 0; w--)
        {
            if(n == 0)
            {
                T4[w] = 0;
                continue;
            }
            int cw = a[n-1].w, cv = a[n-1].v;
            if(cw <= w)
            {
                int r = cv + T4[w-cw];
                if(r > T4[w]) T4[w] = r;
            }
        }
    }
    return T4[W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	return ComputeKnapsack4(N,W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int N;
    cin >> N;
	for(int i=0; i<N ;i++)
    {
        int numberOfBags;
        cin >> numberOfBags;
        for(int j=0; j<numberOfBags ;j++)
        {
            cin >> a[j].v >> a[j].w;
        }
        int numberOfGroups;
        cin >> numberOfGroups;
        int weightOptimal = 0;
        for(int j=0; j<numberOfGroups ;j++)
        {
            int n;
            cin >> n;
            weightOptimal += ComputeKnapsack(numberOfBags, n);
        }
        cout<< weightOptimal <<endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    /*a[0].v=72;
    a[0].w=17;
    a[1].v=44;
    a[1].w=23;
    a[2].v=31;
    a[2].w=24;
    int W = 26;
    cout<<ComputeKnapsack3(3,26);*/

    //freopen("input_assign09_10130.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
