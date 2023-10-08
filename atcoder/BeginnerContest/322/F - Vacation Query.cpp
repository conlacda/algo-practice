// https://atcoder.jp/contests/abc322/tasks/abc322_f
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Lznode {
    int val = 0;
    bool is_null = true;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return Lznode{
            (first.val + second.val) % 2,
            false
        };
    }
    static Lznode v(int val) {
        return Lznode {
            val,
            false
        };
    }
    friend std::ostream& operator<<(std::ostream& os, const Lznode& s) { return os << destructure(s);}
};

struct Node {
    int zero_pre = 0;
    int zero_suf = 0;
    int zero_all = 0;
    int one_pre = 0;
    int one_suf = 0;
    int one_all = 0;
    int size = 1; // để mặc định là 1. Sử dụng trong hàm apply
    bool is_null = true;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node {
            l.zero_pre == l.size ? l.zero_pre + r.zero_pre: l.zero_pre,
            r.zero_suf == r.size ? l.zero_suf + r.zero_suf: r.zero_suf,
            max({l.zero_all, r.zero_all, l.zero_suf + r.zero_pre}),
            l.one_pre == l.size ? l.one_pre + r.one_pre : l.one_pre,
            r.one_suf == r.size ? r.one_suf + l.one_suf : r.one_suf,
            max({l.one_all, r.one_all, l.one_suf + r.one_pre}),
            l.size + r.size,
            false
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.is_null || lz.val == 0) return;
        swap(zero_pre, one_pre);
        swap(zero_suf, one_suf);
        swap(zero_all, one_all);
    }
    static Node v(int val) {
        if (val == 0) {
            return {
                1, 1, 1,
                0, 0, 0,
                1,
                false
            };
        }
        return {
            0, 0, 0,
            1, 1, 1,
            1,
            false
        };
    }
    Node operator!() { return *this; } // dùng cho thao tác query có xét chiều. Node a + Node b = !(Node b + Node a)
    friend std::ostream& operator<<(std::ostream& os, const Node& s) { return os << destructure(s);}
};

struct LazySegtree {
  public:
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
    vector<Node> original() {
        vector<Node> result;
        for (int i=0;i<N;i++) {
            result.push_back(query(i, i));
        }
        return result;
    }
};
// http://localhost:3000/docs/competitive-programming/range-queries/lazy-segment-tree

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<Node> a;
    for (auto &v: s) a.push_back(Node::v(v - '0'));
    LazySegtree seg;
    seg.build(a);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        if (t == 1) {
            // Đảo
            seg.update(l, r, Lznode::v(1));
        } else {
            auto node = seg.query(l, r);
            cout << node.one_all <<'\n';
            // Query đưa ra độ dài range 1 lớn nhất
        }
    }
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/
