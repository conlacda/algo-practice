// https://atcoder.jp/contests/abc369/tasks/abc369_g
#include<bits/stdc++.h>

const int mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

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

template<typename Node, typename Lznode>
struct LazySegtree {
  private:
    int N, size, log;
    vector<Node> data;
    vector<Lznode> lz;

    void update(int k) { data[k] = Node::merge(data[2 * k], data[2 * k + 1]); }
    void all_apply(int k, Lznode lzn) {
        lzn.applyTo(data[k]); // template is a bit weird.
        if (k < size) lz[k] = Lznode::composition(lz[k], lzn);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = Lznode{.is_null = true};
    }
  public:
    LazySegtree() {}
    LazySegtree(std::vector<Node>& v) {build(v);}
    void build(const std::vector<Node>& v) {
        this->N = (int) v.size();
        log = 0; while ((1U << log) < (unsigned int)(N)) log++; 
        size = 1 << log;
        data.resize(2 * size, Node{.is_null = true});
        lz.resize(size, Lznode{.is_null = true});
        for (int i = 0; i < N; i++) data[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, Node x) {
        assert(0 <= p && p < N);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        data[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    template<class... P> void set(int index, P... params) { set(index, Node{params...});}

    Node query(int l, int r) {
        r++;
        assert(0 <= l && l <= r && r <= N);
        if (l == r) return Node{.is_null = true};

        l += size; r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        Node sml = Node{.is_null = true}, smr = Node{.is_null = true};
        while (l < r) {
            if (l & 1) sml = Node::merge(sml, data[l++]);
            if (r & 1) smr = Node::merge(data[--r], smr);
            l >>= 1; r >>= 1;
        }

        return Node::merge(sml, smr);
    }

    Node query_all() { return data[1]; }

    void update(int l, int r, Lznode lznode) {
        r++; assert(0 <= l && l <= r && r <= N);
        if (l == r) return;
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, lznode);
            if (r & 1) all_apply(--r, lznode);
            l >>= 1; r >>= 1;
        }
        l = l2; r = r2;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    template<class... P> void update(int l, int r, P... params) { update(l, r, Lznode{params...});}

    vector<int> original() {
        vector<int> res;
        for (int i=0;i<N;i++) {
            res.push_back(query(i, i).val);
        }
        return res;
    }
};

struct Node {
    int val = 0;// ***
    int id;
    int size = 1; // để mặc định là 1. Sử dụng trong hàm apply
    bool is_null = false;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    friend Node operator+(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        if (l.val > r.val) {
            return Node {
                l.val,
                l.id,
                l.size + r.size
            };
        }
        return Node {
            r.val,
            r.id,
            l.size + r.size, // size
        };
    }
    static Node merge(Node l, Node r) { return l + r; }
    Node operator!() { return *this; }
};

struct Lznode {
    int val = 0; // Node x; assert(x.apply(LzNode()) == x)// ***
    bool is_null = false;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return {
            first.val + second.val,// ***
        };
    }
    // Apply cho 1 range
    // ex: fX = aX+b. fx1 = ax1+b, fx2 = ax2+b => X = x1+x2 có fX = aX + b*size(X)
    void applyTo(Node& node) {
        if (this->is_null) return;
        node.val = node.val + this->val;// ***
    }
};

vector<int> parent_on_tree(vector<vector<int>>& tree, int root = 0) {
    vector<int> parent((int) tree.size(), 0);
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: tree[u]) {
            if (v == p) continue;
            parent[v] = u;
            dfs(v, u);
        }
    };
    dfs(root, root);
    return parent;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    map<pair<int,int>, int> edges;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[{min(u, v), max(u, v)}] = w;
    }
    // tính độ dài của đường đi
    vector<int> dist(n, 0);
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            if (v == p)
                continue;
            dist[v] = dist[u] + edges[{min(u, v), max(u, v)}];
            dfs(v, u);
        }
    };
    dfs(0, 0);
    int leaves_cnt = 0;
    std::function<void(int, int)> cntLeaves = [&](int u, int p) {
        if (u != 0 && (int) adj[u].size() == 1) leaves_cnt++;
        for (auto v: adj[u]) {
            if (v == p)
                continue;
            cntLeaves(v, u);
        } 
    };
    cntLeaves(0, 0);
    /*
    Với mỗi điểm cập nhật thì mk sẽ update subtree
    Cập nhật subtree thì sẽ lấy first, second ra để cập nhật
    update toàn bộ range đó giảm đi k??
    query max cho nó??

    dựng 1 euler tour trên cây này.
    Fill giá trị dist vào trong euler tour
    Chọn 1 node mà chưa pick và đi ngược lên lấy path
    Với path đó thì đi ngược xuống rồi update subtree dùng lazysegment tree + query max cho toàn bộ tree
    */
    makeEulerTour(adj);
    // Dùng lazy segment tree với eulertour
    // thao tác: query max, update cộng
    vector<Node> a(2*n);
    for (int i=0;i<n;i++) {
        a[first[i]] = Node{dist[i], i};
        a[second[i]] = Node{dist[i], i};
    }
    LazySegtree<Node, Lznode> seg;
    seg.build(a);
    map<int, bool> pass;
    pass[0] = true;
    int ans = 0;
    vector<int> parent = parent_on_tree(adj);
    for (int i=0;i<leaves_cnt;i++) {
        auto node = seg.query_all();
        ans += node.val * 2;
        cout << ans << '\n';
        int id = node.id;
        dbg(node.id, node.val);
        dbg(seg.original());
        vector<int> trace;
        while (!pass[id]) {
            trace.push_back(id);
            pass[id] = true;
            id = parent[id];
        }
        reverse(trace.begin(), trace.end());
        // truy ngược lên phần node bên trên
        // rồi update query
        for (auto v: trace) {
            auto p = parent[v];
            int edge = edges[{min(v, p), max(v, p)}];
            seg.update(first[v], second[v], Lznode{-edge});
        }
    }
    // từ đoạn này trở đi thì các node lá đã đi xong
    // kết quả không thay đổi khi chọn thêm bất cứ 1 node nào
    for (int i=leaves_cnt;i<n;i++) {
        cout << ans << '\n';
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Việc chọn node ở đây chỉ là chọn lá, không chọn node khác lá.
Vì khi chọn node lá thì phải đi qua mọi node khác -> đường đi dài nhất
Nếu chọn 1 node A với 1 -> A -> B thì chọn B sẽ luôn tối ưu hơn -> B là lá
Khi chọn 1 node lá thì sẽ đi ngược lại rồi cập nhật giá trị độ dài cho các 
subtree của từng node đó (cập nhật lại khoảng cách cho các lá)

Bài này ý tưởng đơn giản nhưng code thì lằng nhằng:
Chọn từng node lá với khoảng cách còn lại xa nhất
Để chọn được thì phải dùng segment tree max + eulertour
sau khi chọn được 1 node thì sẽ chạy ngược lên những node đi trong lần này
cập nhật lại giá trị cho toàn bộ subtree của node đó (trừ đi độ dài cạnh vừa đi) từ trên xuống (đoạn trace)
sau khi cập nhật thì lại tìm node tiếp theo tương tự

Sau khi xong đoạn chọn lá thì kết quả sau đó dù chọn thêm node nào 
thì giá trị đường đi ko thay đổi
*/
