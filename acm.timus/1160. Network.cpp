// https://timus.online/problem.aspx?space=1&num=1160
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
#define int long long

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
    ll u, v, w;
    friend bool operator<(Edge a, Edge b){
        return a.w < b.w;
    }
    static bool lexicographic_order(Edge a, Edge b){
        if (a.u == b.u) return a.v < b.v;
            return a.u < b.u;    
    }
    friend std::ostream& operator<<(std::ostream& os, const Edge& s) { return os << destructure(s);}
};
vector<Edge> kruskal(vector<vector<pair<ll,ll>>> g){
    // Nhận vào 1 graph và trả về danh sách của MST
    int n = (int) g.size();
    vector<Edge> edges;
    for (int i=0;i<n;i++){
        for (auto pii: g[i]){
            edges.push_back(Edge{i, pii.first, pii.second});
        }
    }
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    vector<Edge> mst;
    for (auto edge: edges){
        if (dsu.find(edge.u) != dsu.find(edge.v)){
            mst.push_back(edge);
            dsu.merge(edge.u, edge.v);
        }
    }
    // sort(mst.begin(), mst.end(), Edge::lexicographic_order); // sắp xếp theo thứ tự đỉnh nhỏ trước
    if ((int)mst.size() != n-1) return {}; // đồ thị ko connected
    return mst;
}
// Doc: http://localhost:3000/docs/competitive-programming/graph/basic/minimum-spanning-tree

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int, int>>> adj(n);
    for (int i=0;i<q;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<Edge> mst = kruskal(adj);
    dbg(mst);
    int _max = 0;
    for (auto v: mst) {
        _max = max(_max, v.w);
    }
    cout << _max << '\n';
    cout << mst.size() << '\n';
    for (auto v: mst) {
        cout << v.u+ 1<< ' '<< v.v +1 <<'\n';
    }
    show_exec_time();
}