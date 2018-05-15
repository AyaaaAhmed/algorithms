// GROUP:   2
// ID1:      20150071
// ID2:      20150080
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Aya Ahmed Abdel Elmoneim
// Name2:   Bassem Elsayed Mohamed
// UVA Username: Basem Elsayed

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
	    sz = 1;
	    n = 0;
	    arr = new Value[sz];
	}


	void Destroy()
	{
	    delete [] arr;
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
        n--;
	}


	Value& operator[](int i)
	{
        return arr[i];
	}

	void print()
	{
	    for(int i=0;i<n;i++)
        {
            cout << arr[i] << "  ";
        }
        cout << endl << "Size = " << sz <<endl;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&)) // n is required to allocate and initialize pos[]
	{
        a.Initialize();
        IsBefore = _IsBefore;
	}


	void Destroy()
	{
        a.Destroy();
	}


	int Child(int i)
	{
        return (i*2) + 1;
	}


	int Parent(int i)
	{
	    return (i-1) / 2;
	}


	void MoveUp(int ind)
	{
        if(ind == 0 || !IsBefore(a.arr[ind], a.arr[Parent(ind)]))
        {
            return;
        }
        swap(a.arr[ind], a.arr[Parent(ind)]);
	    MoveUp(Parent(ind));
	}

	void MoveDown(int ind)
	{
        int l = Child(ind);
        int r = Child(ind) + 1;
        int smallest = ind;
        if ( l < a.n && IsBefore(a.arr[l], a.arr[ind]) )
            smallest = l;
        if ( r < a.n && IsBefore(a.arr[r], a.arr[smallest]) )
            smallest = r;
        if (smallest != ind)
        {
            swap(a.arr[ind], a.arr[smallest]);
            MoveDown(smallest);
        }
	}


	void Add(Elem e)
	{
	    a.AddLast(e);
        MoveUp(a.n-1);
	}


	Elem GetFirst()
	{
	    return a[0];
	}


	Elem RetrieveFirst()
	{
        a.arr[0] = a.arr[a.n-1];
        a.RemoveLast();
        MoveDown(0);
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int	v;
	int	w;
};

struct Node
{
	Array<Edge> adj;

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
	    for(int i=0; i<n ;i++)
        {
            nodes[i].Initialize();
        }
	}
	void Destroy()
	{
	    for(int i=0; i<n ;i++)
        {
            nodes[i].Destroy();
        }
        delete []nodes;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int Size = 2e4+4;
    int N;
    cin >> N;
    for(int i = 0; i < N ; i++)
    {
        Graph g;
        int n,m,s,t;
        g.Initialize(Size);
        cin >> n >> m >> s >> t;
        for(int j = 0 ; j < m ; j++)
        {
            int a,b,w;
            cin >> a >> b >> w;
            g.nodes[a].adj.AddLast({b,w});
            g.nodes[b].adj.AddLast({a,w});
        }

        int vist[Size];
        int dist[Size];
        for(int j=0; j<Size ;j++)
        {
            dist[j] = 999999;
            vist[j] = 0;
        }

        Heap <Edge> heap;
        heap.Initialize(IsBefore);
        heap.Add({s,0});
        dist[s] = 0;
        while(heap.a.n > 0)
        {
            Edge first = heap.GetFirst();
            heap.RetrieveFirst();

            vist[first.v] = 1;
            for(int j = 0 ; j < g.nodes[first.v].adj.n; j++)
            {
                Edge child = g.nodes[first.v].adj[j];
                if (!vist[child.v] && (dist[child.v] > (dist[first.v] + child.w)) )
                {
                    child.w = dist[child.v] = (dist[first.v]+child.w);
                    heap.Add(child);
                }
            }
        }
        cout << "Case #" << i+1 << ": ";
        if (dist[t] < 999999)
            cout << dist[t] << endl;
        else
            cout << "unreachable" << endl;

        heap.Destroy();
        g.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
