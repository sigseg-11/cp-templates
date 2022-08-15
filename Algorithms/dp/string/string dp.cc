// dp[i][j] = the longest common sub-sequence length ending in A[i], B[j].
// dp[i][j] = A[i] == B[j] ? dp[i-1][j-1]+1 : max(dp[i-1][j], dp[i][j-1]);
// FRFC Zero Filling

// dp[i][j] = the longest common sub-string length ending in A[i], B[j].
// dp[i][j] = A[i] == B[j] ? dp[i-1][j-1]+1 : 0;
// FRFC Zero Filling

// dp[i][j] is the shortest edit distance ending in A[i], B[j].
// dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + bool(A[i]==B[j]);
// FRFC N Filling

void longestCommonSubsequence(string A, string B){
	int S = A.size(), T = B.size();
	vector<vector<int>> dp(S+1, vector<int> (T+1, 0));
	for(int i=0; i<S; ++i){
		for(int j=0; j<T; ++j){
			dp[i][j] = A[i] == B[j] ? dp[i-1][j-1]+1 : max(dp[i-1][j], dp[i][j-1]);
		}
	}
}

void longestCommonSubstring(string A, string B){
	int S = A.size(), T = B.size();
	vector<vector<int>> dp(S+1, vector<int> (T+1, 0));
	for(int i=0; i<S; ++i){
		for(int j=0; j<T; ++j){
			dp[i][j] = A[i] == B[j] ? dp[i-1][j-1]+1 : 0;
		}
	}
}


void shortestEditDistance(string A, string B){
	int S = A.size(), T = B.size();
	vector<vector<int>> dp(S+1, vector<int> (T+1, 0));

	for(int i=0; i<S; ++i) dp[i][0] = i;
	for(int j=0; j<T; ++j) dp[0][j] = j;

	for(int i=0; i<S; ++i){
		for(int j=0; j<T; ++j){
			dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + bool(A[i]==B[j]);
		}
	}
}


int longestIncreasingSubsequence(vector<int> s){
    vector<int> r;
    for (auto c : s) {
        if(r.empty() or c>r.back()) 
             //Append to LIS if new element is >= last element in LIS
             r.push_back(c);
        else {
            // Find the index of the smallest number > x
            auto it = lower_bound(all(r), c);
            // Replace that number with x 
            *it = c;
        }
    }
    return r.size();
}

int longestNonDecreasingSubsequence(vector<int> s){
    vector<int> r;
    for (auto c : s) {
        if(r.empty() or c>r.back()) 
             //Append to LIS if new element is >= last element in LIS
             r.push_back(c);
        else {
            // Find the index of the smallest number > x
            auto it = upper_bound(all(r), c);
            // Replace that number with x 
            *it = c;
        }
    }
    return r.size();
}