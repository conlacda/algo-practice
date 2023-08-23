// https://codeforces.com/edu/course/2/lesson/5/4/practice/contest/280801/problem/B
// B. Add Arithmetic Progression On Segment
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
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
    int cnst = 0;
    int d = 0;
    bool is_null = true;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return Lznode{
            first.cnst + second.cnst,
            first.d + second.d,
            false
        };
    }
    static Lznode v(int cnst, int d) {
        return Lznode {
            cnst,
            d,
            false
        };
    }
};

struct Node {
    int val = 0;
    int index = 0;
    bool is_null = true;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node{
            0,
            0,
            false
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.is_null) return;
        val += lz.cnst + lz.d * index;
    }
    static Node v(int val, int index) {
        return {
            val,
            index,
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
    cout << std::fixed << setprecision(15);
//     xi+=a+d⋅(i−l)
// x += a + di - dl
// dl là hằng số, a hằng số,
// di phụ thuộc vào từng số
    int n, q;
    cin >> n >> q;
    vector<Node> a;
    for (int i=1;i<=n;i++) {
        a.push_back(Node::v(0, i));
    }
    LazySegtree seg; seg.build(a);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, a, d;
            cin >> l >> r >> a >> d;
            l--; r--;
            seg.update(l, r, Lznode::v(a - d*(l+1), d));
        } else {
            int index; cin >> index; index--;
            auto node = seg.query(index, index);
            cout << node.val << '\n';
        }
    }
    show_exec_time();
}
/*
Bài này chỉ đơn giản là mỗi lần query nó tăng lên 1 lượng cụ thể và d*i
d là số đã cho, i là index.
Lazy node chỉ cần lưu 2 phần là 1 lượng cụ thể gọi là cnst, và số d.
Hàm merge() thì bỏ trống (merge thành cái gì cũng được) vì chỉ query 1 phần tử chứ ko query range
apply lazynode thì đơn giản là cộng vào là xong
*/
