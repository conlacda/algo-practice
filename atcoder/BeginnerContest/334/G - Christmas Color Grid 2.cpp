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
Optimise:
* chỉ xét cut point để giảm kích thước của segment tree
*/



//===================================================================
/*
// Đoạn code dưới đây xét toàn bộ mọi node để đưa vào dynamic connectivity dẫn tới TLE
// Cần thêm optimise chỉ xét cutpoint như bên trên thì mới pass
// Sử dụng template mới. Code trên sử dụng template cũ
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
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

const int maxN = 1000003;
vector<ll> factorial, factorial_inv; // giai thừa
template<unsigned int mod = mod>
struct Mint {
    friend std::ostream& operator<<(std::ostream& os, const Mint &s) { return os << s.x;}
    friend std::istream& operator>>(std::istream& os, Mint &s) { return os >> s.x;}
    unsigned int x;
 
    Mint() : x(0) {}
    Mint(ll _x) { // auto convert ll to Mint.
        _x %= mod;
        if (_x < 0) _x += mod;
        x = _x;
    }

    unsigned int val() {
        return x;
    }

    Mint& operator += (const Mint &a) {
        x += a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator -= (const Mint &a) {
        x += mod - a.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    Mint& operator *= (const Mint &a) {
        x = (unsigned long long)x * a.x % mod;
        return *this;
    }
    Mint& operator /= (const Mint &a) {
        return *this *= a.inv();
    }

    Mint power(ll pw) const {
        Mint res = 1;
        Mint cur = *this;
        while(pw) {
            if (pw & 1) res *= cur;
            cur *= cur;
            pw >>= 1;
        }
        return res;
    }
    // Chứng minh xem tại CPH - Modular inverse
    Mint inv() const {
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
    
    Mint operator + (const Mint &a) const {
        return Mint(*this) += a;
    }
    Mint operator - (const Mint &a) const {
        return Mint(*this) -= a;
    }
    Mint operator * (const Mint &a) const {
        return Mint(*this) *= a;
    }
    Mint operator / (const Mint &a) const {
        return Mint(*this) /= a;
    }
 
    bool operator == (const Mint &a) const {
        return x == a.x;
    }
    bool operator != (const Mint &a) const {
        return x != a.x;
    }
    bool operator < (const Mint &a) const {
        return x < a.x;
    }
    
    // Hàm này chỉ chạy với n,r < maxN (~ 1e6)
    Mint nCr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (r < 0 || this->x < r.x) return 0;
        if (factorial.size() == 0) cal_factor();
        return Mint(factorial[x]) * Mint(factorial_inv[r.x]) * Mint(factorial_inv[x-r.x]);
    }
    Mint nPr(Mint r) {
        assert(this->x < maxN && r < maxN && "n, r phải nhỏ hơn maxN");
        if (x < r.x) return 0; // xC(r.x)
        if (factorial.size() == 0) cal_factor();
        return Mint(factorial[x]) * Mint(factorial_inv[x-r.x]);
    }
private:
    void cal_factor() { std::function<vector<ll>(int)> mod_inv_range = [&](int sz){ vector<ll> inv(sz, 1); for (int i=2;i<sz;i++){ inv[i] = mod - (mod/i) * inv[mod%i] % mod;} return inv;}; factorial.resize(maxN, 1); factorial_inv.resize(maxN, 1); vector<ll> inv = mod_inv_range(maxN); for (ll i=1;i < (int) factorial.size();i++){ factorial[i] = (factorial[i-1] * i) % mod; factorial_inv[i] = (factorial_inv[i-1] * inv[i]) %mod;}}
};
using mint = Mint<mod>;

// Rollback DSU
struct RollbackDSU {
    int ccnum; // connected component num
    vector<int> rank, parent, siz;
    stack<tuple<int, int, int, int>> op; //a, b, rankA, rankB

    RollbackDSU() {}
    RollbackDSU(int n) {build(n);};
    void build(int n) {
        ccnum = n;
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

        ccnum--;
        parent[b] = a;
        rank[a] += rank[a] == rank[b];
    }

    bool isSame(int a, int b) { return find(a) == find(b); }

    void rollback() {
        if (op.empty()) return;

        auto [a, b, rankA, rankB] = op.top();
        op.pop();

        ccnum++;
        parent[a] = a;
        parent[b] = b;
        rank[a] = rankA;
        rank[b] = rankB;
    }
};


typedef pair<int,int> Edge;

struct Event {
    int type; // add, remove
    Edge edge; // cạnh được thêm/xóa khỏi graph
    static const int ADD = 1, REMOVE = -1, QUERY = 0;
    friend std::ostream& operator<<(std::ostream& os, const Event s) { return os << destructure(s);}
};

struct Node {
    vector<Edge> edges; // lưu các node tồn tại tại thời điểm này
};

struct SegmentTree {
    int n;
    vector<Node> dat;
    SegmentTree() {};
    void build(int _n) {
        n = (int) pow(2, ceil(log2(_n)));
        dat.resize(2 * n -1);
    }
    // tra ve id cua cac node co lien quan
    vector<int> query(int l, int r) {
        assert(l <= r);
        vector<int> nodeIds;
        l += n - 1; r += n;
        while (l < r) {
            if ((l & 1) == 0) nodeIds.push_back(l);
            if ((r & 1) == 0) nodeIds.push_back(r-1);
            l = l / 2; r = (r - 1) / 2;
        }
        return nodeIds;
    }
    Node& getBaseNode(int ith) { return dat[query(ith, ith).at(0)]; }
    // tra ve children cua node tren segment tree
    vector<int> children(int nodeId) { return (nodeId >= 0 && nodeId < n - 1) ? vector<int>{nodeId * 2 + 1, nodeId * 2+ 2} : vector<int>{};}
    // tra ve parent cua node tren segment tree. nodeId la index trong seg.dat[]
    int parent(int nodeId) { int p = (nodeId - 1) /2; return (p >= 0 && p < n-1) ? p: -1;}
    // baseNode là node ở mảng a ban đầu. ko null & ko có children
    bool isBaseNode(int u) { return !(u >= 0 && u < n - 1);}

    // Edge xuat hien tren do thi tai thoi diem start -> end
    void addEdge(Edge edge, int start_time, int end_time) {
        if (edge.first > edge.second) swap(edge.first, edge.second);
        // Lấy ra mọi node có liên quan rồi đẩy dữ liệu vào đây
        auto nodeIds = query(start_time, end_time);
        for (auto nodeId: nodeIds) 
            dat[nodeId].edges.push_back(edge);
    }
};

struct DynamicConnectivity {
private:
    int lastEvent = Event::ADD;
    int event_sz, node_num;
    // chuyển events sang tập hợp cạnh và thời gian tồn tại
    vector<tuple<Edge, int, int>> events2Timeline(vector<vector<Event>> events) {
        vector<tuple<Edge, int, int>> timeline; // tuple<Edge, start, end>
        map<Edge, int> startTime;
        for (int time=0;time<event_sz;time++) { // xét toàn bộ sự kiện của từng thời điểm
            for (auto event: events[time]) {
                if (event.type == Event::ADD) { // add
                    startTime[event.edge] = time;
                } else if (event.type == Event::REMOVE) { // remove
                    // remove cạnh tức là cạnh này chỉ tồn tại tới thời điểm i hiện tại
                    if (startTime[event.edge] <= time -1) // nếu sự kiện add + remove cùng 1 cạnh liền nhau thì cơ bản là nó ko tồn tại
                        timeline.push_back({event.edge, startTime[event.edge], time -1});
                    startTime.erase(event.edge);
                }
            }
        }
        // những cạnh được thêm vào nhưng không bao giờ xóa đi -> tồn tại từ lúc thêm vào -> forever
        int forever = (int) events.size() - 1;
        for (auto [edge, start_time]: startTime)
            timeline.push_back({edge, start_time, forever});
        return timeline;
    }
public:
    SegmentTree seg;
    RollbackDSU dsu;
    vector<vector<Event>> events;
    vector<int> query_indexes;
    DynamicConnectivity(vector<vector<int>>& adj) {
        node_num = adj.size();
        // add initial graph as ADD events
        events.push_back({});
        for (int u=0;u<node_num;u++) {
            for (auto v: adj[u]) {
                if (u < v) events[0].push_back(Event{Event::ADD, Edge{u, v}});
            }
        }
        lastEvent = Event::ADD;
        // build dsu
        dsu.build(node_num);
    };

    // Add event one by one
    void addEvent(Event e) {
        if (e.type == Event::QUERY) {
            query_indexes.push_back((int)events.size() -1);
            lastEvent = Event::QUERY;
            return;
        }
        // ADD, REMOVE
        if ((int) events.size() == 1 || lastEvent == Event::QUERY) events.push_back({}); // events[0] is reserved
        if (e.edge.first > e.edge.second) swap(e.edge.first, e.edge.second);
        events[(int) events.size() -1].push_back(e);
        lastEvent = Event::ADD; // or Event:REMOVE is same
    }
    // Build + add all events to segtree's nodes
    void prepareSegTree() {
        event_sz = (int) events.size();
        seg.build(event_sz);
        auto timeline = events2Timeline(events);
        for (auto [edge, start, end]: timeline)
            seg.addEdge(edge, start, end);
    }
    /* Chạy DFS() từ đỉnh qua toàn bộ cây.
     * Tại node cuối (base node) thì lấy ra kết quả
     * Chỉ những index nào có query sẽ được lấy ra.
    */
    vector<int> getAns() {
        vector<int> resAfterEachEvent; // kết quả sau mỗi cụm events
        std::function<void(int)> dfsOnSegTree = [&](int u) {
            // CHANGE HERE // *** // ***
            int merge_num = 0;
            // Tới node u thì thêm tất cả các edge đang tồn tại trong node u vào
            for (auto edge: seg.dat[u].edges) {
                if (!dsu.isSame(edge.first, edge.second)) {
                    dsu.merge(edge.first, edge.second);
                    merge_num++;
                }
            }
            // dfs() tới các child
            for (auto child: seg.children(u)) dfsOnSegTree(child);
            // tới baseNode là tầng cuối cùng, nếu event_type là query thì in ra kết quả
            if (seg.isBaseNode(u)) { // base node
                resAfterEachEvent.push_back(dsu.ccnum); // lấy ra kết quả ngay sau khi sự kiện xảy ra.
                // Sau đó có queryIndexes lọc ra các kết quả cần lấy 
            }
            // Duyệt xong toàn bộ con thì quay lại xóa các node đã được thêm vào
            for (int i=0;i<merge_num;i++)
                dsu.rollback();
        };
        dfsOnSegTree(0); // dfs from root = 0
        // Get needed results
        vector<int> neededRes;
        for (auto index: query_indexes) neededRes.push_back(resAfterEachEvent[index]);
        return neededRes;
    }
};
/*
DynamicConnectivity dc(vector<vector<int>>& adj);
AddEvent
    dc.addEvent(Event{Event::ADD, Edge{u, v}}); // one by one
    dc.addEvent(Event{Event::QUERY});
dc.prepareSegTree(); // push edge to segtree's nodes
dc.getAns(); // run dfs on segtree then collect answer
*/

// Chuyen doi grid sang graph
// vector<int> nodeIds; // thuận tiện cho việc duyệt qua các node sau này
vector<vector<int>> grid2Graph(vector<string>& grid, char node = '#') {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> adj(n*m);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (grid[i][j] != node) continue;
            // nodeIds.push_back(i * m + j);
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
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int row, col;
    cin >> row >> col;
    vector<string> grid(row);
    for (auto& v: grid) cin >> v;
    auto adj = grid2Graph(grid);
    DynamicConnectivity dc(adj);
    // Xét từng node -> xóa toàn bộ cạnh của node đó -> query -> thêm toàn bộ cạnh vào node đó
    // Có 2 loại node:
    // * Đứng 1 mình -> xóa thì số ccnum giảm đi 1
    // * Có cạnh -> xử lý bằng xóa cạnh tạo ra event trong dynamic connectivity
    for (int i=0;i<row*col;i++) {
        if ((int) adj[i].size() == 0) continue;
        for (auto v: adj[i])
            dc.addEvent({Event::REMOVE, Edge{i, v}});
        
        dc.addEvent({Event::QUERY});
        for (auto v: adj[i])
            dc.addEvent({Event::ADD, Edge{i, v}});
    }
    dc.prepareSegTree();
    int unexpectedCcnum = 0; // số dấu . được đếm thành 1 cc
    for (auto v: grid) unexpectedCcnum += std::count(v.begin(), v.end(), '.');
    mint sum_ccnum = 0;
    for (auto v: dc.getAns()) {
        sum_ccnum += v - unexpectedCcnum - 1;
    }
    dbg(sum_ccnum);
    // ***
    // đoạn này đang sai ko biết sao dsu tính ccnum lại sai
    dbg(dc.getAns(),unexpectedCcnum);
    // xử lý node đứng 1 mk -> mất đi thì số lượng ccnum - 1
    int aloneNodeNum = 0;
    for (int i=0;i<row;i++) {
        for (int j=0;j<col;j++) {
            if (grid[i][j] == '#' && adj[i*col+j].size() == 0) aloneNodeNum++;
        }
    }
    // mỗi cái alone tạo ra dc.dsu.ccnum - unexpectedCcnum - 1 cc
    int ccnum = connectedComponentNum(grid, '#');
    sum_ccnum += (ccnum - 1) * aloneNodeNum;
    cout << sum_ccnum / (row*col - unexpectedCcnum);

    show_exec_time();
}
*/
