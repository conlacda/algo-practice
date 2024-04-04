// https://www.spoj.com/problems/QTREE/
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

struct Node {
    int val = 0;// ***
    int size = 1; // để mặc định là 1. Sử dụng trong hàm apply
    bool is_null = false;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    friend Node operator+(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node {
            max(l.val, r.val), // bài không yêu cầu range query thì để là 0// ***
            l.size + r.size, // size
        };
    }
    static Node merge(Node l, Node r) { return l + r; }
    Node operator!() { return *this; } // dùng cho thao tác query có xét chiều. Node a + Node b = !(Node b + Node a)// ***
};

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
using SegTree = SegmentTree<Node>;

struct HLD {
    int n;
    vector<int> parent, depth, heavy, head, pos;
    vector<int> pos2vertex; // với đỉnh u -> pos[u] + 1 là đỉnh tiếp theo được duyệt. -> pos2vertex[pos[u]+1] ra id của đỉnh kế tiếp u // dựa vào đó sẽ lấy được vị trí phía dưới trong chain (subtree) - tạm hiểu là child
 
    HLD(vector<vector<int>> adj) {
        this->n = adj.size();
        heavy = vector<int>(n, -1);
        parent = depth = head = pos = pos2vertex = vector<int>(n, 0);
        std::function<int(int)> dfs = [&](int v){
            int size = 1;
            int max_c_size = 0;
            for (auto c : adj[v]) {
                if (c != parent[v]) {
                    parent[c] = v, depth[c] = depth[v] + 1;
                    int c_size = dfs(c);
                    size += c_size;
                    if (c_size > max_c_size) max_c_size = c_size, heavy[v] = c;
                }
            }
            return size;
        };
        int cur_pos = 0;
        std::function<void(int, int)> decompose = [&](int v, int h){
            head[v] = h, pos[v] = cur_pos++;
            if (heavy[v] != -1) decompose(heavy[v], h);
            for (auto c : adj[v]) {
                if (c != parent[v] && c != heavy[v]) decompose(c, c);
            }
        };
        dfs(0); decompose(0, 0); // calculate parent, depth, heavy, head, pos
        for (int v=0;v<(int)pos.size();v++) pos2vertex[pos[v]] = v;
    }
 
    vector<pair<int,int>> path_inclusive(int u, int p) {
        vector<pair<int,int>> path;
        while (head[p] != head[u]) {
            path.push_back({u, head[u]});
            u = parent[head[u]];
        }
        path.push_back({u, p});
        return path;
    }
    vector<pair<int,int>> path_exclude_root(int u, int p) {
        vector<pair<int,int>> path;
        while (head[p] != head[u]) {
            path.push_back({u, head[u]});
            u = parent[head[u]];
        }
        if (u != p)
            path.push_back({u, pos2vertex[pos[p] + 1]});
        return path;
    }
  
    SegTree seg;
    void buildSegTree(vector<int> weight){ // w này nằm trên đỉnh. nếu nằm trên cạnh thì chuyển qua đỉnh phía dưới edge(u,v) chọn u với u là con v
        // pos[] lưu vị trí của các node theo thứ tự duyệt. Duyệt trong 1 khối (subtree, chain) -> duyệt từ khối này nối sang khối khác
        vector<Node> wvt(n); // weight of verticies - làm phẳng tree ra dạng [[chain1][chain2][...]...]
        // khi này muốn query(u, v) thì sẽ chia ra [u..->tailu][...][headv..->v] rồi query từng khúc 1
        for (int i=0;i<n;i++) wvt[pos[i]] = Node{weight[i]}; // làm phẳng cây ra thành 1 mảng với các đoạn segment nối tiếp nhau 
        // i là vertex, pos[i] tương ứng là index trên euler tour
        seg.build(wvt);
    }
 
    Node query(int u, int v) {
        int p = lca(u, v);
        Node left;
        auto u2p = path_exclude_root(u, p);
        vector<pair<int,int>> p2u(u2p.rbegin(), u2p.rend());
        for (auto chain: p2u)
            left = left + seg.query(pos[chain.second], pos[chain.first]);

        Node root = seg.query(pos[p], pos[p]);
        
        Node right;
        auto v2p = path_exclude_root(v, p);
        vector<pair<int,int>> p2v(v2p.rbegin(), v2p.rend());
        for (auto chain: p2v)
            right = right + seg.query(pos[chain.second], pos[chain.first]);

        // bỏ root nếu trọng số nằm trên cạnh // ***
        return (!left) + right; // ***
    }

    void set_node(int u, Node node) {
        seg.set(pos[u], node);
    }
 
    void set_edge(int u, int v, Node val) {
        int deeper = (depth[u] > depth[v]) ? u : v; // trọng số đẩy xuống dưới
        set_node(deeper, val);
    }

    int kth_ancestor(int u, int k) { // kth_ancestor(u, 0) = u;
        assert(depth[0] + k <= depth[u]);
        int step = 0;
        for (auto uv: path_inclusive(u, 0)) { // u to root
            step += pos[uv.first] - pos[uv.second]; // nhảy cuối lên đầu chain
            if (step >= k) {
                int p = pos[uv.second] + step -k; // lấy điểm đầu chạy (step-k) bước là ra pos điểm cần tìm
                return pos2vertex[p];
            }
            step++; // nhảy từ chain này sang chain khác
        }
        return 0;
    }

    // Slower than isolated LCA 3 times. if TLE, use LCA instead
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = kth_ancestor(u, depth[u] - depth[v]); // làm cho u, v có cùng độ cao
        auto ur = path_inclusive(u, 0);
        auto vr = path_inclusive(v, 0);
        std::function<int(int, int, vector<pair<int,int>>*)> kth_ancestor = [&](int u, int k, vector<pair<int,int>> *computed_path) {
            int step = 0;
            for (auto chain: *computed_path) {
                step += pos[chain.first] - pos[chain.second];
                if (step >= k) return pos2vertex[pos[chain.second] + step - k];
                step++;
            }
            return (int) 0; // root
        };
        int left = 0, right = depth[u] - depth[0];
        while (left < right) {
            int k = (left + right) / 2;
            if (kth_ancestor(u, k, &ur) == kth_ancestor(v, k, &vr))
                right = k; 
            else
                left = k + 1;
        }
        return kth_ancestor(u, left, &ur);
    }

    int distance(int u, int v) {
        int p = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[p];
    }
};

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<tuple<int, int,int>> edges;
    for (int i=0;i<n-1;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({min(u, v), max(u, v), w});
    }
    HLD hld(adj);
    vector<int> weight(n, 0);
    for (auto&[u, v, w]: edges) {
        int deeper = (hld.depth[u] > hld.depth[v]) ? u : v;
        weight[deeper] = w;
    }
    hld.buildSegTree(weight);
    while (true) {
        string t;
        cin >> t;
        if (t == "DONE") break;
        if (t == "QUERY") {
            int u, v;
            cin >> u >> v;
            u--; v--;
            cout << hld.query(u, v).val << '\n';
        } else {
            // change
            int index, w;
            cin >> index >> w;
            index--;
            auto [u, v, _] = edges[index];
            hld.set_edge(u, v, Node{w});
        }
    }
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int test_num;
    cin >> test_num;
    while (test_num--) solve();

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
*/
