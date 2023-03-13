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

template<class T> struct LSegTree { // 0-based indexing
    int N; vector<T> t, lz; T U=-1e18;
    T F(T i, T j) { 
        return max(i,j); // comb() function
    } LSegTree() {}
    LSegTree(int N) : N(N), t(4*(N+1),U), lz(4*(N+1),0) {}
    void pull(int i) { t[i] = F(t[i*2],t[i*2+1]); }
    void push(int i, int l, int r) {
        t[i]+=lz[i];
        if(l!=r) lz[i*2]+=lz[i], lz[i*2+1]+=lz[i];
        lz[i]=0; }
    void build(vector<ll> &v) { build(v,1,0,N); }
    void build(vector<ll> &v, int i, int l, int r) {
        if(l==r) { t[i]=v[l]; return; } int m=(l+r)/2;
        build(v,i*2,l,m); build(v,i*2+1,m+1,r); pull(i);
    }
    // Add v to range L->R 
    void update(int L, int R, T v) { update(L,R,v,1,0,N); }
    void update(int L, int R, T v, int i, int l, int r) {
        push(i,l,r); if(R<l || L>r) return;
        if(L<=l && R>=r) { lz[i]+=v; push(i,l,r); return; }
        int m=(l+r)/2; update(L,R,v,i*2,l,m);
        update(L,R,v,i*2+1,m+1,r); pull(i);
    }
    T query(int L, int R) { return query(L,R,1,0,N); }
    T query(int L, int R, int i, int l, int r) {
        push(i,l,r); if(R<l || L>r) return U;
        if(L<=l && R>=r) return t[i]; int m=(l+r)/2;
        return F(query(L,R,i*2,l,m), query(L,R,i*2+1,m+1,r));
    }
    // Retrieve current state of vector
    vector<T> original() {
        vector<T> ans;
        for (int i=0;i<N;i++){
            ans.push_back(query(i, i));
        }
        return ans;
    }
};
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(10);
    ll n, b, q;
    cin >> n >> b >> q;
    vector<ll> a(n);
    ll cur = 0;
    vector<ll> prefix_sum;
    for (ll i=0;i<n;i++) {
        cin >> a[i]; a[i]-=b;
        cur += a[i];
        prefix_sum.push_back(cur);
    }
    LSegTree<ll> seg(n);
    seg.build(prefix_sum);
    for (ll i=0;i<q;i++) {
        ll u, v;
        cin >> u >> v; u--; v-=b;
        // cap nhat
        seg.update(u, n-1, v - a[u]);
        a[u] = v;
        // truy van roi in ra - lay ra index nho nhat ma lon hon 0
        ll left = 0, right = n-1;
        while (left != right) {
            ll mid = (left + right) /2;
            if (seg.query(0, mid) >= 0) {
                right = mid;
            } else left = mid+1;
        }
        if (seg.query(0, left) >=0) {
            cout << (double) seg.query(0, left) / (left+1) + b <<'\n';
        } else {
            cout << (double) seg.query(n-1, n-1) / n + b <<'\n';
        }
    }
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
// https://atcoder.jp/contests/abc292/tasks/abc292_h
