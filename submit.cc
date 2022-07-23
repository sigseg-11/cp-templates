/*
The expert at anything was once a beginner.
*/

#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

using ll = long long;
#define MOD int(1e9+7)
#define all(x) (x).begin(), (x).end()
#define rep(x, a, b) for(ll (x) = (a); (x) < (b); ++(x))
#define repx(x) for(ll i = 0; i < x; ++i)
#define sz(x) ((int)x.size())
#define ub(v,x) upper_bound(all(v),x)
#define lb(v,x) lower_bound(all(v),x)
#define pb push_back
#define ff first
#define ss second

#define vll vector<ll>
#define pll pair<ll,ll>
#define tll tuple<ll, ll, ll>
#define readvus(v, n) rep(i, 0, n-1){int x;cin>>x;v.pb(x);}
#define readvs(v) rep(i, 0, sz(v)-1){cin>>v[i];}

// typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> oset;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> T randint(ll a, ll b) { return uniform_int_distribution<T>(a, b)(mt_rng);}
template <typename T> vector<T> randv(int N,int l, int r) {
    vector<T> v(N); 
    generate(v.begin(), v.end(), [&](){ return randint<T>(l, r); });
    return v;
}
// Exponentiation
ll pow(ll a, ll b, ll m = MOD) { a %= m;ll res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1;}return res;}
// Mod
inline ll gcd(int a, int b){return b==0 ? a : gcd(b, a%b);}
inline ll add(ll a, ll b){return (a%MOD + b%MOD)%MOD;}
inline ll sub(ll a, ll b){return (a%MOD - b%MOD)%MOD;}
inline ll mul(ll a, ll b){return (a%MOD *1LL* b%MOD)%MOD;}
inline ll divi(ll a, ll b){return mul(a, pow(b, MOD-2));}

/*

1≤A,B≤M

gcd(A,B)≥N

max(|A-B|)

M>=N
gcd(A,B)≥N



*/


pll brute(int n, int m){
    int val = INT_MIN;
    pll p;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if(abs(i-j)>val and gcd(i, j)>=n){
                val = abs(i-j);
                p = {i, j};
            }
        }
    }
    return p;
}


bool e(int i, int j){
    return brute(i, j).ff ==i or brute(i, j).ff ==i+1 or  brute(i, j).ff == i + 2;
    
}
void seive(){
    // for (int i = 1; i < 70; i++) 
    
    {
        int i= 2;
        for (int j = 2; j < int(1000); j++) {
            if(i<=j){
                dbg_out(i, j, "=>", gcd(i, j),"Ans", brute(i, j), "check",e(i, j) );
                if(!e(i, j)){
                    dbg_out(i, j, "=>", gcd(i, j),"Ans", brute(i, j), "check",e(i, j) );
                }
            }
        }
    }
}

void solve(){
    int n, m;
    cin>>n>>m;
    // pll p=brute(n,m);
    // cout<<p.ff << " "<< p.ss<<endl;
    
    if(n==m){
        std::cout << n <<" "<< m << std::endl;
        return;
    }
    if(gcd(n,m)==1){
        std::cout << n <<" "<< n << std::endl;
        return;
    }
    
    int val = INT_MIN;
    pll p;
    p.ff = n;
    for (ll i = p.ff; i <= m; i+=p.ff) {
        if(abs(i-p.ff)>val and __gcd(p.ff,i)>=n){
            val = abs(i-p.ff);
            p.ss = i;
        }
    }
    cout<<p.ff << " "<< p.ss<<endl;
    
}


int main(){
    ios::sync_with_stdio(0^0); cin.tie(nullptr);
    
    seive();
    
    // int testcases; cin>>testcases; while(testcases--) 
    // solve();

    return EXIT_SUCCESS;
}