#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 998244353;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

/*
các thuộc tính cho hàm cập nhật x = a*x+b -> có 2 thuộc tính a,b
*/
struct Lznode { // F()
    ll a = 1; // a*1+0=a
    ll b = 0;
    /*
    Composition của hàm cập nhật f(g(x)) trả về các thuộc tính của F
    Composition() - f∘g(x) = f(g(x))
    g(x) = a1*x+b1
    f∘g(x) = f(g(x)) = (a1*x+b1)*a2+b2
                     = (a1*a2)x + (b1*a2+b2) 
    -> composition(F l, F r) = F {a1*a2, b1*a2+b2}
                                F{r.a * l.a, r.b * l.a + l.b};
    */
    static Lznode composition(Lznode l, Lznode r) {
        return Lznode{(l.a * r.a) %mod, (r.b * l.a + l.b)%mod};
    }
};

struct Node {
    ll val = 0;
    ll size = 0;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        return Node{
            (l.val + r.val) % mod,
            (l.size + r.size)% mod
        };
    }
    void apply(Lznode lz) {
        *this = Node {
            (val * lz.a + size * lz.b) % mod,
            this->size % mod
        };
        /*
        Hàm thể hiện cập nhật từ lazy tree vào segment tree
        mapping()
        Hình dung segment tree
                ----
            (5)--    --
           (1)--(4)  - - 
        xét cục -- có sum = 5(bằng tổng của 2 cục bên dưới) và len=2
        -> mapping Sum này với Lznode(b,c) -> 5*b+2*c = S.sum*b+S.len*c
        Lý giải: Mapping với Lznode(b,c) -> 1*b+c+4*b+c = 5*b + 2*c = sum*b+len*c
        */
    }
    friend std::ostream& operator<<(std::ostream& os, const Node& s) { return os << destructure(s);}
};

struct LazySegtree {
  private:
    int N, size, log;
    std::vector<Node> data;
    std::vector<Lznode> lz;

    void update(int k) { data[k] = Node::merge(data[2 * k], data[2 * k + 1]); } //merge()
    void all_apply(int k, Lznode f) {
        data[k].apply(f);
        if (k < size) lz[k] = Lznode::composition(f, lz[k]);
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
        // log = ceil_pow2(N);
        log = 0; while ((1U << log) < (unsigned int)(N)) log++; 
        size = 1 << log;
        data = std::vector<Node>(2 * size, Node());
        lz = std::vector<Lznode>(size, Lznode());
        for (int i = 0; i < N; i++) data[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, Node x) {
        assert(0 <= p && p < N);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        data[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    Node get(int p) {
        assert(0 <= p && p < N);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return data[p];
    }

    Node query(int l, int r) {
        assert(0 <= l && l <= r && r <= N);
        if (l == r) return Node();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        Node sml = Node(), smr = Node();
        while (l < r) {
            if (l & 1) sml = Node::merge(sml, data[l++]); // merge()
            if (r & 1) smr = Node::merge(data[--r], smr); // merge()
            l >>= 1;
            r >>= 1;
        }

        return Node::merge(sml, smr); // merge()
    }

    Node all_prod() { return data[1]; }

    void apply(int p, Lznode f) {
        assert(0 <= p && p < N);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        data[p].apply(f);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, Lznode f) {
        assert(0 <= l && l <= r && r <= N);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1;
            r >>= 1;
        }
        l = l2;
        r = r2;

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
            if (!g(Node::merge(sm, data[l]))) { // merge()
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(Node::merge(sm, data[l]))) { //merge()
                        sm = Node::merge(sm, data[l]); //merge()
                        l++;
                    }
                }
                return l - size;
            }
            sm = Node::merge(sm, data[l]); //merge()
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
            if (!g(Node::merge(data[r], sm))) { // //merge()
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(Node::merge(data[r], sm))) { //merge()
                        sm = Node::merge(data[r], sm); //merge()
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = Node::merge(data[r], sm); //merge()
        } while ((r & -r) != r);
        return 0;
    }
};

/* merge(Node A + NodeZero) = Node A
Hàm này chạy ở phần rìa. 
Ví dụ: mảng a có 7 phần tử -> khởi tạo sẽ ra 7 node. Cần 1 nodeZero ở cuối để tạo ra 2^n node
-> merge(Node7, Node8 = NodeZero) = Node7
*/


/*
Định danh các tham số cho node ban đầu (dưới đáy) 
Hàm update = ax+b -> x = 1*x+0-> id= F{1,0};
*/

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;

    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = Node{x, 1};
    }

    LazySegtree seg;
    seg.build(a);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            int c, d;
            cin >> l >> r >> c >> d;
            seg.apply(l, r, Lznode{c, d});
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.query(l, r).val << '\n';
        }
    }
    show_exec_time();
}
