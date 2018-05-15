// GROUP:   2
// ID1:      20150071
// ID2:      20150080
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Aya Ahmed Abdel Moneim
// Name2:   Bassem Elsayed Mohamed
// UVA Username: Basem Elsayed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>
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
            cout << arr[i] << "  ";
        }
        cout << endl << "Size = " << sz <<endl;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	int x,y; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize()
	{
	    adj.Initialize();
	}
	void Destroy()
	{
	    adj.Initialize();
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

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    double x=0, y=v, sqr;
    for(int i=0; i<n ;i++)
    {
        sqr = (x + y) / 2;
        if( (sqr * sqr) < v)
        {
            x = sqr;
        }
        else
        {
            y = sqr;
        }
    }
    return sqr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    int n, frogNumber = 0;
    Graph graph;
    while(true)
    {
        cin>>n;
        if(!cin || n==0) break;

        double *dist = new double[n];
        int *vist = new int[n];
        int *prev = new int[n];

        for(int i=0; i<n ;i++)
        {
            dist[i] = 9999999;
            vist[i] = 0;
            prev[i] = -1;
        }

        graph.Initialize(n);

        for(int i=0; i<n ;i++)
        {
            cin >> graph.nodes[i].x;
            cin >> graph.nodes[i].y;
        }

        int counter = 0;

        for(int i=0; i<n ;i++)
        {
            vist[counter] = 1;
            for(int j=0; j<n ;j++)
            {
                double d = Sqrt( (pow((graph.nodes[counter].x - graph.nodes[j].x),2) + pow((graph.nodes[counter].y - graph.nodes[j].y),2)) );
                if(!vist[j] && dist[j] > d)
                {
                    dist[j] = d;
                    prev[j] = counter;
                }
            }

            double Minimum = 9999999;
            for(int j=0; j<n ;j++)
            {
                if(!vist[j] && dist[j] < Minimum)
                {
                    Minimum = dist[j];
                    counter = j;
                }
            }

            if(counter == 1)
            {
                Minimum = 0;
                while(prev[counter] != -1)
                {
                    if(dist[counter] > Minimum)
                    {
                        Minimum = dist[counter];
                    }
                    counter = prev[counter];
                }
                frogNumber++;
                cout << "Scenario #"<< frogNumber <<endl;
                cout << "Frog Distance = " << setprecision(3) << fixed << Minimum << endl << endl;

                break;
            }
        }
        graph.Destroy();
    }


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
