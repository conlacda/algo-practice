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

struct Node {
    int val;
    vector<int> fre;
    bool is_null = true;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        vector<int> merged_fre(41, 0);
        for (int i=1;i<=40;i++) {
            merged_fre[i] = a.fre[i] + b.fre[i];
        }
        int newval = a.val + b.val;
        for (int i=2;i<=40;i++) {
            for (int j=1;j<i;j++) {
                newval += a.fre[i] * b.fre[j];
            }
        }
        return Node {
            newval,
            merged_fre,
            false
        };
    }
    static Node v(int k) {
        vector<int> fre(41, 0);
        fre[k]++;
        return Node {
            0,
            fre,
            false
        };
    }
    Node operator!() {
        return *this;
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
    SegmentTree(vector<Node> v){ build(v);}
    void build(vector<Node> v) {
        n = 1;
        while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
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
    int n, q;
    cin >> n >> q;
    vector<Node> a(n);
    for (int i=0;i<n;i++) {
        int x; cin >> x;
        a[i] = Node::v(x);
    }
    SegmentTree<Node> seg;
    seg.build(a);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            auto node = seg.query(--u, --v);
            cout << node.val << '\n';
            // query inversion
        } else {
            // update giá trị - set
            seg.set_val(--u, Node::v(v));
        }
    }
    
    show_exec_time();
}
/*
ai < 40
1 node sẽ bao gồm tần số của 40 giá trị
left + right -> tổng left + tổng right + số cặp bên left > bên right
https://stackoverflow.com/questions/64279124/counting-inversions-in-a-segment-with-updates

1 node bao gồm tần số các số từ 1->41.
merge 2 node thì sẽ có tần số mới cộng vào như thường 1 với 1, 2 với 2,..
val = left + right + số phần tử trái > phải

tại đây đoạn cấp phát vector hơi thô bỉ nên chạy mất 2s.
Ko sao nó vẫn pass và ko có ý định tối ưu nó hơn.
*/