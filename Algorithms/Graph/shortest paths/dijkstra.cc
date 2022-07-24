#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define ff first
#define ss second

const int NOV = 3, NOE = 5;
vector<pll> graph[NOV];
vector<ll> dist(NOV, int(1e18)), vis(NOV, false); 

class prioritize{
    public: bool operator()(pll &p1, pll &p2) {return p1.ss > p2.ss;}
};

void dijkstra(int sc){
    dist[sc] = 0;
    priority_queue<pll, vector<pll>, prioritize> pq;
    
    pq.push({sc,0});
    
    while(!pq.empty()){
        auto fs = pq.top(); pq.pop();
        // optimization not necessary
        if(vis[fs.ff]) continue;
        vis[fs.ff] = 1;
        
        for (auto i : graph[fs.ff]) {
            int ngh = i.ff, wt = i.ss;
            if(dist[ngh]>dist[ngh]+wt){ // regular relaxatation
                dist[ngh]=dist[ngh]+wt;
                pq.push({ngh, dist[ngh]});
            }
        }
    }
}

int main(){
    for (int i = 0; i < NOE; i++) {
        int u, v, wt;
        cin>>u>>v>>wt;
        graph[u].push_back({v, wt});
        graph[v].push_back({u, wt});
    }
    
    dijkstra(0);
    
    cout << dist[NOV-1] << endl;
}