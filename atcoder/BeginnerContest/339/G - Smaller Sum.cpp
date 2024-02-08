// https://atcoder.jp/contests/abc339/tasks/abc339_g
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

// temporary version
struct Node {
    int val = 0;
    bool is_null = true;
    friend Node operator+(Node& a, Node& b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
          return Node {
            a.val + b.val,
            false
        };
    }
    static Node v(int _val) {
        return Node {
            _val,
            false
        };
    }
    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

struct PersistentSegTree {
    int actual_sz, n;
    vector<Node> nodes; // lưu trữ toàn bộ node
    vector<int> root; // root[ith] => root node id tại version ith => node[root[ith]] = root node of version ith
    vector<pair<int,int>> children;
    PersistentSegTree() {}
    void build(vector<Node> a) {
        // giống segment tree bt
        actual_sz = (int) a.size();
        n = (int) pow(2, ceil(log2(actual_sz)));
        nodes.resize(2 * n - 1);
        for (int i=0;i<(int) a.size();i++) nodes[n + i - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) nodes[i] = nodes[i * 2 + 1] + nodes[i * 2 + 2];
        // gán root, child
        root.push_back(0); // root[version 0] = 0;
        children.resize(2 * n -1, {-1, -1});
        for (int i=n-2;i>=0;i--) children[i] = {i*2+1, i*2+2};
    }
    void set(int index, Node val) {
        int last_ver = (int) root.size() - 1;
        int lvroot = root[last_ver];
        // tạo ra 1 segment tree mới
        Node newroot = Node();
        int newrootId = nodes.size();
        nodes.push_back(newroot);
        root.push_back(newrootId);
        std::function<void(int, int, int)> cal = [&](int newrootId, int l, int r) {
            if (l == r) {
                nodes[newrootId] = val;
                return;
            }
            int mid = (l + r) /2;
            // tạo ra node child mới
            Node child = Node();
            int childId = nodes.size();
            nodes.push_back(child);
            children.resize(nodes.size()); // xem performance ở đây có ổn ko khi reallocate + reassign
            if (l <= index && index <= mid) {
                // go left, keep right
                // liên kết node hiện tại với node mới
                children[newrootId] = {childId, children[lvroot].second};
                // di chuyển node root cũ đi xuống
                lvroot = children[lvroot].first;
                // recursive cho child mới
                cal(childId, l, mid);
            } else {
                // go right, keep left
                children[newrootId] = {children[lvroot].first, childId};
                lvroot = children[lvroot].second;
                cal(childId, mid + 1, r);
            }
            nodes[newrootId] = nodes[children[newrootId].first] + nodes[children[newrootId].second];
        };
        cal(newrootId, 0, n-1);
    }
    Node query(int l, int r, int version) {
        int rootId = root[version];
        Node ans = Node();
        std::function<void(int, int, int)> cal = [&](int nodeid, int _l, int _r) {
            if (_l > r || _r < l) return;
            if (l <= _l && _r <= r) {
                ans = ans + nodes[nodeid];
                return;
            }
            int mid = (_l + _r) / 2;
            // [_l..mid] + [mid+1.._r]
            cal(children[nodeid].first, _l, mid); cal(children[nodeid].second, mid + 1, _r);
        };
        cal(rootId, 0, n-1);
        return ans;
    }
    // not specify a version, the version will be implied as the latest version
    Node query(int l, int r) { return query(l, r, (int) root.size() -1); }
    vector<Node> original(int version) {
        vector<Node> ans;
        for (int i=0;i<actual_sz;i++) ans.push_back(query(i, i, version));
        return ans;
    }
};
/*
PersistentSegTree seg;
seg.build(vector<Node> a);
seg.set(index, Node::v(new_val));
node = seg.query(l, r, version_ith);
node = seg.query(l, r); // query on the latest version
*/

struct X {
    int index, val;
    friend bool operator<(X a, X b) {
        return a.val < b.val;
    }
    friend std::ostream& operator<<(std::ostream& os, const X s) { return os << destructure(s);}
};  

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<X> a(n);
    vector<int> _a(n);
    for (int i=0;i<n;i++) {
        int x;
        cin >> x;
        a[i] = X{i, x};
        _a[i] = x;
    }
    sort(a.begin(), a.end());
    sort(_a.begin(), _a.end());
    PersistentSegTree seg;
    seg.build(vector<Node>(n, Node::v(0)));
    for (int i=0;i<n;i++) {
        seg.set(a[i].index, Node::v(a[i].val));
    }
    /*
    đưa từng số vào trong segment tree
    Với số x thì xem phiên bản nào mà số bắt đầu vượt quá x
    query trên phiên bản đó là xong
    */
    int q;
    cin >> q;
    int prev = 0;
    dbg(a);
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        l ^= prev;
        r ^= prev;
        x ^= prev;
        l--; r--;
        dbg(l, r, x);
        // Tìm số lớn hơn x bắt đầu -> upper bound
        int version = std::upper_bound(_a.begin(), _a.end(), x) - _a.begin();
        auto node = seg.query(l, r, version);
        prev = node.val;
        cout << node.val << '\n';
    }
    show_exec_time();
}
/*
Sử dụng persistent segement tree
Sắp xếp lại toàn bộ mảng a.
Với mỗi số nằm trong mảng a đẩy vào pseg tree 1 lần
Với 1 query x thì ta tìm tới phiên bản có toàn bộ số đều <= x
Ta có mảng a được sắp xếp nên việc tìm tới upper_bound index cũng chính là phiên bản cần tìm tới
query(l, r) tại phiên bản đó là được.
*/
