// https://tlx.toki.id/problems/troc-13/D
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Copy from nealwu's template - http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result { Fun fun_; public:template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {} template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }}; template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

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
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n,m;
    cin >> n>> m;
    /*
    Có max 90.000 ô tồn tại
    -> compress thành 1 mảng 9*1e4 phần tử
    duyệt dần từ cao xuống thấp
    có 1 mảng lưu trữ trạng thái có nước hay đất
    Với 1 số được duyệt thì xem các ô nào sẽ thành đất
    xét các ô bên cạnh để dsu.merge()
    với mỗi số được duyệt số đất sẽ tăng bằng số ô có giá trị đó
    sau đó trừ đi do việc dsu.merge()
    */
    map<int, vector<pair<int,int>>> _map;
    vector<int> f;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            int x; cin >> x;
            a[i][j] = x;
            f.push_back(x);
            _map[x].push_back(make_pair(i, j));
        }
    }
    sort(f.rbegin(), f.rend());
    f.erase(unique(f.begin(), f.end()), f.end());
    DSU dsu(n*m);
    int cur = 0, ans = 0;
    for (auto it: f){
        // cho các ô có giá trị x thành đất
        vector<pair<int,int>> land = _map[it];
        for (auto l: land){
            cur++;
            // kiểm tra các ô xung quanh nếu chưa có thì merge
            int x = l.first;
            int y = l.second;
            if (y > 0){
                if (a[x][y-1] >= it){
                    if (dsu.find_set(x*m+y-1) != dsu.find_set(x*m+y)){
                        cur--;
                        dsu.merge_set(x*m+y-1, x*m+y);
                    }
                }
            }
            if (y<m-1){
                if (a[x][y+1] >= it){
                    if (dsu.find_set(x*m+y) != dsu.find_set(x*m+y+1)){
                        cur--;
                        dsu.merge_set(x*m+y, x*m+y+1);
                    }
                }
            }
            if (x>0){
                int _x = x-1;
                if (a[_x][y] >=it){
                    if (dsu.find_set(_x*m+y) != dsu.find_set(x*m+y)){
                        cur--;
                        dsu.merge_set(_x*m+y, x*m+y);
                    }
                }
            }
            if (x<n-1){
                int _x = x+1;
                if (a[_x][y] >=it){
                    if (dsu.find_set(_x*m+y) != dsu.find_set(x*m+y)){
                        cur--;
                        dsu.merge_set(_x*m+y, x*m+y);
                    }
                }
            }
        }
        ans = max(ans, cur);
    }
    cout << ans;
    cerr << "Time: " <<(double)clock() / CLOCKS_PER_SEC <<"s\n";
}
