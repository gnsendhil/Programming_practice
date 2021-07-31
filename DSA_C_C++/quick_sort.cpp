//https://www.youtube.com/watch?v=7h1s2SojIRw
//https://www.youtube.com/watch?v=QN9hnmAgmOc
#include <iostream>

using namespace std;

void printarray(int *a, int n)
{
    for(int i=0; i<n; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int partition(int i, int j, int *a)
{
    int pivot_index = i;

    while(i<j)
    {
        while(a[pivot_index]>= a[i])
            i++;
        
        while(a[pivot_index]< a[j])
            j--;

        if (i<j)
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        //printarray(a, 11);
    }
    int temp = a[pivot_index];
    a[pivot_index] = a[j];
    a[j] = temp;

    //printarray(a, 11);
    
    return j;
}

void quicksort(int low, int high, int *a)
{
    if(low<high)
    {
        int j = partition(low, high, a);
        cout<<"low:"<<low<<"high:"<<high<<"J:"<<j<<endl;
        quicksort(low, j-1, a);
        quicksort(j+1, high, a);
    }

}

int main()
{
    int N;
    cout<<"Enter the size of array";
    cin>>N;
    int a[N];
    //{10,6,5,8,22,1,3,24,12,26,12};
    for(int i=0; i<N; i++)
    {
        cin>>a[i];
    }

    quicksort(0,N-1, a);
    printarray(a, N);
}

