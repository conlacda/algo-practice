// https://codeforces.com/problemset/problem/1843/F2
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
    int max_mid = 0;
    int min_mid = 0;
    int max_pref = 0;
    int min_pref = 0;
    int max_suf = 0;
    int min_suf = 0;
    int whole = 0;
    bool is_null = true;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return Node {
            max({a.max_mid, b.max_mid, a.max_suf + b.max_pref}),
            min({a.min_mid, b.min_mid, a.min_suf + b.min_pref}),
            max(a.max_pref, b.max_pref + a.whole),
            min(a.min_pref, b.min_pref + a.whole),
            max(b.max_suf, a.max_suf + b.whole),
            min(b.min_suf, a.min_suf + b.whole),
            a.whole + b.whole,
            false
        };
    }
    static Node v(int k) {
        return Node{k, k, k, k, k, k, k, false};
    }
    Node operator!() {
        Node ans;
        ans.max_mid = max_mid;
        ans.min_mid = min_mid;
        ans.max_pref = max_suf;
        ans.min_pref = min_suf;
        ans.max_suf = max_pref;
        ans.min_suf = min_pref;
        ans.whole = whole;
        ans.is_null = is_null;
        return ans;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

class LCA{
    struct Euler{
        int vertex = INF, height = INF, index = INF;
        friend Euler operator+(Euler a, Euler b) {
            return (a.height < b.height) ? a: b;
        }
    };
    class LCASegmentTree {
    private:
        int n;
        vector<Euler>dat;
    public:
        LCASegmentTree() {}
        void build(vector<Euler> v) {
            n = 1; while (n < (int) v.size()) n *= 2;
            dat.resize(2 * n - 1);
            for (int i=0;i<(int) v.size();i++) this->set_val(i, v[i]);
        }
        void set_val(int i,Euler x){
            i+=n-1; dat[i]=x;
            while(i > 0) {
                i = (i-1)/2;
                dat[i] = dat[i*2+1] + dat[i*2+2];
            }
        }
        Euler query(int l,int r){
            Euler left= Euler(), right = Euler();
            l+=n-1; r+=n;
            while(l<r){ 
                if((l&1)==0) left = left + dat[l];
                if((r&1)==0) right = dat[r-1] + right;
                l=l/2;r=(r-1)/2;
            }
            return left + right;
        }
    };
    vector<int> heightOfTree() {
        vector<int> h(this->n, 0);
        for (auto e: eulertour) h[e.vertex] = e.height; // height[root] = 1
        return h;
    }
public:
    int n;
    vector<Euler> eulertour;
    vector<int> first, height;
    LCASegmentTree seg;
    LCA() {}
    LCA(vector<vector<int>> graph, int root = 0){
        build(graph, root);
    }
    void build(vector<vector<int>> graph, int root = 0) {
        this->n = graph.size();
        this->makeEuler(graph, root);
        seg.build(eulertour);
        height = heightOfTree();
    }
    // Euler tour of tree
    void makeEuler(vector<vector<int>> graph, int root){
        // Euler tour tạo ra verticies, heights, index
        vector<bool> vis(n, false);
        int depth = 0;
        std::function<void(int)> explore = [&](int u){
            vis[u] = true; depth++;
            Euler node = Euler{u, depth, (int) eulertour.size()};
            eulertour.push_back(node);
            for (auto v: graph[u]){
                if (!vis[v]) {
                    explore(v);
                    depth--;
                    eulertour.push_back(node);
                }
            }
        };
        explore(root);
        // Tạo ra mảng first
        first.resize(n, -1);
        for (auto e: eulertour){
            if (first[e.vertex] == -1) {
                first[e.vertex] = e.index;
            }
        }
        
    }
    int lca(int u, int v){
        return seg.query(min(first[u], first[v]), max(first[u], first[v])).vertex;
    }
    int distance(int u, int v) {
        return height[u] + height[v] - 2 * height[lca(u, v)];
    }
    int lca(int r, int u, int v){ // ar = abtrary root - LCA của u,v với r bất kỳ là root
        int ru = lca(r, u);
        int rv = lca(r, v);
        int uv = lca(u, v);
        if (ru == rv) return uv;
        if (ru == uv) return rv;
        return ru;
    }
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
};

class HeavyLightDecomposition{
public:
    int n;
    vector<int> parent, depth, heavy, head, pos;
    LCA lca;
    vector<int> pos2vertex; // với đỉnh u -> pos[u] + 1 là đỉnh tiếp theo được duyệt. -> pos2vertex[pos[u]+1] ra id của đỉnh kế tiếp u // dựa vào đó sẽ lấy được vị trí phía dưới trong chain (subtree) - tạm hiểu là child
 
    HeavyLightDecomposition(vector<vector<int>> adj) {
        this->n = adj.size();
        heavy = vector<int>(n, -1);
        parent = depth = head = pos = pos2vertex = vector<int>(n, 0);
        lca.build(adj);
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
        if (u != p) {
            path.push_back({u, pos2vertex[pos[p] + 1]});
        }
        return path;
    }
  
    SegmentTree<Node> seg;
    void buildSegTree(vector<int> weight){ // w này nằm trên đỉnh. nếu nằm trên cạnh thì chuyển qua đỉnh phía dưới edge(u,v) chọn u với u là con v
        // pos[] lưu vị trí của các node theo thứ tự duyệt. Duyệt trong 1 khối (subtree, chain) -> duyệt từ khối này nối sang khối khác
        vector<Node> wvt(n); // weight of verticies - làm phẳng tree ra dạng [[chain1][chain2][...]...]
        // khi này muốn query(u, v) thì sẽ chia ra [u..->tailu][...][headv..->v] rồi query từng khúc 1
        for (int i=0;i<n;i++) wvt[pos[i]] = Node::v(weight[i]); // làm phẳng cây ra thành 1 mảng với các đoạn segment nối tiếp nhau 
        // i là vertex, pos[i] tương ứng là index trên euler tour
        seg.build(wvt);
    }
 
    Node query(int u, int v) {
        int p = lca.lca(u, v);
        Node left;
        auto u2p = path_exclude_root(u, p);
        vector<pair<int,int>> p2u(u2p.rbegin(), u2p.rend());
        for (auto chain: p2u) {
            left = left + seg.query(pos[chain.second], pos[chain.first]);
        }
        Node root = seg.query(pos[p], pos[p]);
        Node right;
        auto v2p = path_exclude_root(v, p);
        vector<pair<int,int>> p2v(v2p.rbegin(), v2p.rend());
        for (auto chain: p2v) {
            right = right + seg.query(pos[chain.second], pos[chain.first]);
        }
        return (!left) + root + right;
    }

    void set_val(int u, Node node){
        seg.set_val(pos[u], node);
    }
 
    void set_val_for_edge(int u, int v, Node val) {
        int deeper = (depth[u] > depth[v]) ? u : v; // trọng số đẩy xuống dưới
        set_val(deeper, val);
    }
};

void solve() {
    int q;
    cin >> q;
    vector<pair<int,int>> add;
    vector<array<int, 3>> queries;
    dbg(q);
    for (int i=0;i<q;i++) {
        char c; cin >> c;
        if (c == '+') {
            int node, val;
            cin >> node >> val;
            node--;
            add.push_back({node, val});
        } else if (c == '?') {
            int u, v, val;
            cin >> u >> v >> val;
            u--; v--;
            queries.push_back({u, v, val});
        }
    }
    vector<vector<int>> g((int) add.size() + 1);
    vector<int> weight((int) add.size() + 1); weight[0] = 1;
    int latestNode = 1;
    for (auto vw: add) {
        g[latestNode].push_back(vw.first);
        g[vw.first].push_back(latestNode);
        weight[latestNode] = vw.second;
        latestNode++;
    }
    HeavyLightDecomposition hld(g);
    hld.buildSegTree(weight);
    dbg(queries);
    for (auto query: queries) {
        if (query[2] == 0) {
            cout << "YES\n";
            continue;
        }
        Node mx = hld.query(query[0], query[1]);
        dbg(mx);
        if (query[2] <= mx.max_mid && query[2] >= mx.min_mid) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    for (int i=0;i<n;i++) {
        solve();
    }
    show_exec_time();
}
/*
Thứ tự query của segment tree là như thế nào??
node bên dưới thì sẽ có pos lớn hơn.
query từ 1 nhánh thì sẽ lấy pos nhỏ -> pos lớn -> đỉnh trên xuống đỉnh dưới
  2 
1   3

coi nốt 2 là 1 điểm, ko quan tâm chiều
-> 1,3 đều có chiều đi xuống 
xoay chiều 1-> r(1) + 2 + 3
xoay chiều 3-> r(3) + 2 + 1.
1 + 2 + r(3) ra kết quả khác. Node a + Node b != Node b + Node a
Có 2 cách để reverse
* Reverse node đó -> dùng 1 hàm reverse để làm
* Reverse tại segment tree -> dùng 2 segment tree để build. Với query(l, r) thì tại khi lật ngược arr để build thì r < l.
1
7
+ 1 1
+ 1 -1
+ 3 -1
+ 1 -1
+ 1 1
+ 5 -1
? 5 2 2
*/