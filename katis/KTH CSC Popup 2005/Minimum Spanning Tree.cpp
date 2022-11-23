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
#endif

class DSU {
 public:
  vector<int> parent, _rank;
  DSU(int N) {
    this->parent.resize(N);
    this->_rank.resize(N);
    for (int i = 0; i < N; i++) {
      this->make_set(i);
    }
  }

  void make_set(int v) {
    this->parent[v] = v;
    this->_rank[v] = 0;
  }

  int find_set(int v) {
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = find_set(parent[v]);
  }

  void merge_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (_rank[a] < _rank[b]) {
        swap(a, b);
      }
      parent[b] = a;
      if (_rank[a] == _rank[b]) {
        _rank[a]++;
      }
    }
  }
};

struct Edge {
    ll u, v, w;
    friend bool operator<(Edge a, Edge b){
        return a.w < b.w;
    }
    bool operator()(Edge a, Edge b){
        if (a.u == b.u) return a.v < b.v;
        return a.u < b.u;    
    }
    static bool lexicographic_order(Edge a, Edge b){
        if (a.u == b.u) return a.v < b.v;
            return a.u < b.u;    
    }
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
        if (dsu.find_set(edge.u) != dsu.find_set(edge.v)){
            mst.push_back(edge);
            dsu.merge_set(edge.u, edge.v);
        }
    }
    if ((int)mst.size() != n-1){
        return {};
    }
    return mst;
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, m;
    while(cin >> n >> m){
        if (n == 0 && m==0) return 0;
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
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
