// https://atcoder.jp/contests/abc347/tasks/abc347_e
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// Range query, point update
template <typename T = int>
struct FenwickTree {
private:
    vector<T> bit; // binary indexed tree
    T n;
public:
    FenwickTree(){}
    void build(T n) { this->n = n; bit.assign(n, 0); }
    void build(vector<T> a) { build(a.size()); for (int i = 0; i < (int) a.size(); i++) add(i, a[i]); }
    FenwickTree(vector<T> a) { build(a); }
    T sum(T r) {
        if (r==-1) return 0;
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
        return ret;
    }

    T sum(T l, T r) {
        assert(0 <= l && l <= r && r < n);
        return sum(r) - sum(l-1);
    }

    void add(T idx, T delta) {
        assert(0 <= idx && idx < n);
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Cho 1 dãy số với các index sẽ được turnon/off theo bit
    mỗi lần tăng toàn bộ số của dãy số lên k đơn vị nếu index đó được turn on
    Hỏi giá trị cuối cùng của dãy là bao nhiêu.
    -> Track timeline thì sao??
    Ta có thời điểm t thì s có size tính được
    Mỗi index sẽ biết được nó tồn tại từ thời gian nào tới thời gian nào
    -> tối đa là N lần thay đổi giá trị -> tạo ra N range
    query sum range là xong
    */
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    for (auto&v: a) cin >> v;
    vector<int> size;
    set<int> s;
    map<int, vector<pair<int,int>>> timeline; //timeline[i] = {start, end};
    map<int, int> start;
    for (auto v: a) start[v] = -1;
    for (int i=0;i<k;i++) {
        auto v = a[i];
        if (s.count(v) > 0) {
            timeline[v].push_back({start[v], i-1});
            s.erase(v);
            start[v] = -1;
        } else {
            s.insert(v);
            start[v] = i;
        }
        size.push_back(s.size());
    }
    for (auto v: start) {
        if (v.second != -1) {
            timeline[v.first].push_back({v.second, k-1});
        }
    }
    for (auto v: timeline) dbg(v.first, v.second);
    dbg(size);
    FenwickTree<int> fw;
    fw.build(size);
    for (int i=0;i<n;i++) {
        int ans = 0;
        for (auto v: timeline[i+1]) {
            ans += fw.sum(v.first, v.second);
        }
        cout << ans << ' ';
    }

    show_exec_time();
}
