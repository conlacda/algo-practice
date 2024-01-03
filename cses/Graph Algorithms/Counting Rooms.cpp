// [Atcoder|Codeforces].abcxxx.F
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

// Chuyen doi grid sang graph
vector<vector<int>> grid2Graph(vector<string>& grid, char node = '#') {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> adj(n*m+1);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (grid[i][j] != node) continue;
            if (i+1 < n && grid[i+1][j] == node) {
                adj[i*m + j].push_back((i+1)*m + j); 
                adj[(i+1)*m + j].push_back(i*m + j); 
            }
            if (j+1 < m && grid[i][j+1] == node) {
                adj[i*m + j].push_back(i*m + j+1);
                adj[i*m + j+1].push_back(i*m + j);
            }
        }
    }
    return adj;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& v: grid) cin >> v;
    auto graph = grid2Graph(grid, '.');
    DSU dsu(n*m+1);
    for (int i=0;i<n*m+1;i++) {
        for (auto v: graph[i]) {
            dsu.merge(i, v);
        }
    }
    set<int> root;
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (grid[i][j] == '.')
                root.insert(dsu.find(i*m+j));
        }
    }
    cout << root.size();
    show_exec_time();
}

