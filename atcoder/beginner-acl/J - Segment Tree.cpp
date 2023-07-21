// https://atcoder.jp/contests/practice2/tasks/practice2_j
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
// const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Node {
    int index = -1;
    int val = 0;
    friend Node operator+(Node a, Node b) {
        if (a.val > b.val) return a;
        return b;
    }
    static Node v(int k) {
        return Node{-1, k};
    }
    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};
template<typename Node>
class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(vector<Node> v){
        build(v);
    }
    void build(vector<Node> v) {
        n = 1;
        while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<(int) v.size();i++) {
            this->set_val(i, v[i]);
        }
    }
    void set_val(int i, Node x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }
    Node query(int l, int r){
        r++;
        Node left = Node(), right = Node();
        l += n - 1; r += n - 1;
        while (l < r) {
            if ((l & 1) == 0) left = left + dat[l];
            if ((r & 1) == 0) right = dat[r - 1] + right;
            l = l / 2; r = (r - 1) / 2;
        }
        return left + right;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<Node> a(n);
    for (int i=0;i<n;i++) {
        int e; cin >> e;
        a[i] = Node::v(e);
    }
    SegmentTree<Node> seg;
    seg.build(a);
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        x--;
        if (t == 1) seg.set_val(x, Node::v(y));
        else if (t == 2) cout << seg.query(x, y-1).val << "\n";
        else {
            int l = x, r = n-1;
            while (r!=l){
                int m = (l+r)/2;
                if (seg.query(l, m).val >= y) r = m;
                else l = m+1;
            }
            if (seg.query(r,r).val >= y) cout << r+1 << '\n';
            else cout << n+1<<'\n';
        }
    }
    show_exec_time();
}