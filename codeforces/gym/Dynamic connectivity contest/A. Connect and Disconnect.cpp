// https://codeforces.com/gym/100551/problem/A
#include<bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct DSU {
    vector<int> parent, size;
    // stores info from the past
    vector<pair<int, int>> past_parent, past_size;
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) { return (parent[x] == x) ? x : find(parent[x]); }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (size[a] < size[b]) { swap(a, b); }
        // add to history
        past_parent.push_back({b, parent[b]});
        past_size.push_back({a, parent[a]});

        if (a != b) {
            parent[b] = a;
            size[a] += size[b];
        }
    }

    bool isSame(int a, int b) { return find(a) == find(b); }

    // Reverts to previous DSU state.
    void rollback() {
        parent[past_parent.back().first] = past_parent.back().second;
        size[past_size.back().first] = past_size.back().second;
        past_parent.pop_back();
        past_size.pop_back();
    }
};

typedef pair<int,int> Edge;

struct Event {
    int type;
    Edge edge;
    friend std::ostream& operator<<(std::ostream& os, const Event s) { return os << destructure(s);}
};

struct Node {
    vector<Edge> edges; // lưu các node tồn tại tại thời điểm này
    int event_type = 0; // baseNode sẽ lưu thêm event_type để trả về kết quả cho query
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
    void add(int start_time, int end_time, Edge edge) {
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
        return (int) children(u).size() == 0 && !dat[u].is_null;
    }
    /*
    Chuyển event thành timeline rồi thêm vào trên cây.
    */
    void addEvents(vector<Event>& events) {
        map<Edge, int> startTime;
        for (int i=0;i<(int) events.size();i++) {
            auto edge = events[i].edge;
            if (events[i].type == 1) { // add
                startTime[edge] = i;
            } else if (events[i].type == -1) { // remove
                assert(startTime.find(edge) != startTime.end()); // chắc chắn rằng cạnh này có rồi mới xóa đi được. Lưu ý thứ tự Edge(u, v) thì u<v
                add(startTime[edge], i, edge);
                startTime.erase(edge);
            }
        }
        // những cạnh được thêm vào nhưng không bao giờ xóa đi -> tồn tại từ lúc thêm vào -> inf
        int inf = (int) events.size() - 1;
        for (auto [edge, start_time]: startTime)
            add(start_time, inf, edge);
        // Them event_type vào trong baseNode để duyệt ở dfs() thì in ra luôn
        for (int i=0;i<realN;i++) dat[n + i - 1].event_type = events[i].type;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        freopen("connect.in", "r", stdin);
        freopen("connect.out", "w", stdout);
    #endif
    /*
    Dung segment tree co san
    -> Query tra ve danh sach cac node lien quan
    -> Clear cac node cam thua du lieu -> node cha co roi thi xoa du lieu tai node con
    */
    int n, q;
    cin >> n >> q;
    // Read input
    vector<Event> events;
    for (int i=0;i<q;i++) {
        char type;
        cin >> type;
        if (type == '?') {
            events.push_back(Event{0, Edge{-1, -1}});
        } else if (type == '+') {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            events.push_back(Event{1, Edge{--u, --v}});
        } else if (type == '-') {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            events.push_back(Event{-1, Edge{--u, --v}});
        }
    }
    dbg(events);
    // Build segment tree
    vector<Node> a(q, Node::v());
    SegmentTree seg(a);
    seg.addEvents(events);

    DSU dsu(n);
    int ccnum = n;
    std::function<void(int)> dfs = [&](int u) {
        int merge_num = 0;
        for (auto edge: seg.dat[u].edges) {
            if (!dsu.isSame(edge.first, edge.second)) {
                dsu.merge(edge.first, edge.second);
                merge_num++;
                ccnum--;
            }
        }
        if (seg.isBaseNode(u) && seg.dat[u].event_type == 0) { // base node
            dbg(u);
            cout << ccnum << '\n';
        }
        for (auto child: seg.children(u)) dfs(child);
        for (int i=0;i<merge_num;i++) {
            dsu.rollback();
            ccnum++;
        }
    };
    dfs(0);
    show_exec_time();
}
