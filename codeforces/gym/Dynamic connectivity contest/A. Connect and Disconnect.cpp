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

/*
      0 
    /   \
   1     2
  / \   / \
 3   4 5   6
*/
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
            if ((l & 1) == 0) nodeIds.push_back(l); l = l / 2;
            if ((r & 1) == 0) nodeIds.push_back(r-1); r = (r - 1) / 2;
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
    // chuyển events sang tập hợp cạnh nào và thời gian tồn tại
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
                if (u < v) events[0].push_back({Event::ADD, Edge{u, v}});
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
    vector<int> getAns() {
        vector<int> resAfterEvent; // kết quả sau mỗi cụm events
        std::function<void(int)> dfsOnSegTree = [&](int u) {
            // CHANGE HERE // ***
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
                resAfterEvent.push_back(dsu.ccnum); // lấy ra kết quả ngay sau khi sự kiện xảy ra.
                // Sau đó có queryIndexes lọc ra các kết quả cần lấy 
            }
            // Duyệt xong toàn bộ con thì quay lại xóa các node đã được thêm vào
            for (int i=0;i<merge_num;i++)
                dsu.rollback();
        };
        dfsOnSegTree(0); // dfs from root = 0
        // Get needed results
        vector<int> neededRes;
        for (auto index: query_indexes) neededRes.push_back(resAfterEvent[index]);
        return neededRes;
    }
};
/*
DynamicConnectivity dc(vector<vector<int>>& adj);
dc.addEvent(Event{}); // one by one
dc.prepareSegTree(); // push edge to segtree's nodes
dc.getAns(); // run dfs on segtree then collect answer
*/
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    DynamicConnectivity dc(adj);

    for (int i=0;i<q;i++) {
        char type;
        cin >> type;
        if (type == '?') {
            dc.addEvent({Event::QUERY});
            continue;
        }
        int u, v; cin >> u >> v; u--; v--;
        if (u > v) swap(u, v);
        if (type == '+') {
            dc.addEvent({Event::ADD, {u, v}});
        } else {
            // type == '-'
            dc.addEvent({Event::REMOVE, {u, v}});
        }
    }
    dc.prepareSegTree();
    for (auto ans: dc.getAns()) cout << ans << '\n';

    show_exec_time();
}
