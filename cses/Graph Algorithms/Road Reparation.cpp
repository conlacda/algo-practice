// https://cses.fi/problemset/task/1675/
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
/*
DSU dsu(N);
dsu.merge_set(u,v);
dsu.find_set(u) == dsu.find_set(v); // check if u,v in the same SCC
*/
struct Edge {
    ll u, v, w;
    friend bool operator<(Edge a, Edge b){
        return a.w < b.w;
    }
};
vector<Edge> kruskal(vector<vector<pair<ll,ll>>> g){
    // Nhận vào 1 graph và trả về danh sách của MST
    int n = (int) g.size();
    // vector<Edge> edges;
    multiset<Edge> edges;
    for (int i=0;i<n;i++){
        for (auto pii: g[i]){
            edges.insert(Edge{i, pii.first, pii.second});
        }
    }
    // sort(edges.begin(), edges.end());
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
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> g(n);
    for (ll i=0;i<m;i++){
        ll u, v, w;
        cin >> u>> v >> w;
        g[--u].push_back({--v, w});
    }
    vector<Edge> mst = kruskal(g);
    if ((int) mst.size() == 0){
        cout << "IMPOSSIBLE";
    } else {
        ll weight = 0;
        for (auto v: mst){
            weight += v.w;
        }
        cout << weight;
    }
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}