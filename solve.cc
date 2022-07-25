/*
The expert at anything was once a beginner.
*/

// #pragma comment(linker, "/stack:200000000")
// #pragma GCC optimize("Ofast,unroll-loops,tree-vectorize")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")

#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using ll = long long;
#define all(x) (x).begin(), (x).end()
#define rep(x, a, b) for(ll (x) = (a); (x) < (b); ++(x))
#define sz(x) ((int)x.size())
#define ub(v,x) upper_bound(all(v),x)
#define lb(v,x) lower_bound(all(v),x)
#define pb push_back
#define ff first
#define ss second

#define vll vector<ll>
#define pll pair<ll,ll>
#define tll tuple<ll, ll, ll>
#define readv(v) rep(i, 0, sz(v)){cin>>v[i];}
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using omset = tree<pair<T,int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;

// Debug 1
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A, typename B, typename C> ostream& operator<<(ostream &os, const tuple<A, B, C> &p) { return os << '(' << get<0>(p) << ", " << get<1>(p) << ", " << get<2>(p) << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> T rint(T a, T b) { return uniform_int_distribution<T>(a, b)(mt_rng);}
vector<long long> rvector(int N, int l, int r) { vector<long long> v(N); generate(v.begin(), v.end(), [&](){ return rint<long long>(l, r); }); return v;}

// Exponentiation
#define MOD int(1e9+7)
ll mpow(ll a, ll b, ll m = MOD) { a %= m;ll res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1;}return res;}
ll pow(ll a, ll b) {ll res = 1;while (b > 0) {if (b & 1)res = res * a;a = a * a;b >>= 1;}return res;}
inline ll gcd(int a, int b){return b==0 ? a : gcd(b, a%b);}
inline ll lcm(int a, int b){return (a*1LL*b)/gcd(a,b);}
inline tll ee(ll a, ll b){if(b==0) return {a, 1, 0};int d, x, y; tie(d, x, y) = ee(b, a%b);return {d, y, x - (a/b)*y};}
inline ll add(ll a, ll b){return (a%MOD + b%MOD)%MOD;}
inline ll sub(ll a, ll b){return (a%MOD - b%MOD)%MOD;}
inline ll mul(ll a, ll b){return (a%MOD *1LL* b%MOD)%MOD;}
inline ll divi(ll a, ll b){return mul(a, pow(b, MOD-2));}

// Moves
int dxk[8] ={2,2,-2,-2,1,1,-1,-1};
int dyk[8] ={1,-1,1,-1,2,-2,2,-2};
// Solve
void seive(){}

void btfc(){
    
}
// Solution

void solve(){
    
    return;
}


int main(){
    ios::sync_with_stdio(0^0); cin.tie(nullptr);
    
    // seive();
    
    // btfc();
    
    // int testcases; cin>>testcases; while(testcases--) solve();
    
    solve();

    return EXIT_SUCCESS;
}

