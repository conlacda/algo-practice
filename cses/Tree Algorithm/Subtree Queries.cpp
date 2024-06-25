// https://cses.fi/problemset/task/1137/
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
};

struct SumNode {
    int val = 0; // giá trị mặc định nên để là 0// ***
    bool is_null = false;
    friend SumNode operator+(SumNode a, SumNode b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return SumNode{a.val + b.val};// ***
    }
    SumNode operator!() { return *this; }
};
using Node = SumNode;

// euler_tour_on_tree
vector<int> first, second, eulertour;
void makeEulerTour(vector<vector<int>>& adj) {
    int n = adj.size();
    eulertour.clear(); first.resize(n); second.resize(n); // first[v] - thời điểm duyệt v, second[v] - thời điểm ra khỏi v
    int clock = 0;
    std::function<void(int, int)> dfs = [&](int u, int p){
        eulertour.push_back(u);
        first[u] = clock++;
        for (auto v: adj[u]) {
            if (v != p) dfs(v, u);
        }
        second[u] = clock++;
        eulertour.push_back(u);
    };
    dfs(0, 0);
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> w(n);
    for (auto&v: w) cin >> v;
    vector<vector<int>> g(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    makeEulerTour(g);
    /*
    dựng segment tree trên toàn bộ eulertour
    query điểm u -> first[u] -> second[u] là được
    cập nhật giá trị 1 điểm thì cập nhật vị trí first[u], second[u]
    */
    vector<Node> a(2*n);
    for (int i=0;i<2*n;i++)
        a[i] = Node{w[eulertour[i]]}; // điền trọng số vào các node trên euler tour

    SegmentTree<Node> seg;
    seg.build(a);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            u--;
            seg.set(first[u], Node{v});
            seg.set(second[u], Node{v});
        } else {
            // t == 2
            int u;
            cin >> u;
            u--;
            Node res = seg.query(first[u], second[u]);
            cout << res.val / 2<< '\n';
        }
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này khá đơn giản
Sau khi dựng lên eulertour thì subtree(u) khi này sẽ trở thành 
1 range từ first[u] -> second[u]
Thêm trọng số vào các điểm ở euler tour
Query sum cho nó là range rồi chia đôi (vì mỗi node được tính 2 lần)
Cập nhật thì cập nhật giá trị vào first và second là được
*/
