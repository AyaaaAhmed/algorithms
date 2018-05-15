// GROUP:   2
// ID:      20150071
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    Aya Ahmed Abdel Moneim
// UVA Username: Ayaaya

#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_COMPUTERS 8

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point{int x,y;};
double Dist(Point& a, Point& b)
{
    return sqrt(pow((a.x-b.x), 2) + pow((a.y-b.y), 2)) + 16;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int		n; // number of computers (input)
Point	com[MAX_COMPUTERS]; // locations of computers (input)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS]; // dist[i][j]=distance from com[i] to com[j] (pre-computed)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double	best_val; // best value until now
int		best_sol[MAX_COMPUTERS]; // best solution until now (a permutation)

int		s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSol() // evaluate the permutation s, then update best_val and best_sol if necessary
{
    for(int i=0; i<n ;i++)
    {
        best_sol[i] = s[i];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack0(int i) // backtrack using swaps
{
    if(i == n)
    {
        double val = 0;
        for(int j=0; j<n-1 ;j++)
        {
            val += dist[s[j]][s[j+1]];
        }

        if(val < best_val)
        {
            best_val = val;
            UpdateSol();
        }
        return;
    }

    for(int j=i; j<n ;j++)
    {
        swap(s[i], s[j]);
        Backtrack0(i+1);
        swap(s[i], s[j]);
    }
}
void Compute0() // do necessay initializations and call Backtrack0()
{
    for(int i=0; i<n ;i++)
        s[i] = i;
    Backtrack0(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool v[MAX_COMPUTERS]; // v[i]=true if com[i] already taken in the permutation

void Backtrack1(int i) // backtrack using the v[] array
{
    if(i == n)
    {
        double val = 0;
        for(int j=0; j<n-1 ;j++)
        {
            val += dist[s[j]][s[j+1]];
        }

        if(val < best_val)
        {
            best_val = val;
            UpdateSol();
        }
        return;
    }

    for(int j=0; j<n ;j++)
    {
        if(!v[j])
        {
            s[i] = j;
            v[j] = true;
            Backtrack1(i+1);
            v[j] = false;
        }
    }

}
void Compute1() // do necessay initializations and call Backtrack1()
{
    for (int i=0; i<n; i++)
    {
        v[i] = false;
    }
    Backtrack1(0);
}

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

void Backtrack2(int i) // backtrack using dancing links
{
    if(i == n)
    {
        double val = 0;
        for(int j=0; j<n-1 ;j++)
        {
            val += dist[s[j]][s[j+1]];
        }
        if(val < best_val)
        {
            best_val = val;
            UpdateSol();
        }
        return;
    }

    for(int j=F[0]; j!=0 ;j=F[j])
    {
        s[i] = j-1;
        Remove(j);
        Backtrack2(i+1);
        Restore(j);
    }

}
void Compute2() // do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);
    Backtrack2(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeCore()
{
	// do necessay initializations of dist[][] and best_val
    best_val = 99999999;
	for(int i=0; i<n ;i++)
    {
        for(int j=0; j<n ;j++)
        {
            dist[i][j] = Dist(com[i], com[j]);
        }
    }
	//Compute0();
	//Compute1();
	Compute2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute() // get input and then call ComputeCore(); then print output
{
    int netWorkNumber = 1;
    while(true)
    {
        cin>>n;
        if(!cin || n==0) break;
        for(int i=0; i<n ;i++)
        {
            cin >> com[i].x >> com[i].y;
        }

        ComputeCore();

        cout << "**********************************************************" << endl;
        cout << "Network #" << netWorkNumber << endl;
        netWorkNumber++;

        double sum = 0;
        for(int j=0; j<n-1 ;j++)
        {
            sum += Dist(com[best_sol[j]], com[best_sol[j+1]]);
            cout << "Cable requirement to connect (" << com[best_sol[j]].x << "," << com[best_sol[j]].y << ") to ("
                 << com[best_sol[j+1]].x << "," << com[best_sol[j+1]].y << ") is " << setprecision(2) << fixed
                 << Dist(com[best_sol[j]],com[best_sol[j+1]]) <<" feet." << endl;
        }
        cout  << "Number of feet of cable required is " << sum << "." << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign13_00216.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
