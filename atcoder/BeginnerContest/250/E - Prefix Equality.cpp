#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

mt19937 _rand(std::chrono::steady_clock::now().time_since_epoch().count());
map<int, int> randomMap;
void randomMapping() {} // Base case: when there are no more arguments to process
template <typename T, typename... Args>
void randomMapping(T& first, Args&... rest) {
    for (auto&v: first) {
        if (!randomMap.count(v)) {
            auto randomVal = _rand();
            randomMap[v] = randomVal;
            v = randomVal;
        } else {
            v = randomMap[v];
        }
    }

    randomMapping(rest...);
}

struct SumXorNode {
    int sum = 0, _xor = 0;
    bool is_null = false;
    friend SumXorNode operator+(SumXorNode a, SumXorNode b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return SumXorNode {
            a.sum + b.sum,
            a._xor ^ b._xor,
        };
    }
};
using Node = SumXorNode;

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto&v: a) cin >> v;
    for (auto&v: b) cin >> v;
    randomMapping(a, b);
    // xử lý - tính hash cho mọi prefix
    vector<pair<int,int>> aph, bph;
    set<int> as, bs;
    auto node = Node{.is_null = true};
    for (auto&v: a) {
        if (!as.count(v)) {
            as.insert(v);
            node = node + Node{v, v};
        }
        aph.push_back({node.sum, node._xor});
    }
    node = Node{.is_null = true};
    for (auto&v: b) {
        if (!bs.count(v)) {
            bs.insert(v);
            node = node + Node{v, v};
        }
        bph.push_back({node.sum, node._xor});
    }
    // Answer query
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (aph[x].first == bph[y].first and aph[x].second == bph[y].second) cout << "Yes\n";
        else cout << "No\n";
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
