// https://atcoder.jp/contests/abc341/tasks/abc341_e
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

struct Lznode {
    int val = 0; // Node x; assert(x.apply(LzNode()) == x) // ***
    bool is_null = false;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return Lznode {
            (first.val + second.val) % 2, // ***
        };
    }
};

struct Node {
    char lval = '0'; // ***
    char rval = '0'; // ***
    bool good = true;
    bool is_null = false;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        if (!l.good || !r.good) return Node {.good = false};
        bool _good = true;
        if (l.rval == r.lval) _good = false;
        return Node {
            l.lval,
            r.rval,
            _good
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.is_null || lz.val == 0) return;
        dbg(lz.val, lval, rval);
        if (lval == '0') lval = '1'; else lval = '0';
        if (rval == '0') rval = '1'; else rval = '0';
        dbg(lz.val, lval, rval);
    }
    Node operator!() { return *this; } // dùng cho thao tác query có xét chiều. Node a + Node b = !(Node b + Node a)
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
        lz[k] = Lznode{.is_null = true};
    }
  public:
    LazySegtree() {}
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
    vector<Node> original() {
        vector<Node> result;
        for (int i=0;i<N;i++) {
            result.push_back(query(i, i));
        }
        return result;
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
    string s;
    cin >> s;
    vector<Node> sega;
    for (auto v: s) sega.push_back(Node{v, v});
    LazySegtree seg;
    seg.build(sega);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        if (t == 1) {
            // flip
            seg.update(l, r, Lznode{1});
        } else {
            // query
            auto node = seg.query(l, r);
            if (node.good) cout << "Yes\n";
            else cout << "No\n";
        }
    }


    show_exec_time();
}

