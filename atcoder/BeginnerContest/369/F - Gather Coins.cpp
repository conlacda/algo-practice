// https://atcoder.jp/contests/abc369/tasks/abc369_f
// [Atcoder|Codeforces].abcxxx.F
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

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
    SegmentTree(vector<Node>& v){ build(v);}
    void build(vector<Node>& v) {
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
        for (int i=0;i<n;i++){
            res.push_back(query(i, i));
        }
        return res;
    }
};

struct MaxNode {
    int val = 0; // giá trị mặc định nên để là 0// ***
    int row = 0;
    int col = 0;
    bool is_null = false;
    friend MaxNode operator+(MaxNode a, MaxNode b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        if (a.val >= b.val) {
            return MaxNode(a.val, a.row, a.col);
        }
        return MaxNode(b.val, b.row, b.col);
    }
    MaxNode operator!() { return *this; }
};
using Node = MaxNode;

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    Dùng segment tree.
    Với từng dòng ta có 1 segment tree rồi duyệt từ trái qua phải.
    Để trace back thì có thể đơn giữ lấy cái column là được
    với 1 danh sách column có thể in ra được đường đi
    */
    int h, w, n;
    cin >> h >> w >> n;
    vector<set<int>> coins(h);
    for (int i=0;i<n;i++) {
        int u, v;
        cin >> u >> v;
        coins[--u].insert(--v);
    }
    vector<Node> a(w);
    for (int i=0;i<w;i++) {
        a[i] = Node{0, 0, i};
    }
    SegmentTree<Node> seg; seg.build(a);
    map<pair<int,int>, pair<int,int>> parent;
    for (int i=0;i<h;i++) {
        for (auto&v: coins[i]) {
            auto node = seg.query(0, v);
            seg.set(v, Node{node.val + 1, i, v});
            parent[{i, v}] = {node.row, node.col};
        }
    }
    dbg(parent);
    dbg(seg.original());
    auto node = seg.query(0, w-1);
    cout << node.val << '\n';
    dbg(node);
    string ans = "";
    int cur_row = h-1;
    int cur_col = w-1;
    // Di chuyển từ điểm cuối về node
    while (cur_col > node.col) {
        ans += 'R';
        cur_col--;
    }
    while (cur_row > node.row) {
        ans += 'D';
        cur_row--;
    }
    while (cur_col != 0 || cur_row != 0) {
        auto [row, col] = parent[{cur_row, cur_col}];
        while (cur_col > col) {
            ans += 'R';
            cur_col--;
        }
        while (cur_row > row) {
            ans += 'D';
            cur_row--;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này bản chất là duyệt từng dòng một.
Dòng sau sẽ được tính bằng dòng trước, và duyệt từng index trái qua phải.

ooox
xoxo
ooxo
Với sample 1 ta khởi tạo 1 segment tree size 4 với toàn bộ giá trị 0
Để lưu trữ được đường đi thì cần thêm hàng và cột cho từng node
-> Node = {val, row, col}
Duyệt từng hàng 1 và từ trái qua phải
hàng 1: Node{0, 0, 0}, {0, 0, 1}, {0, 0, 2}, {1, 0, 3}
hàng 2: index 0 có x -> set node index 0 = Node{prev_val + 1, row = 1, col = 0} và
đồng thời là parent để trace back parent[{row = 1, col = 0}] = {0, 0}
do bảng này 10^5*10^5 nên từng hàng chỉ duyệt những ô có x, bỏ qua o
index = 2 -> lấy ra điểm có val lớn nhất từ 0->2 chính là node tại index 0
hàng 3: node tại index 2 lấy ra node có val lớn nhất từ 0->2 chính là Node{2, 1, 2}
giá trị mới là Node{2+1, 2, 2} và parent[{2, 2}] = {1, 2}

In ra giá trị:
* Đơn giản là query từ index 0->w-1 là lấy ra được val
* Lấy ra đường đi
    * tại node có val lớn nhất kia ta đi từ (h-1, w-1) tới {node.row, node.col} (đi bằng 2 đoạn thẳng, dịch col trước rồi dịch row sau or dịch row->col)
    * dùng parent để lấy ra điểm trước đó rồi lại đi từ điểm hiện tại tới trước đó (dịch col -> dịch row)
    * cho tới khi chạm điểm {0, 0}
    * reverse đường đi là ra
*/
