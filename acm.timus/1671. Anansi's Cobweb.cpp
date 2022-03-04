// https://acm.timus.ru/problem.aspx?space=1&num=1671
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

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

struct Edge{
    int u, v, sequence;
    friend bool operator<(Edge a, Edge b){
        return a.sequence < b.sequence;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, m;
    cin >> N >> m;
    // Lật ngược DSU lại rồi merge dần vào
    vector<Edge> s;
    for (int i=0;i<m;i++){
        int u, v;
        cin >> u >> v; u--; v--;
        s.push_back(Edge{u, v, 0});
    }
    int q;
    cin >> q;
    // Offline query
    for (int i=0;i<q;i++){
        int u; cin >> u; u--;
        s[u].sequence = q-i;
    }
    sort(s.begin(), s.end());
    DSU dsu(N);
    vector<int> ans;
    int part = N;
    for (auto v: s){
        if (v.sequence > 0) ans.push_back(part);    
        if (dsu.find_set(v.u) != dsu.find_set(v.v)){
            part--;
            dsu.merge_set(v.u, v.v);
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto v: ans){
        cout << v<< ' ';
    }
}
// Bài toán yêu cầu tính số thành phần sau khi gỡ 1 cạnh của DSU
// Có thể được hiểu thành thêm dần các cạnh vào DSU. Tính số thành phần tại thời điểm ngay trước khi thêm thành phần
// => Đơn giản chỉ thêm dần các cạnh vào. Nếu 2 đỉnh khác SCC thì sẽ giảm số thành phần CC đi.