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
    int val = 0; // Node x; assert(x.apply(LzNode()) == x)
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        return Lznode{
            max(first.val, second.val)
        };
    }
};

struct Node {
    int val = 0;
    bool is_null = true;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node{
            0,
            false
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
       val = max(lz.val, val);
    }

    static Node v(int val) {
        return {
            val,
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

    template <bool (*g)(Node)> int max_right(int l) {
        return max_right(l, [](Node x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= N);
        assert(g(Node()));
        if (l == N) return N;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        Node sm = Node();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(Node::merge(sm, data[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(Node::merge(sm, data[l]))) {
                        sm = Node::merge(sm, data[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = Node::merge(sm, data[l]);
            l++;
        } while ((l & -l) != l);
        return N;
    }

    template <bool (*g)(Node)> int min_left(int r) {
        return min_left(r, [](Node x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= N);
        assert(g(Node()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        Node sm = Node();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(Node::merge(data[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(Node::merge(data[r], sm))) {
                        sm = Node::merge(data[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = Node::merge(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
// http://localhost:3000/docs/competitive-programming/range-queries/lazy-segment-tree


signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<Node> a(n, Node::v(0));
    LazySegtree seg;
    seg.build(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            // update
            int l, r, val;
            cin >> l >> r >> val;
            --r;
            seg.update(l, r, Lznode{val});
        } else {
            // query
            int index;
            cin >> index;
            auto node = seg.query(index, index);
            cout << node.val << '\n';
        }
    }
    
    show_exec_time();
}
