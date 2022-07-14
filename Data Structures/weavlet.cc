#include <bits/stdc++.h>
using namespace std;

struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l, *r;
    vector<int> b;
    // nos are in range [x,y]
    // array indices are [from, to)
    wavelet_tree(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (lo == hi or from >= to) return;
        int mid = (lo + hi) / 2;
        auto f = [mid](int x) { return x <= mid; };
        b.reserve(to - from + 1);
        b.push_back(0);
        for (auto it = from; it != to; it++) b.push_back(b.back() + f(*it));
        // see how lambda function is used here
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid + 1, hi);
    }

    // kth smallest element in [l, r] => O(log)
    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        int inLeft = b[r] - b[l - 1];
        int lb = b[l - 1];  // amt of nos in first (l-1) nos that go in left
        int rb = b[r];      // amt of nos in first (r) nos that go in left
        if (k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }

    // count of nos in [l, r] Less than or equal to k => O(log)
    int LTE(int l, int r, int k) {
        if (l > r or k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }
    // count of nos in [l, r] greater than or equal to k => O(log)
    int GTE(int l, int r, int k) {
        return r - l + 1 - (LTE(l, r, k) - count(l, r, k));
    }

    // count of nos in [l, r] equal to k => O(log)
    int count(int l, int r, int k) {
        if (l > r or k < lo or k > hi) return 0;
        if (lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r], mid = (lo + hi) / 2;
        if (k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }
    //  count of elements [x,y] in [l,r] => O(log)
    int countRange(int x, int y, int l, int r) {
        //  std::cout << LTE(l,r,y) << " " << LTE(l,r,x-1) << std::endl;
        return LTE(l, r, y) - LTE(l, r, x - 1);
    }
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};

wavelet_tree *wavelet(vector<int> on) {
    int _N = int(on.size()), mn = INT_MAX, mx = INT_MIN;
    int iarr[_N];
    for (int i = 0; i < _N; ++i) {
        iarr[i] = on[i];
        mn = min(mn, iarr[i]);
        mx = max(mx, iarr[i]);
    }
    int *s = &iarr[0];
    int *e = &iarr[_N];
    return new wavelet_tree(s, e, mn, mx);
}

int main() {
    int n;
    cin >> n;

    vector<int> all(n);
    for (int i = 0; i < n; ++i) cin >> all[i];

    wavelet_tree *T = wavelet(all);

    int q;
    cin >> q;
    while (q--) {
        int x, l, r, k;
        cin >> x;
        cin >> l >> r >> k;
        if (x == 0) {
            // kth smallest element in range [l,r]
            cout << " Kth smallest:  ";
            cout << T->kth(l, r, k) << endl;
        }
        if (x == 1) {
            // find the no of elements less than or equal to K in range [l,r]
            cout << " LTE:  ";
            cout << T->LTE(l, r, k) << endl;
        }
        if (x == 2) {
            // freq of K in [l, r]
            cout << " Occurence of K:  ";
            cout << T->count(l, r, k) << endl;
        }
        if (x == 3) {
            int x = k, y;
            cin >> y;
            // find the no of elements between [x,y] to in range [l,r]
            cout << " Range Count:  ";
            std::cout << T->countRange(x, y, l, r) << std::endl;
        }
    }
    return 0;
}

/*5
1 2 3 4 5
4
0 2 5 3
1 1 5 2
2 1 5 4
3 1 5 1 5*/