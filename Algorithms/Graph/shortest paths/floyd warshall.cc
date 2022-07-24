#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define tll tuple<ll, ll,ll>
const int NOV = 5 , NOE = 8;
int dist[NOV][NOV];
int par[NOV][NOV]; // Priting Shortest Path
int reach[NOV][NOV]; // Transitive Closure
int smallCycle[NOV][NOV]; // smallCycle[i][i] = Cost of cheapest cycle that contains i

// Priting Shortest Path
void printPath(int i, int j){
    if(i!=j) printPath(i, par[i][j]);
    cout << j << " ";
}

// How to pass 2d and 1d arrays
template <size_t r, size_t c>
void print(int (&arr)[r][c]){
    for (int i = 0; i < NOV; i++) {
        for (int j = 0; j < NOV; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

void folydWarshall(){ 
    // Initilizing parent and dist array 
    for (int i = 0; i < NOV; i++) {
        for (int j = 0; j < NOV; j++){
            if(i!=j) dist[i][j] = 1e9;
            par[i][j] = i;
            smallCycle[i][j] = 1e9;
        }
    }
    // Taking Input and Updating dist
    for (int i = 0; i < NOE; i++) {
        int u, v, wt; cin >> u >> v >> wt;
        dist[u][v] = min(dist[u][v], wt);
        smallCycle[u][v] = min(smallCycle[u][v], wt);
        reach[u][v] = 1;
    }
    // k, i, j, and dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int k = 0; k < NOV; k++) 
        for (int i = 0; i < NOV; i++) 
            for (int j = 0; j < NOV; j++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    par[i][j] = par[k][j]; // Keeping parent or dist[i][j] = dist[i][k] + dist[k][j];
                }
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                smallCycle[i][j] = min(smallCycle[i][j], smallCycle[i][k] + smallCycle[k][j]);
                reach[i][j] = reach[i][j] | (reach[i][k] & reach[k][j]);
            }
                
    // smallCycle[i][i] = Cost of cheapest cycle that contains i
    // cheapest cycle : i=0 to i=NOV ans = min(ans, smallCycle[i][i])
    // if cheapest cycle is -ve then -ve cycle exists : if(ans<0) yes
    // Longest (Shortest Path b/w i and j) : 
    // dist[i][j] = smallest dist from i to j
    // reach[i][j] = is j is reachable from i
    
    print(dist);
    print(reach);
    print(par);
    print(smallCycle);
}

int main(){
    folydWarshall();
}