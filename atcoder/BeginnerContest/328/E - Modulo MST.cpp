// https://atcoder.jp/contests/abc328/tasks/abc328_e
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

class DSU {
 public:
    vector<int> parent, rank;
    int N;
    DSU(int N) {
        this->N = N;
        this->parent.resize(N);
        this->rank.resize(N, 0);
        for (int i = 0; i < N; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int v) {
        assert(0 <= v && v < N);
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }
    bool isSame(int a, int b) {
        return find(a) == find(b);
    }
};

struct Edge {
    int u, v, w;
    friend std::ostream& operator<<(std::ostream& os, const Edge& s) { return os << destructure(s);}
};

template<typename T>
struct Combination {
    int n;
    vector<bool> v;
    vector<T> a;
    bool hasNext = true;
    Combination(vector<T>& a, int k){
        n = a.size();
        v.resize(n);
        assert(n >= k);
        std::fill(v.end() - k, v.end(), true);
        this->a = a;
    }
    vector<T> nextPermutation() {
        vector<T> res;
        for (int i = 0; i < n; ++i) {
            if (v[i]) {
                res.push_back(a[i]);
            }
        }
        hasNext = std::next_permutation(v.begin(), v.end());
        return res;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> edges;
    for (int i=0;i<m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        edges.push_back({u, v, w});
    }
    /*
    Lay ra toan bo combination -> xem no co phai MST khong.
    */
    std::function<bool(vector<Edge>)> isMST = [&](vector<Edge> edges){
        // kiem tra xem do thi co hop thanh mst
        DSU dsu(n);
        for (auto edge: edges) {
            if (dsu.isSame(edge.u, edge.v)) return false;
            dsu.merge(edge.u, edge.v);
        }
        return true;
    };
    Combination c(edges, n-1);
    int ans = INF;
    while (c.hasNext) {
        auto comb = c.nextPermutation();
        if (isMST(comb)) {
            int sum = 0;
            for (auto edge: comb) sum += edge.w;
            ans = min(ans, sum %k);
        }
    }
    cout << ans;
    show_exec_time();
}
