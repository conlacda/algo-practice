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


/*
Code with new template
// [Atcoder|Codeforces].abcxxx.F
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

template<typename Node, typename Lznode>
struct LazySegtree {
  private:
    int N, size, log;
    vector<Node> data;
    vector<Lznode> lz;

    void update(int k) { data[k] = Node::merge(data[2 * k], data[2 * k + 1]); }
    void all_apply(int k, Lznode lzn) {
        lzn.applyTo(data[k]); // template is a bit weird.
        if (k < size) lz[k] = Lznode::composition(lz[k], lzn);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = Lznode{.is_null = true};
    }
  public:
    LazySegtree() {}
    LazySegtree(std::vector<Node>& v) {build(v);}
    void build(const std::vector<Node>& v) {
        this->N = (int) v.size();
        log = 0; while ((1U << log) < (unsigned int)(N)) log++; 
        size = 1 << log;
        data.resize(2 * size, Node{.is_null = true});
        lz.resize(size, Lznode{.is_null = true});
        for (int i = 0; i < N; i++) data[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, Node x) {
        assert(0 <= p && p < N);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        data[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    template<class... P> void set(int index, P... params) { set(index, Node{params...});}

    Node query(int l, int r) {
        r++;
        assert(0 <= l && l <= r && r <= N);
        if (l == r) return Node{.is_null = true};

        l += size; r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        Node sml = Node{.is_null = true}, smr = Node{.is_null = true};
        while (l < r) {
            if (l & 1) sml = Node::merge(sml, data[l++]);
            if (r & 1) smr = Node::merge(data[--r], smr);
            l >>= 1; r >>= 1;
        }

        return Node::merge(sml, smr);
    }

    Node query_all() { return data[1]; }

    void update(int l, int r, Lznode lznode) {
        r++; assert(0 <= l && l <= r && r <= N);
        if (l == r) return;
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, lznode);
            if (r & 1) all_apply(--r, lznode);
            l >>= 1; r >>= 1;
        }
        l = l2; r = r2;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    template<class... P> void update(int l, int r, P... params) { update(l, r, Lznode{params...});}

    vector<Node> original() {
        vector<Node> result;
        for (int i=0;i<N;i++) {
            result.push_back(query(i, i));
        }
        return result;
    }
};

struct MinNode {
    int val = 0;
    int size = 1; // để mặc định là 1. Sử dụng trong hàm apply
    bool is_null = false;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static MinNode merge(MinNode l, MinNode r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return {
            max(l.val, r.val),
            l.size + r.size, // size
        };
    }
    friend MinNode operator+(MinNode l, MinNode r) { return MinNode::merge(l, r); }

    MinNode operator!() { return *this; } // dùng cho thao tác query có xét chiều. Node a + Node b = !(Node b + Node a)
    friend std::ostream& operator<<(std::ostream& os, const MinNode& s) { return os << destructure(s);}
};
using Node = MinNode;

struct AxPlusBLznodeForMinNode {
    int a = 1; // x = ax+b -> a = 1, b = 0
    int b = 0;
    bool is_null = false;
    // Apply 1 node lần thứ 2
    static AxPlusBLznodeForMinNode composition(AxPlusBLznodeForMinNode first, AxPlusBLznodeForMinNode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return {
            // (a1x+b1)*a2+b2 = (a1a2)x+(b1a2+b2)
            first.a * second.a,
            first.b * second.a + second.b
        };
    }
    void applyTo(MinNode& node) {
        if (this->is_null) return;
        node.val = node.val * this->a + this->b;
    }
};
using Lznode = AxPlusBLznodeForMinNode;

signed main(){
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
    vector<int> prefix_sum;
    for (int i=0;i<n;i++) {
        cin >> a[i]; a[i]-=b;
        cur += a[i];
        prefix_sum.push_back(cur);
    }
    vector<Node> arr;
    for (auto v: prefix_sum) arr.push_back({v});
    LazySegtree<Node, Lznode> seg;
    seg.build(arr);
    for (ll i=0;i<q;i++) {
        ll u, v;
        cin >> u >> v; u--; v-=b;
        // cap nhat
        seg.update(u, n-1, 1, v - a[u]);
        a[u] = v;
        // truy van roi in ra - lay ra index nho nhat ma lon hon 0
        ll left = 0, right = n-1;
        while (left != right) {
            ll mid = (left + right) /2;
            if (seg.query(0, mid).val >= 0) {
                right = mid;
            } else left = mid+1;
        }
        if (seg.query(0, left).val >=0) {
            cout << (double) seg.query(0, left).val / (left+1) + b <<'\n';
        } else {
            cout << (double) seg.query(n-1, n-1).val / n + b <<'\n';
        }
    }
    

    show_exec_time();
}
*/
