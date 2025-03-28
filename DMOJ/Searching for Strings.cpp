// https://dmoj.ca/problem/ccc20s3
// Submit via vjudge
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

mt19937 _rand(std::chrono::steady_clock::now().time_since_epoch().count());
map<int, int> randomMap;
void randomMapping() {} // Base case: when there are no more arguments to process
template <typename T, typename... Args>
void randomMapping(T& first, Args&... rest) {
    for (auto&v: first) {
        if (!randomMap.count(v)) {
            auto randomVal = _rand();
            randomMap[v] = randomVal;
            v = randomVal;
        } else {
            v = randomMap[v];
        }
    }

    randomMapping(rest...);
}

vector<int> factor;
const int maxN = 200005;
void precompute() {
    factor.resize(maxN);
    int cur = 1;
    for (int i=0;i<maxN;i++) {
        factor[i] = cur;
        cur = (cur * 263) % mod;
    }
}

template<typename Node>
class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(const vector<Node>& v) { build(v);}
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
    template<class... P> void set(int index, P... params) { set(index, Node{params...});}
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
    // Retrieve current state of vector
    vector<Node> original() {
        vector<Node> res;
        for (int i=0;i<n;i++)
            res.push_back(query(i, i));
        return res;
    }

    Node operator[](int index) {
        assert(0 <= index && index < n && "Out of range");
        return query(index, index);
    }

    // return min index r that seg.query(start, r) satisfies the condition
    // return -1 if not found
    int find_right(int val, int start = 0) {
        int l = start, r = n - 1;
        while (l != r) {
            int mid = (l + r) / 2;
            if (query(start, mid).val >= val) r = mid;
            else l = mid + 1;
        }
        if (query(start, l).val >= val)
            return l;
        return -1;
    }

    // tìm ra index lớn nhất để seg.query(index, end) >= val
    // không tìm thấy sẽ trả về -1
    int find_left(int val, int end = -1) {
        if (end == -1) end = n - 1;
        int l = 0, r = end;
        while (l != r) {
            int mid = (l + r) / 2;
            if (mid * 2 < l + r) mid++;
            if (query(mid, end).val >= val) l = mid;
            else r = mid - 1;
        }
        if (query(l, end).val >= val)
            return l;
        return -1;
    }
};

struct SumXorNode {
    int sum = 0, _xor = 0;
    int size = 1, hash = 0, rhash = 0;
    bool is_null = false;
    friend SumXorNode operator+(SumXorNode a, SumXorNode b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return SumXorNode {
            a.sum + b.sum,
            a._xor ^ b._xor,
            a.size + b.size,
            (a.hash + factor[a.size] * b.hash) % mod,
            (b.rhash + factor[b.size] * a.rhash) % mod
        };
    }
};
using Node = SumXorNode;

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    precompute();
    string s, b;
    cin >> s >> b;
    vector<int> vs(s.begin(), s.end());
    vector<int> vb(b.begin(), b.end());
    randomMapping(vs, vb);
    /*
    Query toàn bộ b để xem hash(start, n) có bằng với hash(s) hay không
    Nếu bằng thì cần lưu lại nó bằng 1 giá trị hash thông thường
    */
    // Tính hash cho small string
    Node small = Node{.is_null = true};
    for (auto&v: vs) {
        small = small + Node{.sum = v, ._xor = v, .hash = v, .rhash = v};
    }
    SegmentTree<Node> seg;
    vector<Node> si;
    for (int i=0;i<(int) vb.size();i++) {
        si.push_back(Node{.sum = vb[i], ._xor = vb[i], .hash = vb[i], .rhash = vb[i]});
    }
    seg.build(si);
    set<pair<int,int>> _set;
    for (int i=0;i<(int) b.size() - (int) s.size() + 1;i++) {
        auto node = seg.query(i, i + (int) s.size() - 1);
        if (node.sum == small.sum and node._xor == small._xor) {
            _set.insert({node.hash, node.rhash});
        }
    }
    cout << _set.size();
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
