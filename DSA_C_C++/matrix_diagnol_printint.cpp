#include <iostream>
#include <vector>

using namespace std;

int a[4][4] = {{1,2,3,4},{4,5,6,6},{7,8,9,6},{1,2,3,4}};

int main()
{

    int n = 4;
    for(int i=0; i<n; i++)
    {
        int tmp = i;
        for(int j=0; j<=i; j++)
        {
            cout<<a[tmp][j]<<" ";
            tmp--;
        }
        cout<<endl;
    }
    int coltmp = 1; 
    for(int i=n-1; i>0; i--)
    {
        int tmp = n-1;
        int tmp1 = coltmp;
        for(int j=0; j<i; j++)
        {
            //cout<<"i:"<<i<<"j:"<<j;
            cout<<a[tmp][tmp1]<<" ";
            tmp--;
            tmp1++;
        }
        cout<<endl;
        coltmp++;
    }
}