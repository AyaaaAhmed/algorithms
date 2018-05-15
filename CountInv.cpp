// GROUP:   2
// ID:      20150071
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Aya Ahmed Abd elmonem
//username: ayaaayaa
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
long long CountInvMerge(long long* a, int n)
{
    int mid = n/2;
    int i = 0,j = mid,k;
    long long val = 0;
    long long int *t = new long long int[n];
    for (k = 0;k < n;k++)
    {
        if (j == n ||(i < mid && a[i] < a[j]))
            t[k] = a[i++];
        else
        {
            val += mid - i;
            t[k] = a[j++];
        }

    }
    for(i = 0;i < n;i++)
    {
        a[i] = t[i];
    }

    return val;
}

long long CountInv(long long* a, int n)
{
    int mid = n/2;
    if (n <= 1)
        return 0;
    return (CountInv(a,mid)+CountInv(a+mid,n-mid)+CountInvMerge(a,n));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int nn,m;
    cin>>nn;
    while(nn != 0)
    {
        long long int *aa = new long long int[nn];
        for (int i=0;i<nn;i++)
        {
            cin >> aa[i];
        }
       // delete[]aa;
        cout<<CountInv(aa,nn)<<endl;
        cin >> nn;
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
