
/*
 * Reference: https://www.youtube.com/watch?v=HqPJF2L5h9U
 */

#include <iostream>

using namespace std;

void heapify(int arr[], int n, int i);

int main()
{

    int Arr[10] = {29, 3, 56, 9, 12, 20, 2, 70, 3, 80};
    for(int i=10; i>0; i--)
    {
        cout<<"index:"<<i<<endl;
        heapify(Arr, 10, i);
        for(int x: Arr)
        {
            cout<<x<<endl;
        }
        cout<<"*********"<<endl;
    }

    for(int x: Arr)
    {
        cout<<x<<endl;
    }
}

void heapify(int arr[], int n, int i)
{
    // make the initial values as invalid, as heap logically starts with index 1
    int swap_value=-1, swap_index=-1;

    // find out if it has left child
    if((i*2) <= n)
    {
        swap_value = arr[(i*2)-1];
        swap_index = i*2;
    }

    // find out if it has right child
    if((i*2) + 1 <= n)
    {
        if(swap_value<arr[(i*2)])
        {
            swap_value = arr[(i*2)];
            swap_index = (i*2) + 1;
        }
    }

    if((swap_index !=-1) && (arr[i-1] < swap_value))
    {
        arr[swap_index -1] = arr[i-1];
        arr[i-1] = swap_value;
        heapify(arr, n, swap_index);
    }    
}