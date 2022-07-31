namespace inner {

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

template <typename T>
T gcd(T a, T b) {
  while (b) swap(a %= b, b);
  return a;
}

template <typename T>
T inv(T a, T p) {
  T b = p, x = 1, y = 0;
  while (a) {
    T q = b / a;
    swap(a, b %= a);
    swap(x, y -= q * x);
  }
  assert(b == 1);
  return y < 0 ? y + p : y;
}

template <typename T, typename U>
T modpow(T a, U n, T p) {
  T ret = 1 % p;
  for (; n; n >>= 1, a = U(a) * a % p)
    if (n & 1) ret = U(ret) * a % p;
  return ret;
}

}

namespace my_rand {

// [0, 2^64 - 1)
uint64_t rng() {
  static uint64_t x_ =
      uint64_t(chrono::duration_cast<chrono::nanoseconds>(
                   chrono::high_resolution_clock::now().time_since_epoch())
                   .count()) *
      10150724397891781847ULL;
  x_ ^= x_ << 7;
  return x_ ^= x_ >> 9;
}

// [l, r)
int64_t randint(int64_t l, int64_t r) {
  assert(l < r);
  return l + rng() % (r - l);
}

// choose n numbers from [l, r) without overlapping
vector<int64_t> randset(int64_t l, int64_t r, int64_t n) {
  assert(l <= r && n <= r - l);
  unordered_set<int64_t> s;
  for (int64_t i = n; i; --i) {
    int64_t m = randint(l, r + 1 - i);
    if (s.find(m) != s.end()) m = r - i;
    s.insert(m);
  }
  vector<int64_t> ret;
  for (auto& x : s) ret.push_back(x);
  return ret;
}

// [0.0, 1.0)
double rnd() {
  union raw_cast {
    double t;
    uint64_t u;
  };
  constexpr uint64_t p = uint64_t(1023 - 64) << 52;
  return rng() * ((raw_cast*)(&p))->t;
}

template <typename T>
void randshf(vector<T>& v) {
  int n = v.size();
  for (int loop = 0; loop < 2; loop++)
    for (int i = 0; i < n; i++) swap(v[i], v[randint(0, n)]);
}

}  // namespace my_rand

using my_rand::randint;
using my_rand::randset;
using my_rand::randshf;
using my_rand::rnd;
using my_rand::rng;

struct ArbitraryLazyMontgomeryModInt {
  using mint = ArbitraryLazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static u32 mod;
  static u32 r;
  static u32 n2;

  static u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static void set_mod(u32 m) {
    assert(m < (1 << 30));
    assert((m & 1) == 1);
    mod = m;
    n2 = -u64(m) % m;
    r = get_r();
    assert(r * mod == 1);
  }

  u32 a;

  ArbitraryLazyMontgomeryModInt() : a(0) {}
  ArbitraryLazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  mint operator+(const mint &b) const { return mint(*this) += b; }
  mint operator-(const mint &b) const { return mint(*this) -= b; }
  mint operator*(const mint &b) const { return mint(*this) *= b; }
  mint operator/(const mint &b) const { return mint(*this) /= b; }
  bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  mint operator-() const { return mint() - mint(*this); }

  mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = ArbitraryLazyMontgomeryModInt(t);
    return (is);
  }

  mint inverse() const { return pow(mod - 2); }

  u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static u32 get_mod() { return mod; }
};
typename ArbitraryLazyMontgomeryModInt::u32 ArbitraryLazyMontgomeryModInt::mod;
typename ArbitraryLazyMontgomeryModInt::u32 ArbitraryLazyMontgomeryModInt::r;
typename ArbitraryLazyMontgomeryModInt::u32 ArbitraryLazyMontgomeryModInt::n2;

struct montgomery64 {
  using mint = montgomery64;
  using i64 = int64_t;
  using u64 = uint64_t;
  using u128 = __uint128_t;

  static u64 mod;
  static u64 r;
  static u64 n2;

  static u64 get_r() {
    u64 ret = mod;
    for (i64 i = 0; i < 5; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static void set_mod(u64 m) {
    assert(m < (1LL << 62));
    assert((m & 1) == 1);
    mod = m;
    n2 = -u128(m) % m;
    r = get_r();
    assert(r * mod == 1);
  }

  u64 a;

  montgomery64() : a(0) {}
  montgomery64(const int64_t &b) : a(reduce((u128(b) + mod) * n2)){};

  static u64 reduce(const u128 &b) {
    return (b + u128(u64(b) * u64(-r)) * mod) >> 64;
  }

  mint &operator+=(const mint &b) {
    if (i64(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  mint &operator-=(const mint &b) {
    if (i64(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  mint &operator*=(const mint &b) {
    a = reduce(u128(a) * b.a);
    return *this;
  }

  mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  mint operator+(const mint &b) const { return mint(*this) += b; }
  mint operator-(const mint &b) const { return mint(*this) -= b; }
  mint operator*(const mint &b) const { return mint(*this) *= b; }
  mint operator/(const mint &b) const { return mint(*this) /= b; }
  bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  mint operator-() const { return mint() - mint(*this); }

  mint pow(u128 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = montgomery64(t);
    return (is);
  }

  mint inverse() const { return pow(mod - 2); }

  u64 get() const {
    u64 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static u64 get_mod() { return mod; }
};
typename montgomery64::u64 montgomery64::mod, montgomery64::r, montgomery64::n2;

namespace fast_factorize {
using u64 = uint64_t;

template <typename mint>
bool miller_rabin(u64 n, vector<u64> as) {
  if (mint::get_mod() != n) mint::set_mod(n);
  u64 d = n - 1;
  while (~d & 1) d >>= 1;
  mint e{1}, rev{int64_t(n - 1)};
  for (u64 a : as) {
    if (n <= a) break;
    u64 t = d;
    mint y = mint(a).pow(t);
    while (t != n - 1 && y != e && y != rev) {
      y *= y;
      t *= 2;
    }
    if (y != rev && t % 2 == 0) return false;
  }
  return true;
}

bool is_prime(u64 n) {
  if (~n & 1) return n == 2;
  if (n <= 1) return false;
  if (n < (1LL << 30))
    return miller_rabin<ArbitraryLazyMontgomeryModInt>(n, {2, 7, 61});
  else
    return miller_rabin<montgomery64>(
        n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

template <typename mint, typename T>
T pollard_rho(T n) {
  if (~n & 1) return 2;
  if (is_prime(n)) return n;
  if (mint::get_mod() != n) mint::set_mod(n);
  mint R, one = 1;
  auto f = [&](mint x) { return x * x + R; };
  auto rnd_ = [&]() { return rng() % (n - 2) + 2; };
  while (1) {
    mint x, y, ys, q = one;
    R = rnd_(), y = rnd_();
    T g = 1;
    constexpr int m = 128;
    for (int r = 1; g == 1; r <<= 1) {
      x = y;
      for (int i = 0; i < r; ++i) y = f(y);
      for (int k = 0; g == 1 && k < r; k += m) {
        ys = y;
        for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));
        g = inner::gcd<T>(q.get(), n);
      }
    }
    if (g == n) do
        g = inner::gcd<T>((x - (ys = f(ys))).get(), n);
      while (g == 1);
    if (g != n) return g;
  }
  exit(1);
}

using i64 = long long;

vector<i64> inner_factorize(u64 n) {
  if (n <= 1) return {};
  u64 p;
  if (n <= (1LL << 30))
    p = pollard_rho<ArbitraryLazyMontgomeryModInt, uint32_t>(n);
  else
    p = pollard_rho<montgomery64, uint64_t>(n);
  if (p == n) return {i64(p)};
  auto l = inner_factorize(p);
  auto r = inner_factorize(n / p);
  copy(begin(r), end(r), back_inserter(l));
  return l;
}

vector<i64> factorize(u64 n) {
  auto ret = inner_factorize(n);
  sort(begin(ret), end(ret));
  return ret;
}

map<i64, i64> factor_count(u64 n) {
  map<i64, i64> mp;
  for (auto &x : factorize(n)) mp[x]++;
  return mp;
}

vector<i64> divisors(u64 n) {
  if (n == 0) return {};
  vector<pair<i64, i64>> v;
  for (auto &p : factorize(n)) {
    if (v.empty() || v.back().first != p) {
      v.emplace_back(p, 1);
    } else {
      v.back().second++;
    }
  }
  vector<i64> ret;
  auto f = [&](auto rc, int i, i64 x) -> void {
    if (i == (int)v.size()) {
      ret.push_back(x);
      return;
    }
    for (int j = v[i].second;; --j) {
      rc(rc, i + 1, x);
      if (j == 0) break;
      x *= v[i].first;
    }
  };
  f(f, 0, 1);
  sort(begin(ret), end(ret));
  return ret;
}

}  // namespace fast_factorize

using fast_factorize::divisors;
using fast_factorize::factor_count;
using fast_factorize::factorize;
using fast_factorize::is_prime;

/**
 * @brief 高速素因数分解(Miller Rabin/Pollard's Rho)
 * @docs docs/prime/fast-factorize.md
 */