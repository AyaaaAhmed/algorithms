// GROUP:   2
// ID:      20150071
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Aya ahmed abd elomonem
//username: ayaaayaa
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;
	void Initialize(int _n)
	{
	    n = _n;
	    parent = new int [n];
	    num_nodes = new int [n];
	    for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            num_nodes[i] = 1;
        }
	}
	void Destroy()
	{
	    delete [] parent;
	    delete [] num_nodes;
	}
	int Find(int i)
	{
	    if ( parent[i] == i)
            return i;
        return Find(parent[i]);;
	}
	bool Union(int i, int j)
	{
	    int found_i = Find(i);
	    int found_j = Find(j);
	    if ( found_i == found_j )  return false;
	    else
        {
            if ( num_nodes[found_i] <= num_nodes[found_j])
            {
                parent[found_i] = found_j;
                num_nodes[found_j] += num_nodes[found_i];
                return true;
            }
            else
            {
                parent[found_j] = found_i;
                num_nodes[found_i] += num_nodes[found_j];
                return true;
            }
        }
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int i = 0,j = mid,k;
    Type *t = new Type[n];
    for (k = 0;k < n;k++)
    {
        if (j == n ||(i < mid && IsBefore(a[i] , a[j])))
            t[k] = a[i++];
        else
        {
            t[k] = a[j++];
        }
    }
    for(i = 0;i < n;i++)
    {
        a[i] = t[i];
    }
    delete []t;
}
template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if (n <= 1)
        return;
    MergeSort(a,mid,IsBefore);
    MergeSort(a+mid,n-mid,IsBefore);
    Merge(a,n,IsBefore);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Edge
{
	int u , v;
	int w;
};
bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w < b.w;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int m , n;
    cin >> m >> n;
    while(m !=0 && n != 0)
    {
        Edge edges[n];
        DisjointSets Set;
        Set.Initialize(m);
        for (int i = 0; i < n;i++)
        {
            Edge edge;
            cin >> edge.u>> edge.v>>edge.w;
            edges[i] = edge;
        }
        MergeSort(edges , n, IsBeforeEdge);
        int Cost = 0;
        for (int i = 0; i <n; i++)
        {
            if (Set.Union(edges[i].u,edges[i].v) == false )
            {
                Cost += edges[i].w;
            }
            else
                Set.Union(edges[i].u,edges[i].v);
        }
        cout << Cost << endl;
        cin >> m >> n;
    }
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
