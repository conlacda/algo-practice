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
    vector<bool> frequence;
    bool is_null = true;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        vector<bool> fre(41, 0);
        for (int i=1;i<41;i++) {
            fre[i] = a.frequence[i] || b.frequence[i];
        }
        return Node {
            fre,
            false
        };
    }
    static Node v(int k) {
        vector<bool> frequence(41, false);
        frequence[k] = true;
        return Node{frequence, false};
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
        int x;
        cin >> x;
        a[i] = Node::v(x);
    }
    SegmentTree<Node> seg;
    seg.build(a);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            // query
            auto node = seg.query(--u, --v);
            int cnt = 0;
            for (int i=1;i<41;i++) {
                cnt += node.frequence[i];
            }
            cout << cnt << '\n';
        } else {
            // update
            seg.set_val(--u, Node::v(v));
        }
    }
    
    show_exec_time();
}
/*
Do tại đây giới hạn 1 số chỉ là 1->40 nên có thể dùng mảng tại mỗi node
Việc cập nhật 1 node sẽ kéo theo cập nhật logN*40.
Nếu ko có giới hạn 40 thì việc cập nhật 1 node sẽ tốn logN*k trong đó k là 
khoảng giá trị của 1 node. Khi đó có thể nghĩ tới việc sử dụng compress.
Nhưng về cơ bản nó sẽ quy về 10^5*logN. Do 1 mảng có 10^5 phần tử nên
compress vẫn còn lớn.

Idea: Mo's algorithm với update??
Bài này giống bài distinct query. Nhưng do có thao tác update nên
template của Mo's hiện tại không chạy được
*/