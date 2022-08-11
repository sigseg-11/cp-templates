// [REV] Difference of sum of digits at even and odd position is Prime, 0<= L, R <= 1e18
#include <bits/stdc++.h>
using namespace std;
#define sz(x)  int(x.size())
#define ll long long int


string S;
int m[18][90][90][2];
unordered_set<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };


int dp(int p, int eps, int ops, int t){
    if(p==sz(S)){
        if(sz(S)&1) swap(ops, eps);
        return primes.find(eps-ops)!=primes.end() ? 1 : 0;
    }
    if(m[p][eps][ops][t]==-1){
        // int l = t ? stoi(S.substr(p,1)) : 9;
        int l = t ? S[p] - '0' : 9;
        int ans1 = 0;
        for (int d = 0; d <= l; d++) {
            ans1 += dp(p+1, p%2==0?eps+d:eps, p%2==1?ops+d:ops, t&(l==d)); // TLD Rule
        }
        m[p][eps][ops][t] = ans1;
    }
    return m[p][eps][ops][t];
}

int main(){
    ll l, r;
    cin>>l>>r, --l;

    memset(m, -1, sizeof(m));
    S = to_string(l);
    ll ansL = dp(0, 0, 0, 1);
    
    memset(m, -1, sizeof(m));
    S = to_string(r);
    ll ansR = dp(0, 0, 0, 1);
    
    cout << ansR - ansL << endl;
}