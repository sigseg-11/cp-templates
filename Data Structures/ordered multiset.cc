class ordered_multiset {
   public:
    tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag,
         tree_order_statistics_node_update>
        omset;
    vector<ll> on;
    int N;

    ordered_multiset() { N = 0;}

    void insert(int x) {
        N++;
        omset.insert({x, N});
        on.push_back(x); // Value inserted at i pos
    }

    ll size(){
        return N;
    }

    ll kthLargestValue(int k) { return (*omset.find_by_order(k)).first; }

    ll countLT(int x) { return omset.order_of_key({x, LLONG_MIN}); }

    ll countET(int x) {
        auto p1 = omset.lower_bound({x, LLONG_MIN});
        auto p2 = omset.upper_bound({x, LLONG_MAX});
        return distance(p1, p2);
    }

    void eraseByValue(int v) {
        int rank = omset.order_of_key({v, LLONG_MIN});
        auto it = omset.find_by_order(rank);
        if (it != omset.end()) omset.erase(it);
    }

    void eraseByIndex(int i) {
        int rank = omset.order_of_key({on[i], i});
        auto it = omset.find_by_order(rank);
        if (it != omset.end()) omset.erase(it);
    }

    void print() {
        for (auto it = omset.begin(); it != omset.end(); it++) {
            cout << (*it).first << " ";
        }
        cout << endl;
        for (auto it = omset.begin(); it != omset.end(); it++) {
            cout << (*it).second << " ";
        }
        cout << endl;
    }
};
