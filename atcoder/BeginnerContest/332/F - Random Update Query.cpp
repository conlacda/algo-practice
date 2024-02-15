// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

const int maxN = 1000003;
vector<ll> factorial, factorial_inv; // giai thừa
template<unsigned int mod = mod>
struct Mint {
    friend std::ostream& operator<<(std::ostream& os, const Mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, Mint &s) { 
        os >> s.x;
        s.normalize();
        return os;
    }
    unsigned int x;
 
    Mint() : x(0) {}
    Mint(ll _x) { // auto convert ll to Mint.
        x = _x;
        normalize();
    }
    void normalize() {
        x %= mod;
        if (x < 0) x += mod;
    }
    unsigned int val() {
        return x;
    }

    Mint& operator += (const Mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator -= (const Mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator *= (const Mint &a) {
        x = (unsigned long long)x * a.x % mod;
        return *this;
    }
    Mint& operator /= (const Mint &a) {
        return *this *= a.inv();
    }

    Mint power(ll pw) const {
        Mint res = 1;
        Mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    // Chứng minh xem tại CPH - Modular inverse
    Mint inv() const {
        assert(x != 0);
        unsigned int t = x;
        unsigned int res = 1;
        while(t != 1) {
            unsigned int z = mod / t;
            res = (unsigned long long)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    
    Mint operator + (const Mint &a) const {
        return Mint(*this) += a;
    }
    Mint operator - (const Mint &a) const {
        return Mint(*this) -= a;
    }
    Mint operator * (const Mint &a) const {
        return Mint(*this) *= a;
    }
    Mint operator / (const Mint &a) const {
        return Mint(*this) /= a;
    }
 
    bool operator == (const Mint &a) const {
        return x == a.x;
    }
    bool operator != (const Mint &a) const {
        return x != a.x;
    }
    bool operator < (const Mint &a) const {
        return x < a.x;
    }
    
    // Hàm này chỉ chạy với n,r < maxN (~ 1e6)
    Mint nCr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (r < 0 || this->x < r.x) return 0;
        if (factorial.size() == 0) cal_factor();
        return Mint(factorial[x]) * Mint(factorial_inv[r.x]) * Mint(factorial_inv[x-r.x]);
    }
    Mint nPr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (x < r.x) return 0; // xC(r.x)
        if (factorial.size() == 0) cal_factor();
        return Mint(factorial[x]) * Mint(factorial_inv[x-r.x]);
    }
private:
    void cal_factor() { std::function<vector<ll>(int)> mod_inv_range = [&](int sz){ vector<ll> inv(sz, 1); for (int i=2;i<sz;i++){ inv[i] = mod - (mod/i) * inv[mod%i] % mod;} return inv;}; factorial.resize(maxN, 1); factorial_inv.resize(maxN, 1); vector<ll> inv = mod_inv_range(maxN); for (ll i=1;i < (int) factorial.size();i++){ factorial[i] = (factorial[i-1] * i) % mod; factorial_inv[i] = (factorial_inv[i-1] * inv[i]) %mod;}}
};
using mint = Mint<mod>;

struct Lznode {
    mint val = 0; // Node x; assert(x.apply(LzNode()) == x) // ***
    mint pos = 0;
    bool is_null = true;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        mint newpos = first.pos + second.pos - first.pos * second.pos;
        return Lznode {
            (first.val * first.pos - first.val * first.pos * second.pos + second.val * second.pos) / newpos,
            newpos,
            false // is_null
        };
    }
    static Lznode v(mint val, mint pos) {
        return Lznode {
            val, // ***
            pos,
            false // is_null
        };
    }
};

struct Node {
    mint val = 0; // ***
    bool is_null = true;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node {
            l.val + r.val, // ***
            false // is_null
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.is_null) return;
        val = val * (mint(1) - lz.pos) + lz.val * lz.pos;
    }
    static Node v(mint val) {
        return {
            val, // ***
            false // is_null
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
        dbg(l, r);
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
    int n, q;
    cin >> n >> q;
    vector<Node> a(n);
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        a[i] = Node::v(mint(x));
    }
    LazySegtree seg;
    seg.build(a);
    while (q--) {
        int l, r; mint val;
        cin >> l >> r >> val;
        l--; r--;
        seg.update(l, r, Lznode::v(val, mint(1) / (r-l+1)));
    }
    for (int i=0;i<n;i++) {
        auto node = seg.query(i, i);
        cout << node.val << ' ';
    }
    show_exec_time();
}
/*
Node chứa val
Lznode chứa val và posibility
-> các hàm merge, composition, ... có thể dễ dàng (dùng nháp là ra)
*/
