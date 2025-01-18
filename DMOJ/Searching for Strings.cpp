// https://dmoj.ca/problem/ccc20s3
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

template<typename Node>
class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(const vector<Node>& v){ build(v);}
    void build(const vector<Node>& v) {
        n = 1; while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1, Node{.is_null = true});
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
    void set(int index, Node x) {
        index += n - 1;
        dat[index] = x;
        while (index > 0) {
            index = (index - 1) / 2;
            dat[index] = dat[index * 2 + 1] + dat[index * 2 + 2];
        }
    }
    Node query(int l, int r){
        assert(l <= r);
        Node left = Node{.is_null = true}, right = Node{.is_null = true};
        l += n - 1; r += n;
        while (l < r) {
            if ((l & 1) == 0) left = left + dat[l];
            if ((r & 1) == 0) right = dat[r - 1] + right;
            l = l / 2; r = (r - 1) / 2;
        }
        return left + right;
    }
};

struct Node {
    int sum = 0;
    int _xor = 0;
    bool is_null = false;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return Node{
            a.sum + b.sum,
            a._xor ^ b._xor
        };
    }
};

template<class Iterable = string> // chỉ chạy với 64bit.
class Hash {
private:
    const ll factor = 263; // số nguyên tố lớn hơn 255 - là full bảng Acsii
    const char min_char = 0x00; // kí tự 0
    vector<ll> inv, pc; // pre-compute
    ll n;
    // a*x ≡ 1 mod m -> find x - xem thêm tại math-compilation snippet
    ll mod_inv(ll a) { ll x, y;auto extended_gcd = [&] (ll a, ll b) -> ll { x = 1; y =0; ll x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) {ll q = a1 / b1;tie(x, x1) = make_tuple(x1, x - q * x1);tie(y, y1) = make_tuple(y1, y - q * y1);tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;};ll g = extended_gcd(a, mod);if (g != 1) return -1;else x = (x%mod +mod) %mod;return x;}
    int toInt(char x) { // char(127) = 127 nhưng char(128) = -127, ... char(255) = -1 
        int valOfChar = x - min_char + 1;
        int res = (valOfChar <= 0) ? valOfChar + 256 : valOfChar;
        assert(res > 0 && "min_char phải nhỏ hơn s[i]");
        return res;
    }
    int toInt(int x) {
        return x - min_char + 1;
    }
public:
    Iterable s;
    vector<ll> prefix_hash, suffix_hash;
    void build(ll length = 250000){ ll p = 1; for (ll i=0;i<length;i++){ pc.push_back(p); p = (p* factor) % mod;} for (auto v: pc) inv.push_back(mod_inv(v));}
    // Precompute O(N) dạng prefix sum để sau tính hash từ l->r với O(1).     
    void load(Iterable s) {
        assert((int) pc.size() >= (int) s.size() && "quên chưa hash.build()??");
        this->s = s; this->n = (ll) s.size();
        prefix_hash = suffix_hash = {0};
        ll pre = 0, suf = 0;
        for (int i=0;i< (int) s.size();i++) {
            pre = (pre + toInt(s[i]) * pc[i]) % mod;
            suf = (suf + toInt(s[(int) s.size() - i - 1]) * pc[i]) % mod;
            prefix_hash.push_back(pre);
            suffix_hash.push_back(suf);
        }
    }
    // Lấy ra hash của s.substr(start, length)
    ll substr(ll start, ll length) {
        assert(length <= n); // assert(start+length <= n); nếu chỉ muốn range thông thường ko phải dạng rolling
        ll end = (start + length > n) ? (start + length - n -1) : (start+length-1);
        // hash dạng rolling substr- tức là nếu start+length> s.size() thì sẽ vòng lại lấy từ đầu đi tiếp
        std::function<int(ll, ll, vector<ll>&)> hashOfSubstr = [&](ll start, ll length, vector<ll>& ps_hash){
            ll ans = 0;
            if (start + length <= n) {
                ans = (ps_hash[start + length] - ps_hash[start] + mod) % mod;
                return (ans * inv[start]) % mod;
            }
            ll start2ssize = (ps_hash[n] - ps_hash[start] + mod) % mod;
            start2ssize = (start2ssize * inv[start]) % mod;
            ll zero2end = ps_hash[length + start - n];
            ans = (start2ssize + zero2end * pc[n - start]) % mod;
            if (ans < 0) ans += mod;
            return ans;
        };
        return (ll) hashOfSubstr(start, length, prefix_hash) << 32 | hashOfSubstr(n - 1 - end, length, suffix_hash);
    }
};

mt19937 _rand(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string a, b;
    cin >> a >> b;
    Hash<string> hsh;
    hsh.build((int) b.size() + 5);
    hsh.load(b);
    map<char, int> m;
    for (auto&v: a) {
        if (!m.contains(v))
            m[v] = _rand();
    }
    for (auto&v: b) {
        if (!m.contains(v))
            m[v] = _rand();
    }
    vector<Node> aa(a.size()), bb(b.size());
    for (int i=0;i< (int) a.size();i++) aa[i] = Node{m[a[i]], m[a[i]]};
    for (int i=0;i< (int) b.size();i++) bb[i] = Node{m[b[i]], m[b[i]]};
    SegmentTree<Node> seg1(aa), seg2(bb);
    auto node = seg1.query(0, (int) aa.size() - 1);
    int ans = 0;
    set<int> matched;
    for (int i=0;i<=(int) bb.size() - (int) aa.size();i++) {
        auto node2 = seg2.query(i, i + (int) a.size() - 1);
        if (node.sum == node2.sum and node._xor == node2._xor) {
            auto hash_value = hsh.substr(i, a.size());
            if (matched.count(hash_value) == 0) {
                ans++;
                matched.insert(hsh.substr(i, a.size())); 
            }
        }
    }
    cout << ans;
    /*
    Nếu lặp qua toàn bộ permutation(a) rồi check trong string b thì quá chậm
    Sử dụng hash thì mỗi string a lặp qua b mất O(N)
    Tổng sẽ là O(N^2)

    Observation:
    nếu permuatation(a) match với b[L:R] thì số lượng các chữ cái có trong a sẽ bằng số lượng các chữ cái có trong b
    ví dụ: a = aab b = cabad thì a có 2a và 1b, b[1:3] cũng có 2a và 1b -> có 1 cách để sắp xếp a thành b[L:R]
    nhưng do 1 string trong permutation của a chỉ được đếm 1 lần
    do đó mỗi khi match được 1 substring trên b thì thêm hash của nó vào trong set
    khi hash của subtr ko có trong set thì mới đếm lên 1
    */
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
