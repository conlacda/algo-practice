// https://codeforces.com/edu/course/2/lesson/5/3/practice/contest/280799/problem/C
// C. Addition and First element at least X

#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
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
    bool is_null = true;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return Lznode{
            first.val + second.val, // hàm cộng. Cộng 2 lần thì sẽ cộng 2 giá trị với nhau là xong
            false
        };
    }
    static Lznode v(int val) {
        return Lznode {
            val,
            false
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
            max(l.val, r.val), // tìm giá trị đầu tiên thì lấy hàm max. rồi binary search từ l->mid để tìm ra vị trí đầu tiên có giá trị >= val
            false
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.is_null) return;
        val = val + lz.val; // đoạn này không phải là lz.val * size
        // lưu ý rằng 1 node to có giá trị k. Khi thêm 1 lượng k vào toàn bộ node con của nó
        // thì giá trị node to cũng tăng 1 lượng k.
    }
    static Node v(int val) {
        return {
            val,
            false
        };
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
    vector<Node> a(n, Node::v(0));
    LazySegtree seg;
    seg.build(a);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            // update
            int l, r, val;
            cin >> l >> r >> val;
            r--;
            seg.update(l, r, Lznode::v(val));
        } else {
            dbg(seg.original());
            // query
            int index, val;
            cin >> val >> index;
            int left = index, right = n-1;
            while (left < right) {
                int mid = (left + right) / 2;
                auto node = seg.query(index, mid);
                if (node.val >= val) {
                    right = mid;
                } else left = mid +1;
            }
            auto node = seg.query(index, right);
            if (node.val < val) {
                cout << -1 << '\n';
            } else
            cout << right << '\n';
        }
    }
    
    show_exec_time();
}
