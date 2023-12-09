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

class LCA{
private:
    template<typename T> struct RMQ { int n = 0; vector<T> values; vector<vector<int>> range_low;  static int largest_bit(int x) { return x == 0 ? -1 : 31 - __builtin_clz(x); }  int better_index(int a, int b) const { return values[a] < values[b] ? a : b; }  void build(const vector<T> &_values) { values = _values; n = (int) values.size(); int levels = largest_bit(n) + 1; range_low.resize(levels);  for (int k = 0; k < levels; k++) range_low[k].resize(n - (1 << k) + 1);  for (int i = 0; i < n; i++) range_low[0][i] = i;  for (int k = 1; k < levels; k++) for (int i = 0; i <= n - (1 << k); i++) range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]); }  int query_index(int a, int b) const { b++; assert(0 <= a && a < b && b <= n); int level = largest_bit(b - a); return better_index(range_low[level][a], range_low[level][b - (1 << level)]); } };
    vector<int> euler_vertices, euler_height; // là 2 array ở ảnh trong cp-algorithm
public:
    int n, log2_n, root;
    vector<int> first, depth;
    vector<vector<int>> up; // up[u] chứa danh sách cha của u. up[u][k] là cha thứ 2^k, up[u][0] là cha thứ 1, up[u][1] là cha 2
    RMQ<int> rmq;
    LCA() {}
    LCA(vector<vector<int>>& graph, int root = 0){ build(graph, root);}
    void build(vector<vector<int>>& graph, int root = 0) {
        this->n = graph.size(); log2_n = ceil(log2(n)); this->root = root;
        depth.resize(n, 0);
        first.resize(n, -1);
        up.assign(n, vector<int>(log2_n + 1));
        makeEuler(graph, root);
        rmq.build(euler_height);
        binary_lifting(graph, root, root);
    }
    // Euler tour of tree
    void makeEuler(vector<vector<int>>& graph, int root){
        // Euler tour tạo ra verticies, depths, index
        int dep = 0, cur_index = 0;
        std::function<void(int, int)> explore = [&](int u, int p){
            depth[u] = dep; dep++;
            if (first[u] == -1) first[u] = cur_index;
            euler_vertices.push_back(u); euler_height.push_back(dep);
            cur_index++;
            for (auto v: graph[u]){
                if (v == p) continue;
                explore(v, u);
                dep--; cur_index++;
                euler_vertices.push_back(u); euler_height.push_back(dep);
            }
        };
        explore(root, root);
    }
    void binary_lifting(vector<vector<int>>& graph, int u, int p)
    {
        up[u][0] = p;
        for (int i = 1; i <= log2_n; ++i)
            up[u][i] = up[up[u][i-1]][i-1];

        for (int v : graph[u])
            if (v != p)
                binary_lifting(graph, v, u);
    }
    // Expose
    int lca(int u, int v){
        int fu = first[u];
        int fv = first[v];
        if (fu > fv) swap(fu, fv);
        int index = rmq.query_index(fu, fv);
        return euler_vertices[index];
    }

    int distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int kth_ancestor(int u, int k) {
        if (k >= depth[u]) return root;
        if (k == 0) return u;
        int cur = 0;
        while (k != 0) {
            if (k&1) u = up[u][cur];
            cur++; k>>=1;
        }
        return u;
    }
    int lca(int r, int u, int v){ // ar = abtrary root - LCA của u,v với r bất kỳ là root
        int ru = lca(r, u);
        int rv = lca(r, v);
        int uv = lca(u, v);
        if (ru == rv) return uv;
        if (ru == uv) return rv;
        return ru;
    }
};

void solve(){
    int n;
    cin >>n;
    vector<vector<int>> g(n);
    for (int i=0;i<n;i++){
        int m; cin >>m;
        for (int j=0;j<m;j++){
            int v; cin >>v; v--;
            g[i].push_back(v);
            g[v].push_back(i);
        }
    }
 
    int q;
    cin >>q;
    LCA lca;
    lca.build(g);
    for (int i=0;i<q;i++){
        int u, v; cin >> u>>v; u--;v--;
        cout<< lca.lca(u, v) +1<< '\n';
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N;
    cin >> N;
    for (int i=0;i<N;i++){
        cout << "Case " << i+1<< ":\n";
        solve();
    }
    show_exec_time();
} 
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
