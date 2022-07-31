#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> g;
vector<vector<int>> cmponent;
vector<int> topo;

int NOE, NOV;

void graph(int noe, int nov){
	NOE = noe, NOV = nov;
	g.resize(NOV, vector<T>());
}

void add_edge(int v, int u){
	g[v].push_back(u);
	// g[u].push_back(v);
}

void dfs(int node, int cid){
    cmponent[node] = cid;
    // Before dfsing any neighbour
    for (auto ngh : graph[node]) {
        if(!cmponent[ngh]) {
            // Before dfsing ngh neighbour
            dfs(ngh, cid);
            // After dfsing ngh neighbour
        }
    }
    // After dfsing all neighbour
    topo.push_back(node);
}

void component(){
	int ccnt = 0;
    for (int i = 0; i < NOV; i++) {
        if(!vis[i]) ++ccnt, dfs(i, ccnt); // order matters
    }
}
