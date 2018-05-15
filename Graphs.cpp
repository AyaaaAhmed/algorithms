// GROUP:   2
// ID:      20150071
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Aya Ahmed Abd Elmonem
//Username :ayaaayaa
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize()
	{
	    n = 0;
	    sz = 1;
	    arr = new Value[sz];
	}


	void Destroy()
	{
	    delete[]arr;
	}


    void AddLast(Value v)
	{
	    if(n == sz)
        {
            Value * new_arr = new Value[sz];
            for(int i=0; i<n ;i++)
            {
                new_arr[i] = arr[i];
            }
            sz *= 2;
            arr = new Value[sz];
            for(int i=0;i<n;i++)
            {
                arr[i] = new_arr[i];
            }
            arr[n] = v;
            n++;
            delete [] new_arr;
        }
        else
        {
            arr[n] = v;
            n++;
        }
	}


	void RemoveLast()
	{
	    if(n > 0)
        {
            n--;
            if(n <= (sz/2))
            {
                Value * new_arr = new Value[sz];
                for(int i=0; i<n ;i++)
                {
                    new_arr[i] = arr[i];
                }
                sz /= 2;
                arr = new Value[sz];
                for(int i=0;i<n;i++)
                {
                    arr[i] = new_arr[i];
                }
                delete [] new_arr;
            }
        }
	}


	Value& operator[](int i)
	{
	    if( (n > 0) && (i < sz) )
        {
            return arr[i];
        }
	}

	void print()
	{
	    for(int i=0;i<n;i++)
        {
            cout << arr[i] << endl;
        }
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<int> adj;
	void Initialize()
	{
	    adj.Initialize();
	}
	void Destroy()
	{
	    adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;
	void Initialize(int _n)
	{
	    n = _n;
	    nodes = new Node[n];
	    for (int i = 0; i < n; i++)
        {
            nodes[i].Initialize();
        }
	}
	void Destroy()
	{
        for (int i = 0; i < n; i++)
        {
            nodes[i].Destroy();
        }
        delete []nodes;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Type>
struct Queue
{
	int f, n;
	Type* elems;
	void Initialize(int size)
	{
	    f = 0;
	    n = 0;
	    elems = new Type[size];
	}

	void Destroy()
	{
	    delete []elems;
	}

	void Add(Type t)
	{
	    elems[n++] = t;
	}

	Type Pop()
	{
	    Type F = elems[f];
	    f++;
	    return F;
	}

	Type Peek()
	{
	    return elems[f];
	}

	int Num()
	{
	    return ( n - f );
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BFS(Graph& g, int s)
{
    Queue <int> que;
    que.Initialize(10000);
    int maxDay = 0, index = 0;

    int* vis = new int[g.n];
    int* dst = new int[g.n];
    int* pre = new int[g.n];
    int* arr = new int [g.n];
    memset(vis, 0, ((sizeof(int))*g.n));
    memset(pre, -1, ((sizeof(int))*g.n));
    memset(arr, 0, ((sizeof(int))*g.n));
    for(int i=0; i<g.n; i++)
    {
        dst[i] = g.n;
    }
    vis[s] = 1;
    dst[s] = 0;
    que.Add(s);
    while(que.Num())
    {
        int cur = que.Pop();
        for(int i=0; i<g.nodes[cur].adj.n; i++)
        {
            int x = g.nodes[cur].adj[i];
            if(!vis[x])
            {
                vis[x] = 1;
                pre[x] = cur;
                dst[x] = dst[cur]+1;
                arr[dst[x]]++;
                que.Add(x);
            }
        }
    }

    for(int i=0; i<g.n ;i++)
    {
        if(maxDay < arr[i])
        {
            maxDay = arr[i];
            index = i;
        }
    }
    if(maxDay != 0 && index !=0)
    {
        cout << maxDay << " " << index << endl;
    }
    else
    {
        cout << 0 <<endl;
    }
    que.Destroy();
}
int main()
{
    int E,m,n,T,t;
    Graph G1;
    cin >> E;
    G1.Initialize(E);
    for (int i = 0; i < E; i++)
    {
        cin >> m;
        for (int j = 0; j < m; j++)
        {
            cin >> n;
            G1.nodes[i].adj.AddLast(n);
        }
    }
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> t;
        BFS(G1,t);
    }

    G1.Destroy();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
