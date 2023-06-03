// https://codeforces.com/problemset/problem/1833/E

#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
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
  vector<int> parent, _rank;
  int N;
  DSU(int N) {
    this->N = N;
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
    assert(0 <= v && v < N);
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

struct Node {
    int nodeNum = 1, connectionNum = 0;
    friend std::ostream& operator<<(std::ostream& os, const Node &s) { return os << destructure(s);}
    bool isFull() {
        return this->nodeNum * 2 == this->connectionNum;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    /*
    Tạo ra 1 đồ thị 2 chiều, a->b cũng có b->a
    Từ đây duyệt qua từng node để tính nodeNum và connection
    */
    vector<Node> nodes(n);
    vector<unordered_set<int>> adj(n);
    for (int i=0;i<n;i++) {
        cin >> a[i]; a[i]--;
        adj[i].insert(a[i]);
        adj[a[i]].insert(i);
    }
    DSU dsu(n);
    for (int u=0;u<n;u++) {
        for (auto v: adj[u]) {
            int ru = dsu.find_set(u);
            int rv = dsu.find_set(v);
            if (ru == rv) {
                nodes[ru] = Node{nodes[ru].nodeNum, nodes[ru].connectionNum + 1};
            } else {
                dsu.merge_set(ru, rv);
                int r = dsu.find_set(ru);
                nodes[r] = Node{nodes[ru].nodeNum + nodes[rv].nodeNum, nodes[ru].connectionNum + nodes[rv].connectionNum + 1};
            }
        }
    }
    unordered_set<int> roots;
    for (int i=0;i<n;i++) {
        roots.insert(dsu.find_set(i));
    }
    int full = 0, notFull = 0;
    for (auto v: roots) {
        if (nodes[v].isFull()) full++;
        else notFull = 1;
    }
    cout << full + notFull << ' '<< (int) roots.size() << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();
    show_exec_time();
}
