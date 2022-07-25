// https://atcoder.github.io/ac-library/production/document_en/segtree.html
// https://atcoder.jp/contests/practice2/tasks/practice2_j

// Node
using S = int;
// Merge Node
S op(S a, S b) { return max(a, b); }
// Identity
S e() { return -1; }
// Binary Search Function
int target;
bool f(int v) { return v < target; }

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
    // If f is monotone, this is the maximum r that satisfies f(op(a[l], a[l + 1], ..., a[r - 1])) = true
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
    // If f is monotone, this is the minimum l that satisfies f(op(a[l], a[l + 1], ..., a[r - 1])) = true.
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

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &(a[i]));
    }

    segtree<S, op, e> seg(a);

    for (int i = 0; i < q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int x, v;
            scanf("%d %d", &x, &v);
            x--;
            seg.set(x, v);
        } else if (t == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            printf("%d\n", seg.prod(l, r));
        } else if (t == 3) {
            int p;
            scanf("%d %d", &p, &target);
            p--;
            printf("%d\n", seg.max_right<f>(p) + 1);
        }
    }
}