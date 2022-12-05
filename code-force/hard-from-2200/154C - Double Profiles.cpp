// https://codeforces.com/contest/154/problem/C
// https://codeforces.com/contest/154/my
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


template<class Iterable> // chỉ chạy với 64bit.
class Hash{
private:
    vector<ll> pc;
    ll factor = 137;
    ll length;
    vector<ll> inv;
    Iterable s, rs;
public:
    vector<ll> prefix_hash, rprefix_hash;
    char min_char = char(0);
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    Hash(){}
    void build(ll length = 200005){
        // Pre compute 
        ll p = 1;
        for (ll i=0;i<length;i++){
            pc.push_back(p);
            p = (p* factor) % mod;
        }
        for (auto v: pc) inv.push_back(mod_inv(v));
    }
    ll once(Iterable s){
        ll hash_value = 0;
        for (int i=0;i< (int) s.size();i++){
            int v = s[i] - min_char + 1;
            hash_value = (hash_value + 1LL*v*pc[i]) % mod;
        }
        return hash_value; 
    }
    ll ronce(Iterable s){
        reverse(s.begin(), s.end()); // phần này viết giống dạng once nhanh hơn được 1 chút
        return once(s);
    }
    // lấy ra luôn 1 lúc hash ngược và hash xuôi
    pair<ll, ll> both_once(Iterable s){
        return make_pair(once(s), ronce(s));
    }
};
struct IntPairHash {
    static_assert(sizeof(int) * 2 == sizeof(size_t));
    size_t operator()(pair<ll, ll> p) const noexcept {
        return size_t(p.first) << 32 | p.second; // <<32 chỉ chạy với 64 bit.
    }
};

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
    ll v, hvalue, rhvalue;
    bool friend operator<(Object x, Object y){
        if (x.hvalue == y.hvalue) return x.rhvalue < y.rhvalue;
        return x.hvalue < y.hvalue;
    }
    bool friend operator==(Object x, Object y){
        if (x.hvalue == y.hvalue && x.rhvalue == y.rhvalue) return true;
        return false;
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
        vector<ll> gi = vector(g[i].begin(), g[i].end());
        s_without_itself.push_back(Object{i, hash.once(gi), hash.ronce(gi)});
        gi.push_back(i);
        sort(gi.begin(), gi.end());
        s_with_itself.push_back(Object{i, hash.once(gi), hash.ronce(gi)});
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
/*
You have been offered a job in a company developing a large social network. Your first task is connected with searching profiles that most probably belong to the same user.

The social network contains n registered profiles, numbered from 1 to n. Some pairs there are friends (the "friendship" relationship is mutual, that is, if i is friends with j, then j is also friends with i). Let's say that profiles i and j (i ≠ j) are doubles, if for any profile k (k ≠ i, k ≠ j) one of the two statements is true: either k is friends with i and j, or k isn't friends with either of them. Also, i and j can be friends or not be friends.

Your task is to count the number of different unordered pairs (i, j), such that the profiles i and j are doubles. Note that the pairs are unordered, that is, pairs (a, b) and (b, a) are considered identical.

Input
The first line contains two space-separated integers n and m (1 ≤ n ≤ 106, 0 ≤ m ≤ 106), — the number of profiles and the number of pairs of friends, correspondingly.

Next m lines contains descriptions of pairs of friends in the format "v u", where v and u (1 ≤ v, u ≤ n, v ≠ u) are numbers of profiles that are friends with each other. It is guaranteed that each unordered pair of friends occurs no more than once and no profile is friends with itself.

Output
Print the single integer — the number of unordered pairs of profiles that are doubles.

Please do not use the %lld specificator to read or write 64-bit integers in С++. It is preferred to use the %I64d specificator.
Examples
input
3 3
1 2
2 3
1 3
output
3
input
3 0
output
3
input
4 1
1 3
output
2
Note
In the first and second sample any two profiles are doubles.

In the third sample the doubles are pairs of profiles (1, 3) and (2, 4).

*/
