#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
// #define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#include "random.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

/*
Lấy ra các cutpoint của đồ thị vô hướng
*/
set<int> findCutPoints(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> vis(n, false);
    vector<int> tin(n, -1), low(n, -1);
    int clock = 0;
    set<int> cutpoints;
    std::function<void(int, int)> dfs = [&](int v, int p = -1) {
        vis[v] = true;
        tin[v] = low[v] = clock++;
        int children=0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (vis[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1)
                    cutpoints.insert(v);
                ++children;
            }
        }
        if (p == -1 && children > 1)
            cutpoints.insert(v);
    };
    for (int i=0;i<n;i++) {
        if (!vis[i]) dfs(i, -1);
    }
    return cutpoints;
}

// Đếm số lượng ccnum trên grid
int connectedComponentNum(vector<string>& grid, char node = '#') {
    int ccnum = 0;
    int n = grid.size(), m = grid[0].size();
    vector<bool> vis(n * m, false);
    std::function<void(int, int)> dfs = [&](int i, int j){
        vis[i * m + j] = true;
        if (i+1 < n && grid[i+1][j] == node && !vis[(i+1) * m + j]) dfs(i+1, j);
        if (i-1 >= 0 && grid[i-1][j] == node && !vis[(i-1) * m + j]) dfs(i-1, j);
        if (j+1 < m && grid[i][j+1] == node && !vis[i*m+j+1]) dfs(i, j+1);
        if (j-1 >= 0 && grid[i][j-1] == node && !vis[i*m+j-1]) dfs(i, j-1);
    };
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (!vis[i*m+j] && grid[i][j] == node) ccnum++, dfs(i, j);
        }
    }
    return ccnum;
}

const int maxN = 1000003;
template<unsigned int mod = mod>
struct mint {
    friend std::ostream& operator<<(std::ostream& os, const mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, mint &s) { return os >> s.x;}
    unsigned int x;
 
    mint() : x(0) {}
    mint(ll _x) { // auto convert ll to mint.
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }
 
    mint& operator += (const mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator -= (const mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    mint& operator *= (const mint &a) {
        x = (unsigned long long)x * a.x % mod;
        return *this;
    }
    mint& operator /= (const mint &a) {
        return *this *= a.inv();
    }

    mint power(ll pw) const {
        mint res = 1;
        mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    mint inv() const {
        assert(x != 0);
        unsigned int t = x;
        unsigned int res = 1;
        while(t != 1) {
            unsigned int z = mod / t;
            res = (unsigned long long)res * (mod - z) % mod;
            t = mod - t * z;
        }
        return res;
    }
    
    mint operator + (const mint &a) const {
        return mint(*this) += a;
    }
    mint operator - (const mint &a) const {
        return mint(*this) -= a;
    }
    mint operator * (const mint &a) const {
        return mint(*this) *= a;
    }
    mint operator / (const mint &a) const {
        return mint(*this) /= a;
    }
 
    bool operator == (const mint &a) const {
        return x == a.x;
    }
    bool operator != (const mint &a) const {
        return x != a.x;
    }
    bool operator < (const mint &a) const {
        return x < a.x;
    }
    
    // Hàm này chỉ chạy với n,r < maxN (~ 1e6)
    mint nCr(mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (r < 0 || this->x < r.x) return 0;
        if (f.size() == 0) cal_factor();
        return mint(f[x]) * mint(finv[r.x]) * mint(finv[x-r.x]);
    }
    mint nPr(mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (x < r.x) return 0; // xC(r.x)
        if (f.size() == 0) cal_factor();
        return mint(f[x]) * mint(finv[x-r.x]);
    }
private:
    vector<ll> f, finv;
    void cal_factor() { std::function<vector<ll>(int)> mod_inv_range = [&](int sz){ vector<ll> inv(sz, 1); for (int i=2;i<sz;i++){ inv[i] = mod - (mod/i) * inv[mod%i] % mod;} return inv;}; f.resize(maxN, 1); finv.resize(maxN, 1); vector<ll> inv = mod_inv_range(maxN); for (ll i=1;i < (int) f.size();i++){ f[i] = (f[i-1] * i) % mod; finv[i] = (finv[i-1] * inv[i]) %mod;}}
};

// Chuyen doi grid sang graph
set<int> nodes;
vector<vector<int>> grid2Graph(vector<string>& grid, char node = '#') {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> adj(n*m+1);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (grid[i][j] != node) continue;
            nodes.insert(i * m + j);
            if (i+1 < n && grid[i+1][j] == node) {
                adj[i*m + j].push_back((i+1)*m + j); 
                adj[(i+1)*m + j].push_back(i*m + j); 
            }
            if (j+1 < m && grid[i][j+1] == node) {
                adj[i*m + j].push_back(i*m + j+1);
                adj[i*m + j+1].push_back(i*m + j);
            }
        }
    }
    return adj;
}

class DSU {
public:
    int components;
    vector<int> rank, parent, siz;
    stack<tuple<int, int, int, int>> op; //a, b, rankA, rankB

    DSU() {}
    DSU(int n) {
        components = n;
        rank.resize(n);
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        return (v == parent[v] ? v : find(parent[v]));
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;

        if (rank[a] < rank[b]) swap(a, b);
        op.push(make_tuple(a, b, rank[a], rank[b]));

        components--;
        parent[b] = a;
        rank[a] += rank[a] == rank[b];
    }

    bool isSame(int a, int b) { return find(a) == find(b); }

    void rollback() {
        if (op.empty()) return;

        auto [a, b, rankA, rankB] = op.top();
        op.pop();

        components++;
        parent[a] = a;
        parent[b] = b;
        rank[a] = rankA;
        rank[b] = rankB;
    }
};


typedef pair<int,int> Edge;

struct Event {
    int type;
    Edge edge;
    static const int ADD = 1;
    static const int REMOVE = -1;
    static const int QUERY = 0; // not used
    friend std::ostream& operator<<(std::ostream& os, const Event s) { return os << destructure(s);}
};


struct Node {
    vector<Edge> edges; // lưu các node tồn tại tại thời điểm này
    int event_type = 0;
    bool is_null = true;
    static Node v() { // ***
        return Node{.is_null = false}; // ***
    } // ***

    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

/*
      0 
    /   \
   1     2
  / \   / \
 3   4 5   6
*/
struct SegmentTree {
    int realN, n; // realN: kích thước ban đầu của mảng, n là kích thước làm tròn tới pow(2)
    vector<Node> dat;
    SegmentTree() {}
    SegmentTree(vector<Node>& v){ build(v);}
    void build(vector<Node>& v) {
        for (auto &node: v) assert(!node.is_null);
        realN = (int) v.size();
        n = 1; while (n < realN) n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
    }
    // Edge xuat hien tren do thi tai thoi diem start -> end
    void addEdge(Edge edge, int start_time, int end_time) {
        if (edge.first > edge.second) swap(edge.first, edge.second);
        // Lấy ra mọi node có liên quan rồi đẩy dữ liệu vào đây
        auto nodeIds = query(start_time, end_time);
        for (auto nodeId: nodeIds) {
            dat[nodeId].edges.push_back(edge);
        }
    }
    // tra ve id cua cac node co lien quan
    vector<int> query(int l, int r){
        assert(l <= r);
        vector<int> relatedNodeIds;
        l += n - 1; r += n;
        while (l < r) {
            if ((l & 1) == 0) relatedNodeIds.push_back(l);
            if ((r & 1) == 0) relatedNodeIds.push_back(r-1);
            l = l / 2; r = (r - 1) / 2;
        }
        return relatedNodeIds;
    }
    Node& getBaseNode(int ith) {
        auto q = query(ith, ith);
        assert((int) q.size() == 1);
        return dat[q[0]];
    }
    // tra ve children cua node tren segment tree
    vector<int> children(int nodeId) {
        if (nodeId >= 0 && nodeId < n - 1)
            return vector<int>{nodeId * 2 + 1, nodeId * 2+ 2};
        return {};
    }
    // tra ve parent cua node tren segment tree. nodeId la index trong seg.dat[]
    int parent(int nodeId) {
        int p = (nodeId - 1) /2;
        if (p >= 0 && p < n-1)
            return p;
        return -1;
    }
    // baseNode là node ở mảng a ban đầu. ko null & ko có children
    bool isBaseNode(int u) {
        return !(u >= 0 && u < n - 1) && !dat[u].is_null;
    }
    /*
    Chuyển event thành timeline rồi thêm vào trên cây.
    */
    void addEvents(vector<vector<Event>>& events) {
        map<Edge, int> startTime;
        for (int i=0;i<(int) events.size();i++) {
            for (auto eventAtSameTime: events[i]) {
                auto edge = eventAtSameTime.edge;
                if (eventAtSameTime.type == 1) { // add
                    startTime[edge] = i;
                } else if (eventAtSameTime.type == -1) { // remove
                    // assert(startTime.find(edge) != startTime.end() && "Edge(u, v) lấy u < v. u > v gây lỗi. Kiểm tra lúc events.push_back()");
                    addEdge(edge, startTime[edge], i-1);
                    startTime.erase(edge);
                }
            }
        }
        // những cạnh được thêm vào nhưng không bao giờ xóa đi -> tồn tại từ lúc thêm vào -> inf
        int inf = (int) events.size() - 1;
        for (auto [edge, start_time]: startTime)
            addEdge(edge, start_time, inf);
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& v: grid) cin >> v;
    auto adj = grid2Graph(grid, '#');
    auto cutpoints = findCutPoints(adj);
    // Dung cai cutpoint nay de xu ly rieng cac node.
    // Neu ko phai cutpoint thi cac node dung le -> ccnum-1
    //                          cac node co canh -> ccnum giu nguyen
    vector<vector<Event>> events; // type, edge

    // Chỉ có add/remove được đưa vào segtree. Query lấy kết quả sẽ được đánh dấu để xử lý sau
    vector<int> queryEventIndexes;
    int curIndex = 0;
    // Thêm sự kiện khởi tạo - thêm các cạnh có sẵn vào trên cây | sự kiện rỗng
    vector<Event> init_events;
    for (auto u: nodes) {
        for (auto v: adj[u]) {
            if (u > v) continue; // skip để u->v, v->u ko bị lặp lại 2 lần
            init_events.push_back({Event::ADD, Edge{u, v}});
        }
    }
    if ((int) init_events.size() != 0)
        events.push_back(init_events);
    curIndex++;

    // Lien tuc cac su kien xoa -> query -> them vao dan xen
    for (auto u: cutpoints) {
        // Xoa moi canh lien quan toi node do
        vector<Event> removeEvents;
        for (auto v: adj[u])
            removeEvents.push_back({Event::REMOVE, Edge{min(u, v), max(u, v)}});

        events.push_back(removeEvents);
        // Remove xong thì sẽ lấy ra kết quả
        queryEventIndexes.push_back(curIndex);
        curIndex++;

        // Them tro lai toan bo cac canh
        vector<Event> addEvents;
        for (auto v: adj[u])
            addEvents.push_back({Event::ADD, Edge{min(u, v), max(u, v)}});

        events.push_back(addEvents);
        curIndex++;
    }    

    dbg(queryEventIndexes, events.size());
    vector<Node> a((int) events.size(), Node::v());
    SegmentTree seg(a);
    seg.addEvents(events);
    
    dbg(events);

    DSU dsu(n * m);
    // Khởi tạo mọi điểm đều ko có cạnh nào -> số ccnum bằng số node #
    int ccnum = (int) nodes.size();
    mint sum_ccnum = 0;
    vector<int> res;
    std::function<void(int)> dfs = [&](int u){
        int merge_num = 0;
        for (auto edge: seg.dat[u].edges) {
            if (!dsu.isSame(edge.first, edge.second)) {
                dsu.merge(edge.first, edge.second);
                merge_num++;
                ccnum--;
            }
        }
        // if (seg.isBaseNode(u) && seg.dat[u].event_type == 0) { // base node
        if (seg.isBaseNode(u)) {
            res.push_back(ccnum-1);
        }
        for (auto child: seg.children(u)) dfs(child);
        for (int i=0;i<merge_num;i++) {
            dsu.rollback();
            ccnum++;
        }
    };
    dfs(0);
    for (auto i: queryEventIndexes) {
        sum_ccnum += res[i];
    }
    ccnum = connectedComponentNum(grid, '#');
    // Tìm ra các node không phải cut point và xử lý
    for (auto node: nodes) {
        if (!cutpoints.contains(node)) {
            if ((int) adj[node].size() == 0) {
                sum_ccnum += ccnum -1;
            } else sum_ccnum += ccnum;
        }
    }
    dbg(cutpoints);
    dbg(sum_ccnum);
    cout << sum_ccnum / nodes.size();
    show_exec_time();
}
/*
Chuyển từ dạng event đơn vector<int> -> event kép vector<vector<int>> nhiều sự kiện xảy ra 1 lúc để làm giảm
kích thước segment tree
* giảm kích thước của segment tree xuống -> thêm tất cả sự kiện vào có vẻ ko ổn vì kích thước quá lớn
* sự kiện khởi tạo luôn được đặt ở đầu??
* Bỏ qua sự kiện query -> lấy đầu ra sau khi xử lý sự kiện??
* map kia có làm chương trình bị chậm không -> thay thế bằng cách nào nhanh hơn được không? unorrdered_map??
*/
