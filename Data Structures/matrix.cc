#include <bits/stdc++.h>
using namespace std;


// IO
ll row, col;
using matrix = vector<vector<ll>>;

matrix mat;
void read(){
	cin>>row>>col;
	mat.resize(row, vector<ll>(col));
	for(int i=0; i<row; ++i){
		for(int j=0; j<col; ++j){
			cin>>mat[i][j];
		}
	}
}
void write(){
	cout<<row<<" "<<col<<endl;
	for(int i=0; i<row; ++i){
		for(int j=0; j<col; ++j){
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}

// DFS

int di[8]={};
int dj[8]={};
vector<vector<bool>> visited;
visited.assign(vector<)

bool e(int i, int j){
	return i>=0 and j>=0 and i<row and j<col and visited[i][j]==false and mat[i][j]!=0;
}

void dfs(int i, int j){
	visited[i][j] = false;
	for (int k = 0; k < 8; ++k){
		int ni = i + di[k];
		int nj = j + dj[k];
		dfs(ni, nj);
	}
}


void dfs(int i, int j){
	int nSCC = 0;
	for (int i = 0; i < row; ++i){
		for (int j = 0; j < col; ++j){
			if(visited[i][j]==false){
				nSCC++;
				dfs(i, j);
			}
		}
	}
}

// BFS

void bfs(int i, int j){

}


// Operation

matrix add(matrix a, matrix b){
	assert(a.size()==b.size());
	assert(a[0].size()==b[0].size());

	matrix ans(a.size(), vector<ll> (a[0].size()));

	for(int i=0; i<row; ++i){
		for(int j=0; j<col; ++j){
			ans[i][j] = a[i][j] + b[i][j]; 
		}
	}
	return ans;
}