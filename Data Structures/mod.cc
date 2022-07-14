using MOD = int(1e9 + 7);

inline ll pow(ll a, ll b, ll m) {a %= m; ll res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1;} return res;}
inline ll pow(ll a, ll b) {ll res = 1; while (b > 0) { if (b & 1) res = res *1LL* a; a = a *1LL* a; b >>= 1;} return res;}
inline ll gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
inline tll ee(ll a, ll b) { if (b == 0) return {a, 1, 0}; int d, x, y; tie(d, x, y) = ee(b, a % b); return {d, y, x - (a / b) * y};}
inline ll add(ll a, ll b) { return (a % MOD + b % MOD) % MOD; }
inline ll sub(ll a, ll b) { return (a % MOD - b % MOD) % MOD; }
inline ll mul(ll a, ll b) { return (a % MOD * 1LL * b % MOD) % MOD; }
inline ll divi(ll a, ll b) { return mul(a, pow(b, MOD - 2, MOD)); }
