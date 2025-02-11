// #pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max() / 2; // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

mt19937 _rand(std::chrono::steady_clock::now().time_since_epoch().count()); // mt19937_64
const int NULL_ID = 0;
bool is_null(int node_id) { return node_id == NULL_ID; }
struct Node {
    int id = NULL_ID, lid = NULL_ID, rid = NULL_ID;
    int pid = NULL_ID; // parent id
    int val;
    int prior = _rand(); // random heap value
    int size = 0;

    static Node v(int val) {// ***
        return Node {
            .val = val,
            .size = 1
        };
    }

    void recalc();
};

struct Lznode {
    bool reverse = false; // nếu có 1 giá trị thì ko cần set default value // ***
    int add = 0; // range add // nhưng nhiều giá trị ko set thì lúc update ko chạy đúng Lznode{true} -> add sẽ random // ***

    bool null = false; // để không phải quan tâm tới giá trị để Node = Node + Lznode_zero
    static void applyToNode(int id);
};

const int MAX_SZ = (int) 2e6; // Be careful with MLE, as well as TLE, due to allocating a large amount of memory// ***
Node nodes[MAX_SZ]; // faster in a problem with multiple testcases by reusing allocated memory
Lznode lznodes[MAX_SZ]; // do not use vector<> due to large number of nodes

struct Treap {
    // Config
    bool isSortedByValue = false; // order theo index hoặc order theo value // ***
    // Data
    vector<int> usableNodeIds; // improve speed by pre-allocating??
    int treap_index = NULL_ID + 1;

    // node bị xóa đi sẽ được chuyển về usableNodeIds
    int usableId() {
        if (usableNodeIds.empty()) {
            assert(treap_index + 1 < MAX_SZ && "số lượng node quá lớn (>5e6)");
            return treap_index++;
        }
        auto id = usableNodeIds.back();
        usableNodeIds.pop_back();
        return id;
    }

    // Tạo ra 1 node với val rồi trả về node đó (node.id là index trên nodes)
    int create_node(int val, int prior = -1) {
        int id = usableId();
        nodes[id] = Node::v(val);
        nodes[id].id = id;
        lznodes[id].null = true; // do dùng chung vector<Node|Lznode> nên khi sử dụng Node thì phải xóa dữ liệu cũ đi
        if (prior != -1) nodes[id].prior = prior;
        return id;
    }

    void recycle(int node_id) {
        if (is_null(node_id)) return;
        usableNodeIds.push_back(node_id);
        Node& node = nodes[node_id];
        recycle(node.lid); recycle(node.rid);
    }

    Node& operator[](int node_id) { return nodes[node_id]; }

    int getRootId(int id) {
        while (!is_null(nodes[id].pid)) id = nodes[id].pid;
        return id;
    }

    // Tách node_id thành 2 phần theo v | >= v goes to the right
    pair<int,int> splitByVal(int id, int val) {
        if (is_null(id)) return {NULL_ID, NULL_ID};
        Lznode::applyToNode(id);
        Node& node = nodes[id];
        if (node.val >= val) {
            auto p = splitByVal(node.lid, val);
            node.lid = p.second;
            nodes[p.second].pid = node.id; nodes[p.first].pid = NULL_ID;
            recalc(node.id);
            return {p.first, node.id};
        } else {
            auto p = splitByVal(node.rid, val);
            node.rid = p.first;
            nodes[p.first].pid = node.id; nodes[p.second].pid = NULL_ID;
            recalc(node.id);
            return {node.id, p.second};
        }
    }

    // sz nodes go left, (n-sz) nodes go right
    pair<int,int> splitBySize(int id, int sz) {
        if (is_null(id)) return {NULL_ID, NULL_ID};
        Lznode::applyToNode(id);
        Node& node = nodes[id];
        Node& left = nodes[node.lid];
        if (left.size >= sz) {
            auto p = splitBySize(node.lid, sz);
            node.lid = p.second;
            nodes[p.second].pid = node.id;
            nodes[p.first].pid = NULL_ID;
            recalc(node.id);
            return {p.first, node.id};
        } else {
            auto p = splitBySize(node.rid, sz - left.size - 1);
            node.rid = p.first;
            nodes[p.first].pid = node.id;
            nodes[p.second].pid = NULL_ID;
            recalc(node.id);
            return {node.id, p.second};
        }
    }

    // Chia thành 3 part [0:L-1], [L:R], [R:N-1]
    tuple<int, int, int> split3PartsBySize(int root, int L, int R) {
        auto [l, mr] = splitBySize(root, L);
        auto [m, r] = splitBySize(mr, R - L + 1);
        return {l, m, r};        
    }

    // Merge 2 nodes thành 1 -> trả về id node đã merge | Merge ko reorder value mà chỉ gắn 2 root vào nhau
    int merge(int id1, int id2) {
        if (is_null(id1)) return id2;
        if (is_null(id2)) return id1;
        Lznode::applyToNode(id1); Lznode::applyToNode(id2);
        // isSortedByValue = true <=> value nhỏ sang trái, lớn sang phải
        // ngược lại thì giữ lại theo index được thêm vào
        if (isSortedByValue and nodes[id1].val >= nodes[id2].val) swap(id1, id2);
        Node& lnode = nodes[id1];
        Node& rnode = nodes[id2];
        Node* mergedNode;
        if (lnode.prior > rnode.prior) {
            auto id = merge(lnode.rid, id2);
            lnode.rid = id;
            nodes[id].pid = lnode.id;
            mergedNode = &lnode;
        } else {
            auto id = merge(id1, rnode.lid);
            rnode.lid = id;
            nodes[id].pid = rnode.id;
            mergedNode = &rnode;
        }
        mergedNode->pid = NULL_ID;
        recalc(mergedNode->id);
        return mergedNode->id;
    }

    // Merge nhiều node vào 1 lúc lần lượt trái -> phải
    int merge(vector<int> ids) {
        assert(!ids.empty() && "Cần có ít nhất 1 node id trong đây");
        int root = ids[0];
        for (int i=1;i<(int) ids.size();i++)
            root = merge(root, ids[i]);
        return root;
    }

    // Index val, sau khi insert giá trị đó sẽ nằm tại vị trí index -> return new root id
    int insertAtIndex(int root, int index, int val) {
        assert(!isSortedByValue && "Order theo index thì mới có thể insert tại index!");
        auto newId = create_node(val);
        // Tách treap theo size rồi merge newId vào
        auto [l, r] = splitBySize(root, index);
        return merge({l, newId, r});
    }

    // Trả về danh sách id theo thứ tự tăng dần của val
    vector<int> inorderIds(int id, bool applyLzy = true) {
        vector<int> res;
        std::function<void(int)> go = [&](int id) {
            if (applyLzy) Lznode::applyToNode(id);
            if (is_null(id)) return;
            go(nodes[id].lid);
            res.push_back(id);
            go(nodes[id].rid);
        };
        go(id);
        return res;
    }

    void printOut(int root) {
        auto orders = inorderIds(root);
        vector<int> res;
        for (auto&id: orders) {
            res.push_back(nodes[id].val);
        }
        for (auto&v: res) cout << v << ' ';
    }

    // not-tested - not sure how it works
    int unite(int l, int r) {
        if (is_null(l)) return r;
        if (is_null(r)) return l;
        if (nodes[l].prior < nodes[r].prior)
            swap(l, r);

        pair<int,int> p = splitByVal(r, nodes[l].val);
        nodes[l].lid = unite(nodes[l].lid, p.first);
        nodes[l].rid = unite(nodes[l].rid, p.second);
        return l;
    }

    void update(int root, int L, int R, Lznode lz) { // reverseRange
        if (is_null(root)) return;
        auto [l, mid, r] = split3PartsBySize(root, L, R);
        merge({l, mid, r});
    }

    void update_all(int root, Lznode lz) {
        assert(!is_null(root));
        update(root, 0, nodes[root].size - 1, lz);
    }

    Node query(int root, int L, int R) {
        assert(!is_null(root));
        assert(R < nodes[root].size && "R lớn hơn kích thước treap tại root");
        auto [l, m, r] = split3PartsBySize(root, L, R);
        Node ans = nodes[m]; // trả về node mid  chứa dữ liệu của range[L:R]
        merge({l, m, r});
        return ans;
    }

    Node query_all(int root) {
        assert(!is_null(root));
        return query(root, 0, nodes[root].size - 1);
    }

    void recalc(int node_id) {
        if (is_null(node_id)) return;
        Node& node = nodes[node_id];
        // Query
        assert(lznodes[node_id].null);
        Lznode::applyToNode(node.lid); Lznode::applyToNode(node.rid);
        node.recalc(); // recalculate based on its data and 2 children
    }
};

// Tính toán lại giá trị của Node dựa vào val và 2 node bên dưới
void Node::recalc() {
    // Node + Node
    Node& node = nodes[id];
    Node& left = nodes[node.lid];
    Node& right = nodes[node.rid];

    int size = 1; // ***
    if (!is_null(node.lid)) { // ***
        size += left.size; // ***
    } // ***
    if (!is_null(node.rid)) { // ***
        size += right.size; // ***
    } // ***
    node.size = size; // ***
}

void Lznode::applyToNode(int id) {// ***
    // hàm này sẽ lấy lazynode trên đầu node và apply luôn xuống (cùng index) Node + Lznode
    if (is_null(id) || lznodes[id].null) return;
    Node& node = nodes[id];
    Lznode& lz = lznodes[id];
    Lznode& leftlz = lznodes[node.lid];
    Lznode& rightlz = lznodes[node.rid];
    // Đẩy lzynode xuống bên dưới
    lz.null = true;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    Treap treap;
    int root = NULL_ID;
    int x;
    cin >> x;
    root = treap.merge(root, treap.create_node(1));

    vector<int> a(n-1);
    for (auto&v: a) cin >> v;
    for (int i=0;i<=(int) a.size() - 1;i++) {
        root = treap.insertAtIndex(root, a[i]-1, i+2);
    }
    treap.printOut(root);


    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
