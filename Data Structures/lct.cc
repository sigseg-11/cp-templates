/*
The expert at anything was once a beginner.
*/

#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using ll = long long;
#define MOD int(1e9+7)
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

typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> oset;
// Debug 1
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A, typename B, typename C> ostream& operator<<(ostream &os, const tuple<A, B, C> &p) { return os << '(' << get<0>(p) << ", " << get<1>(p) << ", " << get<2>(p) << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
// Debug 2
template <typename T> T randint(ll a, ll b) { return uniform_int_distribution<T>(a, b)(mt_rng);}
vector<ll> randv(int N,int l, int r) { vector<ll> v(N); generate(v.begin(), v.end(), [&](){ return randint<ll>(l, r); }); return v;}
// Exponentiation
ll pow(ll a, ll b, ll m = MOD) { a %= m;ll res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1;}return res;}
// Mod
inline ll gcd(int a, int b){return b==0 ? a : gcd(b, a%b);}
inline tll ee(ll a, ll b){if(b==0) return {a, 1, 0};int d, x, y; tie(d, x, y) = ee(b, a%b);return {d, y, x - (a/b)*y};}
inline ll add(ll a, ll b){return (a%MOD + b%MOD)%MOD;}
inline ll sub(ll a, ll b){return (a%MOD - b%MOD)%MOD;}
inline ll mul(ll a, ll b){return (a%MOD *1LL* b%MOD)%MOD;}
inline ll divi(ll a, ll b){return mul(a, pow(b, MOD-2));}

// Moves
int dxk[8] ={2,2,-2,-2,1,1,-1,-1};
int dyk[8] ={1,-1,1,-1,2,-2,2,-2};
// Solve
struct node {
  int p = 0, c[2] = {0, 0}, pp = 0;
  bool flip = 0;
  // ToDo
  int sz = 0, ssz = 0, vsz = 0; // sz -> aux tree size, ssz = subtree size in rep tree, vsz = virtual tree size
  long long val = 0, sum = 0, lazy = 0, subsum = 0, vsum = 0;
  node() {}
  node(int x) {
    // ToDo
    val = x; sum = x;
    sz = 1; lazy = 0;
    ssz = 1; vsz = 0;
    subsum = x; vsum = 0;
  }
};
struct LCT {
  vector<node> t;
  LCT() {}
  LCT(int n) : t(n + 1) {}

  // <independant splay tree code>
  int dir(int x, int y) { return t[x].c[1] == y; }
  void set(int x, int d, int y) {
    if (x) t[x].c[d] = y, pull(x);
    if (y) t[y].p = x;
  }
  void pull(int x) {
    if (!x) return;
    int &l = t[x].c[0], &r = t[x].c[1];
    // ToDo
    t[x].sum = t[l].sum + t[r].sum + t[x].val;
    t[x].sz = t[l].sz + t[r].sz + 1;
    t[x].ssz = t[l].ssz + t[r].ssz + t[x].vsz + 1;
    t[x].subsum = t[l].subsum + t[r].subsum + t[x].vsum + t[x].val;
  }
  void push(int x) { 
    if (!x) return;
    int &l = t[x].c[0], &r = t[x].c[1];
    if (t[x].flip) {
      swap(l, r); 
      if (l) t[l].flip ^= 1; 
      if (r) t[r].flip ^= 1;
      t[x].flip = 0;
    }
    if (t[x].lazy) {
      // ToDo
      t[x].val += t[x].lazy;
      t[x].sum += t[x].lazy * t[x].sz;
      t[x].subsum += t[x].lazy * t[x].ssz;
      t[x].vsum += t[x].lazy * t[x].vsz;
      if (l) t[l].lazy += t[x].lazy;
      if (r) t[r].lazy += t[x].lazy;
      t[x].lazy = 0;
    }
  }
  void rotate(int x, int d) { 
    int y = t[x].p, z = t[y].p, w = t[x].c[d];
    swap(t[x].pp, t[y].pp);
    set(y, !d, w);
    set(x, d, y);
    set(z, dir(z, y), x);
  }
  void splay(int x) { 
    for (push(x); t[x].p;) {
      int y = t[x].p, z = t[y].p;
      push(z); push(y); push(x);
      int dx = dir(y, x), dy = dir(z, y);
      if (!z) rotate(x, !dx); 
      else if (dx == dy) rotate(y, !dx), rotate(x, !dx); 
      else rotate(x, dy), rotate(x, dx);
    }
  }
  // </independant splay tree code>

  // making it a root in the rep. tree
  void make_root(int u) {
    access(u);
    int l = t[u].c[0];
    t[l].flip ^= 1;
    swap(t[l].p, t[l].pp);
    t[u].vsz += t[l].ssz;
    t[u].vsum += t[l].subsum;
    set(u, 0, 0);
  }
  // make the path from root to u a preferred path
  // returns last path-parent of a node as it moves up the tree
  int access(int _u) {
    int last = _u;
    for (int v = 0, u = _u; u; u = t[v = u].pp) {
      splay(u); splay(v);
      t[u].vsz -= t[v].ssz;
      t[u].vsum -= t[v].subsum;
      int r = t[u].c[1];
      t[u].vsz += t[r].ssz;
      t[u].vsum += t[r].subsum;
      t[v].pp = 0;
      swap(t[r].p, t[r].pp);
      set(u, 1, v);
      last = u;
    }
    splay(_u);
    return last;
  }
  void link(int u, int v) { // u -> v
    // assert(!connected(u, v));
    make_root(v);
    access(u); splay(u);
    t[v].pp = u;
    t[u].vsz += t[v].ssz;
    t[u].vsum += t[v].subsum;
  }
  void cut(int u) { // cut par[u] -> u, u is non root vertex
    access(u);
    assert(t[u].c[0] != 0);
    t[t[u].c[0]].p = 0;
    t[u].c[0] = 0;
    pull(u);
  }
  // parent of u in the rep. tree
  int get_parent(int u) {
    access(u); splay(u); push(u);
    u = t[u].c[0]; push(u);
    while (t[u].c[1]) {
      u = t[u].c[1]; push(u);
    }
    splay(u);
    return u;
  }
  // root of the rep. tree containing this node
  int find_root(int u) {
    access(u); splay(u); push(u);
    while (t[u].c[0]) {
      u = t[u].c[0]; push(u);
    }
    splay(u);
    return u;
  }
  bool connected(int u, int v) {
    return find_root(u) == find_root(v);
  }
  // depth in the rep. tree
  int depth(int u) {
    access(u); splay(u);
    return t[u].sz;
  }
  int lca(int u, int v) {
    // assert(connected(u, v));
    if (u == v) return u;
    if (depth(u) > depth(v)) swap(u, v);
    access(v); 
    return access(u);
  }
  int is_root(int u) {
    return get_parent(u) == 0;
  }
  int component_size(int u) {
    return t[find_root(u)].ssz;
  }
  int subtree_size(int u) {
    int p = get_parent(u);
    if (p == 0) {
      return component_size(u);
    }
    cut(u);
    int ans = component_size(u);
    link(p, u);
    return ans;
  }
  long long component_sum(int u) {
    return t[find_root(u)].subsum;
  }
  long long subtree_sum(int u) {
    int p = get_parent(u);
    if (p == 0) {
      return component_sum(u);
    }
    cut(u);
    long long ans = component_sum(u);
    link(p, u);
    return ans;
  }
  // sum of the subtree of u when root is specified
  long long subtree_query(int u, int root) {
    int cur = find_root(u);
    make_root(root);
    long long ans = subtree_sum(u);
    make_root(cur);
    return ans;
  }
  // path sum
  long long query(int u, int v) {
    int cur = find_root(u);
    make_root(u); access(v);
    long long ans = t[v].sum;
    make_root(cur);
    return ans;
  }
  void upd(int u, int x) {
    access(u); splay(u);
    t[u].val += x;
  }
  // add x to the nodes on the path from u to v
  void upd(int u, int v, int x) {
    int cur = find_root(u);
    make_root(u); access(v);
    t[v].lazy += x;
    make_root(cur);
  }
};

void solve(){
    int n, q;
    cin>>n>>q;
    LCT l(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin>>x;
        l.upd(i, x);
    }
    for (int i = 0; i < n-1; ++i)
    {
        int u, v;
        cin>>u>>v;
        --u, --v;
        l.link(u, v);
    }
    while(q--){
        int  ty;
        cin>>ty;
        if(ty==2){
            int u;
            cin>>u;
            --u;
            cout<<l.subtree_sum(u)<<endl;
        }else{
            int u, x;
            cin>>u>>x;
            --u;
            int s = l.query(u, u);
            l.upd(u, -s);
            l.upd(u, x);
        }
    }
    
}


int main(){
    ios::sync_with_stdio(0^0); cin.tie(nullptr);
    
    // seive();
    
    // btfc();
    
    // int testcases; cin>>testcases; while(testcases--) solve();
    
    solve();

    return EXIT_SUCCESS;
}

