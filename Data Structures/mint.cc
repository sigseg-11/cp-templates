using MOD = int(1e9 + 7);

inline ll pow(ll a, ll b, ll m) {a %= m; ll res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1;} return res;}
inline ll pow(ll a, ll b) {ll res = 1; while (b > 0) { if (b & 1) res = res *1LL* a; a = a *1LL* a; b >>= 1;} return res;}
inline ll gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
inline tll ee(ll a, ll b) { if (b == 0) return {a, 1, 0}; int d, x, y; tie(d, x, y) = ee(b, a % b); return {d, y, x - (a / b) * y};}
inline ll add(ll a, ll b) { return (a % MOD + b % MOD) % MOD; }
inline ll sub(ll a, ll b) { return (a % MOD - b % MOD) % MOD; }
inline ll mul(ll a, ll b) { return (a % MOD * 1LL * b % MOD) % MOD; }
inline ll divi(ll a, ll b) { return mul(a, pow(b, MOD - 2, MOD)); }


template <int mod = int(1e9+7)>
struct mint {
  int x;

  mint() : x(0) {}

  mint(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

  mint &operator+=(const mint &p) {
    if ((x += p.x) >= mod) x -= mod;
    return *this;
  }

  mint &operator-=(const mint &p) {
    if ((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }

  mint &operator*=(const mint &p) {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }

  mint &operator/=(const mint &p) {
    *this *= p.inverse();
    return *this;
  }

  mint operator-() const { return mint(-x); }

  mint operator+(const mint &p) const { return mint(*this) += p; }

  mint operator-(const mint &p) const { return mint(*this) -= p; }

  mint operator*(const mint &p) const { return mint(*this) *= p; }

  mint operator/(const mint &p) const { return mint(*this) /= p; }

  bool operator==(const mint &p) const { return x == p.x; }

  bool operator!=(const mint &p) const { return x != p.x; }

  mint inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return mint(u);
  }

  mint pow(int64_t n) const {
    mint ret(1), mul(x);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const mint &p) { return os << p.x; }

  friend istream &operator>>(istream &is, mint &a) {
    int64_t t;
    is >> t;
    a = mint<mod>(t);
    return (is);
  }
  
  int get() const { return x; }

  static constexpr int get_mod() { return mod; }
};

