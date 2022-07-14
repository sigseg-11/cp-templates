#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class SegTree {
   public:
    ll N;
    vector<ll> arr;
    struct node { // TODO
        ll mn, mx, sm; 
        ll lazy = 0;

        node(){   // TODO
            mn = INT_MAX;
            mx = INT_MIN;
            sm = 0;
            lazy = 0;
        }
    };

    vector<node> st;

    SegTree(vector<ll> on){
        N = int(on.size());
        arr.resize(N);
        arr = on;
        st.resize(4*N);
        build(0, N - 1, 1);
    }

    node node_combiner(node left, node right) { //TODO
        node ans;
        ans.sm = (left.sm + right.sm);  
        return ans;
    }

    void node_setter(node &n, ll idx){ //TODO
        n.sm = arr[idx];
    }

    void node_updater(node &n, ll val){ //TODO
        n.sm = val;
    }
    void node_lazy_updater(node &n, ll val){ //TODO
        n.lazy = val;
    }

    void push(ll ss, ll se, ll idx, ll val) {
        node_updater(st[idx], val);                         
        if (ss != se) {
            node_lazy_updater(st[2 * idx], val);
            node_lazy_updater(st[2 * idx + 1], val);
        }
    }
    void push_lazy(node &n, ll ss, ll se, ll idx){ //TODO
        if (n.lazy != 0) {
            push(ss, se, idx, n.lazy);
            n.lazy = 0;
        }
    }

    void build(ll ss, ll se, ll idx) {
        if (ss == se) {
            node_setter(st[idx], ss);
            return;
        }
        ll mid = (ss + se) / 2;
        build(ss, mid, 2 * idx);
        build(mid + 1, se, 2 * idx + 1);
        st[idx] = node_combiner(st[2 * idx], st[2 * idx + 1]);
        return;
    }

    void update(ll ss, ll se, ll us, ll ue, ll val, ll idx) {
        push_lazy(st[idx], ss, se, idx);
        if (ue < ss or se < us) {
            return;
        }
        if (ss >= us and se <= ue) {
            push(ss, se, idx, val);
            return;
        }
        ll mid = (ss + se) / 2;
        update(ss, mid, us, ue, val, 2 * idx);
        update(mid + 1, se, us, ue, val, 2 * idx + 1);
        st[idx] = node_combiner(st[2 * idx], st[2 * idx + 1]);
        return;
    }

    node query(ll ss, ll se, ll qs, ll qe, ll idx) {
        push_lazy(st[idx], ss, se, idx);
        if (ss >= qs && se <= qe) {
            return st[idx];
        }
        if (qe < ss or qs > se) {
            node nullNode;
            return nullNode;
        }
        ll mid = (ss + se) / 2;
        node left = query(ss, mid, qs, min(mid, qe), 2 * idx);
        node right = query(mid + 1, se, max(mid + 1, qs), qe, 2 * idx + 1);
        return node_combiner(left, right);
    }

    void update(ll l, ll r, ll val){ // 0 index
        update(0, N - 1, l, r, val, 1);
        return;
    }

    node query(ll l, ll r){ // 0 index
        return query(0, N - 1, l, r, 1);
    }
};

int32_t main() {
    int n, q;
    cin >> n >> q;
    vector<ll> arr(n,0);
    for (int i = 0; i < (n); ++i) {
        cin >> arr[i];
    }
    
    SegTree st(arr);
    
    while(q--){
        int t;
         cin>>t;
         if(t==1){
             int k, u;
             cin>>k>>u;
             --k;
             st.update(k, k, u);
         }else{
            int a, b;
            cin>>a>>b;
            --a, --b;
            std::cout << st.query(a, b).sm << std::endl;
         }
    }
    return 0;
}