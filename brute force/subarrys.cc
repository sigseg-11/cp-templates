template<typename T>
T op(T a, T b){
	return min(a, b);
}
template<typename T>
vector<vector<T>> subarrays(vector<T> on){
	int N = on.size();
	vector<vector<T>> ans;
	for (int i = 0; i < N; ++i){
		for(int j = i; j < N; ++j){
		    vector<T> t;
		    for(int k=i; k<=j; k++) t.push_back(on[k]);
			ans.push_back(t);
			t.clear();
		}
	}
	return ans;
}