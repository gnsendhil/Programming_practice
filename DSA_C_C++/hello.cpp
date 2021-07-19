/* Hacker Rank - Dynamic Array */
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, num_queries;
    int q_type, x, y;
    cin>>n;
    cin>>num_queries;
    vector<int> arr[n];
    vector<int> lastanswersarr;
    int lastanswer = 0;
    for(int i=0; i<num_queries; i++)
    {
        int idx;
        cin>>q_type;
        cin>>x;
        cin>>y;
        idx = (x ^ lastanswer) % n;
        if(q_type == 1)
        {
            arr[idx].push_back(y);
        }
        else if (q_type == 2)
        {
            lastanswer = arr[idx][y% arr[idx].size()];
            lastanswersarr.push_back(lastanswer);
            printf("%d\n", lastanswer);
        }

    }

}