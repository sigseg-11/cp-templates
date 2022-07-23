std::pair<int, std::vector<int>> tree_diameter(const std::vector<std::vector<int>>& G) {
    std::vector<int> to(G.size());

    auto dfs = [&](const auto& dfs, int v, int p) -> std::pair<int, int> {
        std::pair<int, int> ret(0, v);
        for (int c : G[v]) {
            if (c == p) continue;
            auto weight = dfs(dfs, c, v);
            ++weight.first;
            if (ret < weight) {
                ret = weight;
                to[v] = c;
            }
        }
        return ret;
    };

    auto p = dfs(dfs, 0, -1);
    auto q = dfs(dfs, p.second, -1);
    std::vector<int> path;
    int v = p.second;
    while (v != q.second) {
        path.push_back(v);
        v = to[v];
    }
    path.push_back(v);
    return {q.first, path};
}

long long tree_hash(const std::vector<std::vector<int>>& G, int root = -1) {
    static constexpr long long mod = (1LL << 61) - 1;

    static auto add = [&](long long a, long long b) {
        if ((a += b) >= mod) a -= mod;
        return a;
    };

    static auto mul = [&](long long a, long long b) {
        __int128_t c = (__int128_t)a * b;
        return add(c >> 61, c & mod);
    };

    static std::random_device rd;
    static std::mt19937_64 rng(rd());
    static std::uniform_int_distribution<long long> rand(1, mod - 1);
    static std::vector<long long> R;

    auto dfs = [&](auto& dfs, int v, int p, int d) -> long long {
        if ((int) R.size() == d) {
            R.push_back(rand(rng));
        }
        long long res = 1;
        for (int c : G[v]) {
            if (c != p) {
                res = mul(res, dfs(dfs, c, v, d + 1));
            }
        }
        res = add(res, R[d]);
        return res;
    };

    long long res;
    if (root == -1) {
        int d;
        std::vector<int> path;
        std::tie(d, path) = tree_diameter(G);
        res = dfs(dfs, path[d / 2], -1, 0);
        if (d % 2 == 1) {
            res = std::min(res, dfs(dfs, path[d / 2 + 1], -1, 0));
        }
    } else {
        res = dfs(dfs, root, -1, 0);
    }
    return res;
}