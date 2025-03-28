// https://codeforces.com/gym/101808/problem/B
// B. Amer and Graphs
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

struct SumXorNode {
    // for multiset hash
    int sum = 0, mul = 1;
    int size = 1;
    bool is_null = false;
    friend SumXorNode operator+(SumXorNode a, SumXorNode b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return SumXorNode {
            a.sum + b.sum,
            (a.mul * b.mul) % mod,
            a.size + b.size
        };
    }
    friend bool operator<(SumXorNode a, SumXorNode b) {
        if (a.sum != b.sum) return a.sum < b.sum;
        if (a.mul != b.mul) return a.mul < b.mul;
        return a.size < b.size;
    }
};
using Node = SumXorNode;

mt19937 _rand(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> dist(1, mod - 1);
map<pair<int,int>, int> randomMap;
void randomMapping() {} // Base case: when there are no more arguments to process
template <typename T, typename... Args>
void randomMapping(T& first, Args&... rest) {
    for (auto&v: first) {
        if (randomMap.find(v) == randomMap.end()) {
            randomMap[v] = dist(_rand);
        }
    }

    randomMapping(rest...);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> graph(n);
    for (int i=0;i<n;i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        if (l > r) swap(l, r);
        graph[i] = {l, r};
    }
    randomMap.clear();
    randomMapping(graph);
    vector<Node> a(n);
    for (int i=0;i<n;i++) {
        int val = randomMap[graph[i]];
        a[i] = Node{val, val};
    }
    map<Node, int> M;
    for (int i=0;i<n;i++) {
        Node node = Node{.is_null = true};
        for (int j=i;j<n;j++) {
            node = node + a[j];
            M[node]++;
        }
    }
    int ans = 0;
    for (auto&v: M) {
        ans += v.second * (v.second - 1) / 2;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) solve();

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
