#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// Range query, point update
template <typename T>
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
        dbg(l, r);
        assert(0 <= l && l <= r && r < n);
        return sum(r) - sum(l-1);
    }

    void add(T idx, T delta) {
        assert(0 <= idx && idx < n);
        for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
    }
    void set(T idx, T val) {
        T diff = val - sum(idx, idx);
        add(idx, diff);
    }

    vector<T> original(){ // Return original value of input vector
        vector<T> a;
        for (T i=0;i<this->n;i++) a.push_back(sum(i,i));
        return a;
    }
};
/*
FenwickTree<int> fw;
fw.build(vector<int> a{1,2,3,4,5});
fw.build(n);
fw.sum(l,r) // sum[l:r] -> fw.sum(r) = fw.sum(r, r)
fw.add(r, k) // a[r] = a[r] + k
fw.set(i, val);
*/
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    sort(a.begin(), a.end());
    /*
    Bruteforce, 1 doan dau, k- doan sau
    */
    FenwickTree<int> fw;
    fw.build(a);
    dbg(a);
    int ans = INF;
    for (int i=0;i<=k;i++) {
        // Tinh left
        int left = (i==0) ? 0: fw.sum(0, i*2-1);
        // Tinh right
        int pr = k-i;
        int right = (i==k) ? 0: fw.sum(n-pr, n-1);
        // dbg(i, left, pr, right);
        ans = min(ans, left+ right);
    }
    // dbg(ans);
    int sum =0;
    for (auto v: a) sum += v;
    cout << sum - ans <<'\n';
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
