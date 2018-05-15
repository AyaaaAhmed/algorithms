// GROUP:   2
// ID:      20150071
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Aya Ahmed Abdel Moneim
// UVA Username: Ayaaayaa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    Type *merg = new Type[n];
    int middle = n / 2;
    if(n <= 1)
        return;
    int str1 = 0 , str2 = middle;
    for(int i = 0 ; i < n ; i++)
    {
        if(str2 == n || (str1 < middle && IsBefore(a[str1] , a[str2])))
            merg[i] = a[str1++];
        else
            merg[i] = a[str2++];
    }
    for(int i=0; i<n ;i++)
        a[i] = merg[i];
    delete [] merg;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n / 2;
    if(n <= 1)
        return;
    MergeSort(a, mid, IsBefore);
    MergeSort(mid+a ,n-mid, IsBefore);
    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v;
	int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    return (a.v/(double)a.w) > (b.v/(double)b.w);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
    int upperBound = 0, j;
    for(j = i ; j < n; j++)
    {
        if (w >= a[j].w)
        {
            upperBound += a[j].v;
             w -= a[j].w;
        }
        else
        {
            break;
        }
    }
    upperBound += (w / double(a[j-1].w)) * a[j-1].v;
    return upperBound;
}

void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    int upperBound = Bound(i,w);
    if ((upperBound + cur_val) <= best_val)
    {
        return;
    }

    if(i == n)
    {
        if(cur_val >= best_val)
        {
            best_val = cur_val;
        }
        return;
    }

    if(a[i].w <= w)
    {
        BackTrack(i+1, w-a[i].w, cur_val+a[i].v);
    }
    BackTrack(i+1, w, cur_val);
}

int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
    BackTrack(0, W, 0);
    return best_val;
}

void Compute()
{
    int T;
    cin >> T;
    for(int i=0; i<T ;i++)
    {
        cin >> n;
        for(int j=0; j<n ;j++)
        {
            cin >> a[j].v >> a[j].w;
        }
        int maxNumberOfPeopleGroup;
        cin >> maxNumberOfPeopleGroup;
        MergeSort(a, n, IsBefore);
        int Max = 0;
        for(int j=0; j<maxNumberOfPeopleGroup ;j++)
        {
            int maxWeight;
            cin >> maxWeight;
            best_val = 0;
            Max += ComputeKnapsack(n, maxWeight);
        }
        cout << Max << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign12_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
