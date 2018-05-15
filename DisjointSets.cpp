// GROUP:   2
// ID:      20150071
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Aya Ahmed Abd Elmonem
// username: ayaaayaa
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
int main()
{
    int N,n,m,x,y,Max = 0;
    DisjointSets Set;
    cin >> N;
    for (int i = 0;i < N;i++)
    {
        cin >> m;
        Set.Initialize(m);
        cin >> n;
        for (int a = 0; a < n; a++)
        {
            cin>>x>>y;
            x--;
            y--;
            Set.Union(x,y);
        }
        Max = 0;
        for (int c = 0 ; c < m ; c++)
        {
            if (Set.num_nodes[c] > Max)  Max = Set.num_nodes[c];
        }
        cout << Max <<endl;
    }
	return 0;
}
