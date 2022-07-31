// Algorithm that constructs an array res [i] in linear time that represents the maximum number of characters that the prefix and suffix of S [0: i] match.
void border(const string& S, vector<int>& res){
    int n = (int)S.size(), j = 0;
    res.resize(n, 0);
    for(int i = 0; i < n-1; i++){
        while(S[i+1] != S[j] && --j >= 0) j = res[j];
        res[i+1] = ++j;
    }
}