#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define tll tuple<ll, ll,ll>
const int NOV = 5 , NOE = 8;
vector<tll> edge;
// vector<tll> edge(NOE); don't presize vector if using push_back
// for v-1 times relax all edges
// relax all edges 1 more time for -ve cycle i.e. vth time and if dist decreses => -ve cycle
vector<ll> dist(NOV, INT_MAX);

void bellmanford(int sc){ 
    // Set Source to zero
    dist[sc] = 0;
    // Relax graph all e, v-1 times
    for (int i = 1; i <= NOV - 1; i++) {
        for (int j = 0; j < NOE; j++) {
            int u = get<0>(edge[j]);
            int v = get<1>(edge[j]);
            int wt = get<2>(edge[j]);
            if (dist[u] != INT_MAX and dist[u] + wt < dist[v]) // presence of relaxatation denotes better lower path cost found
                dist[v] = dist[u] + wt; // update with lower cost
        }
    }
    // relax all e again if dist still decreses => -ve cycle
    for (int j = 0; j < NOE; j++) {
        int u = get<0>(edge[j]);
        int v = get<1>(edge[j]);
        int wt = get<2>(edge[j]);
        if (dist[u] != INT_MAX and dist[u] + wt < dist[v]) { // still after V-1 relaxatation, any relaxatation is found => -ve cycle
            printf("Graph contains negative weight cycle");
            return;
        }
    }
}

int main(){
    for(int i=0; i<NOE; ++i){
        int u, v, wt;
        cin>>u>>v>>wt;
        edge.push_back({u, v, wt});
    }

    bellmanford(0);
    
    for (int i = 0; i < NOV; i++) {
        cout << dist[i] << " ";
    }
}