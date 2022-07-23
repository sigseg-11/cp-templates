#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// References:
//   <https://cp-algorithms.com/graph/hld.html>
//   <https://codeforces.com/blog/entry/53170>
//   <https://ei1333.github.io/luzhiled/snippets/tree/heavy-light-decomposition.html>
//   <https://atcoder.jp/contests/past202010-open/submissions/21473312>
//   <https://math314.hateblo.jp/entry/2014/06/24/220107>
//   <https://qiita.com/Pro_ktmr/items/4e1e051ea0561772afa3>

// HL Decomposition
// --Notes when giving initial values (not identity elements) to vertices
// --Do it after executing hld.build ()
// --Note that the vertex u is hld.in [u] inside hld.
// --If there is a value on the side, give it to the vertex on the child side and call the function with edge = true
// ToDo
using S = set<int>;
S op(S a, S b) { if(a.size()<b.size()) swap(a, b); for(auto i: a) b.insert(i); return b;}
S e() { set<int> s; return s; }

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = 0;
        while ((1U << log) < (unsigned int)(_n)) log++;
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

struct HLD {
    int N, root;
    vector<vector<int>> G;
    vector<int> parent;  // Parent of vertex u
    vector<int> depth;  // Depth of vertex u
    vector<int> sz;  // The size of the subtree rooted at vertex u (heavy)
    vector<int> in;  // Search order during HL decomposition (Euler Tour)
    vector<int> out;  // See below
    vector<int> head;  // The root of the connected component after HL decomposition to which the vertex u belongs
    vector<int> rev;  // Reverse lookup from search sequence number to original vertex number
    int t = 0;  // For calculation of search order


    // [ in[u], out[u] )      := Corresponds to subtrees rooted at vertex u
    // [ in[head[u]], in[u] ] := Corresponds to the path from vertex u to its head in the connected component after HL decomposition

    HLD() {}
    HLD(int n, int r = 0) : N(n), root(r) {
        G.resize(N); parent.resize(N); depth.resize(N); sz.resize(N);
        in.resize(N); out.resize(N); head.resize(N); rev.resize(N);
    }

    // Stretch sides in both directions
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    // Find the size of each subtree
    void dfs_sz(int u, int p, int d) {
        parent[u] = p;
        depth[u] = d;
        sz[u] = 1;
        // Search while keeping the heavy edge at the beginning
        if (G[u].size() && G[u][0] == p) swap(G[u][0], G[u].back());
        for (int& v : G[u]) if (v != p) {  // NOTE: swap のために int& が必要
            dfs_sz(v, u, d + 1);
            sz[u] += sz[v];
            if (sz[G[u][0]] < sz[v]) swap(G[u][0], v);
        }
    }

    // HL Decomposition
    void dfs_hld(int u, int p) {
        in[u] = t++;
        rev[in[u]] = u;
        for (const int& v : G[u]) if (v != p) {
            head[v] = (v == G[u][0] ? head[u] : v);  // heavy or light
            dfs_hld(v, u);
        }
        out[u] = t;
    }

    void build() {
        dfs_sz(root, -1, 0);
        dfs_hld(root, -1);
    }

    // Follow the parent by depth d from vertex u (level-ancestor): O (log N)
    // It is assumed that the destination is on the tree
    //   - d <= depth[u]
    int la(int u, int d) const {
        assert(0 <= u && u < N);
        while (true) {
            int v = head[u];
            if (in[u] - d >= in[v]) return rev[in[u] - d];
            d -= in[u] - in[v] + 1;
            u = parent[v];
        }
    }

    // LCA of vertices u, v: O (log N)
    int lca(int u, int v) const {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        while (true) {
            if (in[u] > in[v]) swap(u, v);  // in[u] <= in[v]  (u が根側)
            if (head[u] == head[v]) return u;
            v = parent[head[v]];
        }
    }

    // (u, v) Number of edges between paths: O (log N)
    int distance(int u, int v) const {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return depth[u] + depth[v] - 2*depth[lca(u, v)];
    }

    // Does vertex w exist on the (u, v) path: O (log N)
    bool on_path(int u, int v, int w) const {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        assert(0 <= w && w < N);
        return distance(u, w) + distance(w, v) == distance(u, v);
    }

    // Update query for path [u, v]: O ((log N) ^ 2)
    template<class F>
    void apply_path(int u, int v, bool edge, const F& func) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        while (true) {
            if (in[u] > in[v]) swap(u, v);  // in[u] <= in[v]  (u が根側)
            if (head[u] == head[v]) break;
            func(in[head[v]], in[v]);
            v = parent[head[v]];
        }
        func(in[u] + edge, in[v]);
    }

    // Get query for path [u, v]: O ((log N) ^ 2)
    template <class S, S (*op)(S, S), S (*e)(), class F>
    S prod_path(int u, int v, bool edge, const F& func) const {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        S Su = e(), Sv = e();
        while (true) {
            if (in[u] > in[v]) { swap(u, v); swap(Su, Sv); }  // in[u] <= in[v]  (u が根側)
            if (head[u] == head[v]) break;
            Sv = op(Sv, func(in[head[v]], in[v]));
            v = parent[head[v]];
        }
        return op(Su, op(Sv, func(in[u] + edge, in[v])));
    }

    // Update query for subtree rooted at vertex u: O (log N)
    void apply_subtree(int u, bool edge, function<void(int, int)> func) {
        assert(0 <= u && u < N);
        func(in[u] + edge, out[u] - 1);
    }

    // Get query for subtree rooted at vertex u: O (log N)
    template <class S>
    S prod_subtree(int u, bool edge, function<S(int, int)> func) const {
        assert(0 <= u && u < N);
        return func(in[u] + edge, out[u] - 1);
    }
};

class HeavyLight{
    public:
    HLD hld;
    bool edge;
    segtree<S, op, e> seg;
    HeavyLight(vector<vector<int>> t, vector<int> val, bool Edge){
        int NOV = t.size();
        edge = Edge;
        HLD thld(NOV, 0);
        for(int i=0; i<NOV; i++){
            for (int j = 0; j < int(t[i].size()); j++) {
                thld.add_edge(i, t[i][j]);
            }
        }
        thld.build();
        vector<S> X(NOV); // ToDo
        for (int i = 0; i < NOV; i++) {
            X[thld.in[i]].insert(val[i]); // ToDo
        }
        segtree<S, op, e> tseg(X);
        hld = thld;
        seg = tseg;
    }
    
    S queryPath(int u, int v){
        return hld.prod_path<S,op,e>(u, v, edge, [&](int l, int r) {return seg.prod(l, r+1);});
    }
    
    // void updatePath(int u, int v, S x){
    //     x -= queryPath(u, v);
    //     hld.apply_path(u, v, edge, [&](int l, [[maybe_unused]] int r) {seg.set(l, seg.get(l) + x);});
    // }
    
    S querySubtree(int v){
        return hld.prod_subtree<S>(v,edge, [&](int l, int r) {return seg.prod(l, r+1);});
    }

    // void updateSubtree(int v, S x){ // ToDo
    //     return hld.apply_subtree(v, edge, [&](int l, [[maybe_unused]] int r) {seg.set(l, seg.get(l) + x);});
    // }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N;
    vector<int> A(N); for(int i=0;i<N; ++i) cin >> A[i];
    
    vector<vector<int>> t(N);
    for(int i=0;i<N-1; ++i) {
        ll u, v; cin >> u >> v;
        u--; v--;
        t[u].push_back(v);
    }
    bool edge = false;
    
    HeavyLight hl(t, A, edge);


    for (int i = 0; i < N; i++) {
        std::cout << hl.querySubtree(i).size() << std::endl;
    }

    return 0;
}
// Verify: https://judge.yosupo.jp/problem/vertex_add_path_sum
