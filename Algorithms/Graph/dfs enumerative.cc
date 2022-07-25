const int NOS;

struct state{
	int id, val;
	vector<state*> link;
};

unordered_map<state, int> visited;

int dfs(state s, state p){
	for(int i = 0; i < s.link.size(); ++i){
		if(visited.count(state)==false){
			dfs(s.link[i], s);
		}
	}
}