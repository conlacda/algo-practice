#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
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

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    FenwickTree<ll> fw;
    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    for (auto &v: a) cin >> v;
    fw.build(a);
    for (ll i=0;i<q;i++) {
        ll t, l, r;
        cin >> t >> l >> r;
        if (t == 0) {
            fw.add(l, r);
        } else cout << fw.sum(l, r-1) <<'\n';
    }

    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
