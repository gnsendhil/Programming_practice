#include <bits/stdc++.h>
using namespace std;


void shortest_path(int num, vector<pair<int,int>> Graph[])
{
    int inf = (int)1e8;
    vector<int> Distance(num+1, inf);
    Distance[1] = 0;
    set<pair<int, int>> Queue;
    Queue.insert({0,1});
    while(!Queue.empty())
    {
        auto top = Queue.begin();
        //cout<<top->second<<endl;
        int index = top->second;
        //cout<<"index_pointer:"<<index<<endl;
        Queue.erase(top);
        for(auto next: Graph[index]){
            int v = next.first, cost = next.second;
            //cout<<"index:"<<next.first<<"cost:"<<cost<<"min_dist"<<Distance[index]<<endl;
            if (cost < Distance[index])
            {
                cost = 0;
            }
            else
            {
                cost = cost - Distance[index];
            }
            if( Distance[index] + cost < Distance[v] ) {
                if(Queue.find( {Distance[v],v})!=Queue.end())
                    Queue.erase(Queue.find( {Distance[v], v} ));
                Distance[v] = Distance[index] + cost;
                Queue.insert( {Distance[v], v} );
            }
        }
        //cout<<"index_pointer:"<<index<<endl;
        /*for(int i=0; i<=num; i++)
        {
            cout<<Distance[i]<<" ";
        }
        cout<<endl;*/
    }
    if(Distance[num] != inf)
        cout<<Distance[num];
    else
        cout<<"NOT POSSIBLE";

}

int main(){
    int num, R, Hi, Hj, C;

    cin >>num>>R;

    vector<pair<int, int> > *Graph = new vector<pair<int, int> > [num+1];

    for(int i=0; i<R; i++)
    {
        cin>>Hi>>Hj>>C;
        Graph[Hi].push_back(make_pair(Hj, C));
        Graph[Hj].push_back(make_pair(Hi, C));
    }

    /*for(int i=1; i<=num; i++ )
    {
        for(auto next: Graph[i])
        {
            cout<<i<<"->"<<next.first<<":"<<next.second;
            cout<<" ";
        }
        cout<<endl;
    }*/

    shortest_path(num, Graph);
}