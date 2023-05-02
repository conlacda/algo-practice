// https://codeforces.com/contest/154/problem/C
// https://codeforces.com/contest/154/my
#include<bits/stdc++.h>

typedef long long ll;
const int mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

<hash-string with int toInt(char x) -> int toInt(int x)>

long long nCr(ll n, ll r) {
    if(r > n - r) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    ll i;
    for(i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}
 
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
 
struct Object{
    ll v, hvalue;
    bool friend operator<(Object x, Object y){
        return x.hvalue < y.hvalue;
    }
    bool friend operator==(Object x, Object y){
        return x.hvalue == y.hvalue;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, q;
    cin >> n>>q;
    vector<vector<ll>> g(n);
    for (ll i=0;i<q;i++) {
        ll u, v; cin >> u>> v;u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (auto &v: g){
        sort(v.begin(), v.end());
    }
    Hash<vector<ll>> hash; hash.build(n+5);
    /*
    Bài này yêu cầu tìm ra số cặp đỉnh (u1, u2) mà có các đỉnh kề giống hệt nhau
    2 đỉnh u1, u2 sẽ là double profile nếu u1, u2 có set(đỉnh kề) bằng nhau
    hoặc nếu u1 nối tới u2 thì set(đỉnh kề + chính nó) bằng nhau
    Ví dụ 1<->2 3<->2 => (1,3) là double profile vì set(kề) = {2}
    1<->2 2<->3 3<->1 => (1,3) là double profile vì set(kề + chính nó) = {1,2,3}.
                        nếu ko tính chính nó thì set(kề 1) = {2, 3}, set(kề 3) = {1,2}
    để so sánh 2 set(vector) với nhau ta dùng hash(vector<>). Khi này chỉ cần sắp xếp NlogN
    là ta có thể đếm được có bao nhiêu đỉnh có set(kề)/set(kề+chính nó) bằng nhau.
    -> Với K đỉnh bằng nhau thì có kC2 cặp double profile
    */
    vector<Object> s_with_itself, s_without_itself;
    for (ll i =0;i<n;i++){
        vector<ll> gi = g[i];
        auto ho = hash.getHash(gi);
        s_without_itself.push_back(Object{i, ho});
        gi.push_back(i);
        sort(gi.begin(), gi.end());
        ho = hash.getHash(gi);
        s_with_itself.push_back(Object{i, ho});
    }
    DSU dsu(n);
    sort(s_with_itself.begin(), s_with_itself.end());
    sort(s_without_itself.begin(), s_without_itself.end());
    for (ll i=1;i<n;i++){
        if (s_with_itself[i] == s_with_itself[i-1]){
            dsu.merge_set(s_with_itself[i].v, s_with_itself[i-1].v);
        }
        if (s_without_itself[i] == s_without_itself[i-1]){
            dsu.merge_set(s_without_itself[i].v, s_without_itself[i-1].v);
        }
    }
    for (ll i=0;i<n;i++) dsu.find_set(i);
    map<ll, int> m;
    for (int i=0;i<n;i++){
        m[dsu.parent[i]]++;
    }
    ll ans = 0;
    for (auto v: m){
        if (v.second > 1){
            ans += nCr(v.second, 2);
        }
    }
    cout << ans;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
