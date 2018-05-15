// GROUP:   2
// ID:      20150071
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Aya Ahmed Abd Elmonem

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

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(int&, int&);
	void Initialize(bool (*_IsBefore)(int&, int&))
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
	    while( ind != 0 && (IsBefore( a[ind] , a[Parent(ind)])))
        {
            Elem temp =  a[Parent(ind)];
            a[Parent(ind)] = a[ind];
            a[ind] = temp;
            ind = Parent(ind);
        }
	}


    void MoveDown(int ind)
	{
        int l = Child(ind);
        int r = Child(ind) + 1;
        int smallest = ind;
        if ( IsBefore(l, a.n) && IsBefore(a.arr[l], a.arr[ind]) )
            smallest = l;
        if ( IsBefore(r, a.n) && IsBefore(a.arr[r], a.arr[smallest]) )
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


    int Get_Cost(Heap heap)
	{
	    int cost=0,total_cost=0;
        while (heap.a.n > 1)
        {
            cost = heap.GetFirst();
            heap.RetrieveFirst();
            cost += heap.GetFirst();
            heap.RetrieveFirst();
            total_cost += cost;
            heap.Add(cost);
        }
        return ( total_cost );
	}

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a < b;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Heap <int> heap;
    Array <int> arra;
    arra.Initialize();
    heap.Initialize(IsBeforeInt);
//    arra.Initialize(IsBeforeInt);
    int n , num ,cost;
    do
    {
        cin>>n;
        for (int i = 0; i < n; i++)
            {
                cin >> num;
                heap.Add(num);
            }
            cost = heap.Get_Cost(heap);
            if ( cost != 0)
                {
                    arra.AddLast(cost);
                    heap.Initialize(IsBeforeInt);
                }
                else
                    n=0;


    }while ( n !=0 );

     arra.print();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
