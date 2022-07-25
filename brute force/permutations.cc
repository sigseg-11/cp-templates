template<typename T>
vector<vector<T>> permute(vector<T> on, bool distinct = true){
	int _N = int(on.size());
	vector<vector<T>> ans(_N);
	if(distinct==false){
		vector<pair<T, int>> _on(N);
		for (int i = 0; i < _N; ++i) {
			_on[i] = {on[i], i};
		}
		sort(begin(_on), end(_on));
		int row = 0;
		do{
			ans[row++] = _on;
		}while(next_permutation(begin(_on), end(_on)));
	}else{
		sort(begin(on), end(on));
		int row = 0;
		do{
			ans[row++] = on;
		}while(next_permutation(begin(on), end(on)));
	}
	return ans;
}