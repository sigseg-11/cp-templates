ll op(ll a, ll b){
	return __gcd(a, b); // TODO
}

vector<ll> prefix(vector<ll> on){
	int N = int(on.size());
	vector<ll> ans(N);
	ans[0] = on[0];
	for(int i=1; i<N; ++i){
		ans[i] = op(ans[i-1], on[i]); 
	}
	return ans;
}


vector<ll> suffix(vector<ll> on){
	int N = int(on.size());
	vector<ll> ans(N);
	ans[N-1] = on[N-1];
	for(int i=N-2; ~i; --i){
		ans[i] = op(ans[i-1], on[i]); 
	}
	return ans;
}


vector<ll> pre = prefix(arr), suff = suffix(arr);

ll getWithout(int idx){
	return op(pre[idx-1], suff[idx+1]);
}