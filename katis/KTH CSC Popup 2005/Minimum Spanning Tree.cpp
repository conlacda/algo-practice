// https://open.kattis.com/problems/minspantree
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

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

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, m;
    while(cin >> n >> m){
        if (n == 0 && m==0) break;
        vector<vector<pair<ll, ll>>> g(n);
        for (ll i=0;i<m;i++){
            ll u, v, w;
            cin >> u>> v>> w;
            if (u>v) swap(u, v);
            g[u].push_back({v, w});
        }
        vector<Edge> mst = kruskal(g);
        if ((int) mst.size() == 0) {
            cout << "Impossible\n";
        } else {
            ll weight = 0;
            for (auto v: mst) weight+= v.w;
            cout << weight<<'\n';
            sort(mst.begin(), mst.end(), Edge::lexicographic_order);
            for (auto v: mst){
                cout << v.u << ' '<< v.v <<'\n';
            }
        }
    }    
    show_exec_time();
}
