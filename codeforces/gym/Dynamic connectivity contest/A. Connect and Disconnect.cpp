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
    int ccnum; // connected component num
    vector<int> rank, parent, siz;
    stack<tuple<int, int, int, int>> op; //a, b, rankA, rankB

    DSU() {}
    DSU(int n) {
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
    static const int ADD = 1;
    static const int REMOVE = 0;
    static const int QUERY = 2; // not used
    friend std::ostream& operator<<(std::ostream& os, const Event s) { return os << destructure(s);}
};

struct Node {
    vector<Edge> edges; // lưu các node tồn tại tại thời điểm này
    int event_type = 0; // baseNode sẽ lưu thêm event_type để trả về kết quả cho query
    bool is_null = true;

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
        for (auto nodeId: nodeIds) 
            dat[nodeId].edges.push_back(edge);
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
        for (int time=0;time<(int) events.size();time++) { // xét toàn bộ sự kiện của từng thời điểm
            for (auto event: events[time]) {
                if (event.type == Event::ADD) { // add
                    startTime[event.edge] = time;
                } else if (event.type == Event::REMOVE) { // remove
                    // remove cạnh tức là cạnh này chỉ tồn tại tới thời điểm i hiện tại
                    addEdge(event.edge, startTime[event.edge], time-1);
                    startTime.erase(event.edge);
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
    #else
        freopen("connect.in", "r", stdin);
        freopen("connect.out", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    // Read input - tại đây tạo ra vector<vector<Event>> events và queryIndexes
    vector<vector<Event>> events;
    // Sự kiện khởi tạo - đẩy tất cả các cạnh đã có của đồ thị vào
    events.push_back({}); // do không có gì nên sẽ để trống

    vector<int> queryIndexes; // lưu lại các index cần lấy ra kết quả. index i thể hiện kết quả được in ra sau sự kiện add/remove thứ i
    int curIndex = 0;
    for (int i=0;i<q;i++) {
        char type;
        cin >> type;
        if (type == '?') {
            queryIndexes.push_back(curIndex);
            continue;
        }
        int u, v; cin >> u >> v; u--; v--;
        if (u > v) swap(u, v);
        curIndex++;
        if (type == '+') {
            vector<Event> addEvents {Event{Event::ADD, Edge{u, v}}};
            events.push_back(addEvents);
        } else {
            // type == '-'
            vector<Event> removeEvents {Event{Event::REMOVE, Edge{u, v}}};
            events.push_back(removeEvents);
        }
    }
    vector<Node> a(events.size(), Node{.is_null = false});
    SegmentTree seg(a);
    seg.addEvents(events);

    DSU dsu(n);
    int ccnum = n;
    vector<int> res;
    std::function<void(int)> dfs = [&](int u) {
        int merge_num = 0;
        // Tới node u thì thêm tất cả các edge đang tồn tại trong node u vào
        for (auto edge: seg.dat[u].edges) {
            if (!dsu.isSame(edge.first, edge.second)) {
                dsu.merge(edge.first, edge.second);
                merge_num++;
                ccnum--;
            }
        }
        // dfs() tới các child
        for (auto child: seg.children(u)) dfs(child);
        // tới baseNode là tầng cuối cùng, nếu event_type là query thì in ra kết quả
        if (seg.isBaseNode(u)) { // base node
            res.push_back(ccnum); // lấy ra kết quả ngay sau khi sự kiện xảy ra.
            // Sau đó có queryIndexes lọc ra các kết quả cần lấy 
        }
        // Duyệt xong toàn bộ con thì quay lại xóa các node đã được thêm vào
        for (int i=0;i<merge_num;i++) {
            dsu.rollback();
            ccnum++;
        }
    };
    dfs(0);
    for (auto index: queryIndexes) {
        cout << res[index] << '\n';
    }
    show_exec_time();
}

/*
=> Bài này thực sự rất khó để gói nó vào template.
Hoặc gói xong nó sẽ khó maintain quá mức nên tạm thời để dạng dở dang.
Rồi viết lại cấu trúc các phần để gặp bài cụ thể sử dụng theo form.

Ví dụ:
Tại đây hỏi ccnum cần dùng DSU. Nhưng bài khác hỏi về giá trị khác thì DSU lại ko cần.
Rồi lại phải ném 1 cấu trúc khác vào trong segment tree. Như thế còn khó maintain hơn để ở main
vì các biến bị giới hạn trong class, còn để ở main thì ko cần lo scope, cứ thế sử dụng kết hợp mọi biến
*/
