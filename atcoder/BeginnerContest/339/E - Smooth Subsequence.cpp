// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

struct Node {
    int val = 0; // giá trị mặc định nên để là 0 // ***
    bool is_null = true;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return Node {
            max(a.val, b.val), // ***
            false
        };
    }
    static Node v(int k) { // ***
        return Node{k, false}; // ***
    } // ***
    Node operator!() { return *this; }

    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(vector<Node>& v){ build(v);}
    void build(vector<Node>& v) {
        for (auto &node: v) assert(!node.is_null);
        n = 1;
        while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
    void set_val(int i, Node x) {
        assert(!x.is_null && "dùng Node::v(val) thay vì Node {val}");
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }
    Node query(int l, int r){
        assert(l <= r);
        Node left = Node(), right = Node();
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
        for (int i=0;i<n;i++){
            res.push_back(query(i, i));
        }
        return res;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for (auto&v : a) cin >> v;
    dbg(a);
    /*
    Tới mỗi số ai check xem số có chuỗi lớn nhất đang là bao nhiêu
    [ai-d, ai+d]
    segmenttree max
    */
    vector<Node> seginput((int) 1e6 + 5, Node::v(0));
    SegmentTree seg;
    seg.build(seginput);
    for (auto v: a) {
        int l = max(v - d, (int) 0);
        int r = v + d;
        auto node = seg.query(l, r);
        seg.set_val(v, Node::v(node.val + 1));
    }
    cout << seg.query(0, (int) 1e6 + 4).val;
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
