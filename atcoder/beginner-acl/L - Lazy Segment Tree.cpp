#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
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

struct Lznode {
    int updated = 0;
    static Lznode composition(Lznode first, Lznode second) {
        return Lznode{
            (first.updated + second.updated) % 2
        };
    }
};

struct Node {
    int val = 0;
    int zero = 0;
    int one = 0;
    bool is_null = true;
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node{
            l.val + r.val + l.one * r.zero,
            l.zero + r.zero,
            l.one + r.one,
            false
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.updated == 0) return;
        *this = {
            this->one * this->zero - this->val, // dòng này là khó nhìn ra nhất
            this->one,
            this->zero,
            false
        };
    }
    static Node v(int val) {
        return {
            0,
            (val == 0) ? 1 : 0,
            (val == 1) ? 1 : 0,
            false
        };
    }
    Node operator!() { return *this; }
    friend std::ostream& operator<<(std::ostream& os, const Node& s) { return os << destructure(s);}
};

struct LazySegtree {
  private:
    int N, size, log;
    vector<Node> data;
    vector<Lznode> lz;

    void update(int k) { data[k] = Node::merge(data[2 * k], data[2 * k + 1]); }
    void all_apply(int k, Lznode lzn) {
        data[k].apply(lzn);
        if (k < size) lz[k] = Lznode::composition(lz[k], lzn);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = Lznode();
    }
  public:
    LazySegtree() {}
    void build(const std::vector<Node>& v) {
        this->N = (int) v.size();
        log = 0; while ((1U << log) < (unsigned int)(N)) log++; 
        size = 1 << log;
        data.resize(2 * size, Node());
        lz.resize(size, Lznode());
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

    Node query(int l, int r) {
        r++;
        assert(0 <= l && l <= r && r <= N);
        if (l == r) return Node();

        l += size; r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        Node sml = Node(), smr = Node();
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
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<Node> a(n);
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        a[i] = Node::v(x);
    }
    LazySegtree seg;
    seg.build(a);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            seg.update(--u, --v, Lznode{1});
        } else {
            // query
            auto node = seg.query(--u, --v);
            cout << node.val << '\n';
        }
    }
    show_exec_time();
}
