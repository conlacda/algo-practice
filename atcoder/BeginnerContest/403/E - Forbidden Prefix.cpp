// https://atcoder.jp/contests/abc403/tasks/abc403_e
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

const int MAX_SZ = (int) 2e6; // the maximum number of nodes

struct Node {
    int id, pid; // parent id
    int count = 0; // số lần string được thêm vào trie
    set<int> children{}; // mảng chứa id của children
    char val;
    static Node v(int id, int pid, char val) {
        return Node {
            .id = id,
            .pid = pid,
            .val = val
        };
    }
    bool is_leaf() { return count > 0;}
    int findChild(char val);
    int findDescendant(string s);
    void addChild(int childId) {children.insert(childId);}
    void removeChild(int childId) {children.erase(childId);}
};
vector<Node> nodes(MAX_SZ); // nodes nodes
int Node::findChild(char val) {
    for (auto&id: children) {
        if (nodes[id].val == val)
            return id;
    }
    return -1;
}
// Tìm node cuối cùng mà đi từ root tới đó = s
int Node::findDescendant(string s) {
    int id = this->id;
    for (auto&v: s) {
        id = nodes[id].findChild(v);
        if (id == -1) {
            return -1;
        }
    }
    return id;
}

struct Trie {
private:
    // trả về free id, đồng thời xóa nó khỏi danh sách
    int freeNodeId() {
        assert((int) freeNodeIds.size() > 0 && "not enough node to allocate");
        auto id = freeNodeIds[(int) freeNodeIds.size() - 1];
        freeNodeIds.pop_back();
        return id;
    }
    // Đưa id trở lại pool, đồng thời xóa nó khỏi children của parent
    void recycle(int id) {
        freeNodeIds.push_back(id);
        Node& parentNode = nodes[nodes[id].pid];
        parentNode.removeChild(id);
    }
public:
    int ROOT_ID;
    vector<int> freeNodeIds; // danh sách node id có thể sử dụng
    // chỉ định rootId khi có nhiều Trie, rootId sẽ là node đầu tiên trie đó dùng tránh dùng chung
    Trie(int rootId = 0): ROOT_ID(rootId) {
        freeNodeIds.resize(MAX_SZ, 0);
        std::iota(freeNodeIds.begin(), freeNodeIds.end(), rootId);
        reverse(freeNodeIds.begin(), freeNodeIds.end());
        nodes[ROOT_ID] = Node::v(freeNodeId(), -1, '\0');
    }
    
    void insert(string s) {
        int curid = ROOT_ID;
        for (auto&v: s) {
            auto childId = nodes[curid].findChild(v);
            if (childId == -1) {
                auto freeId = freeNodeId();
                nodes[freeId] = Node::v(freeId, nodes[curid].id, v);
                nodes[curid].addChild(freeId);
                childId = freeId;
            }
            curid = childId;
        }
        nodes[curid].count++; // set bằng 1 nếu 1 string chỉ được insert 1 lần
    }

    // Xóa toàn bộ string có prefix trong trie. Trả về số lượng đã xóa.
    int erase_by_prefix(string s) {
        auto id = nodes[ROOT_ID].findDescendant(s);
        if (id == -1)
            return 0;

        // số lượng string match prefix bị xóa - chính là số lượng leaf bị xóa
        int prefix_matched = nodes[id].count; 
        // Xóa toàn bộ descendant
        // Recycle node và mọi descendant với dfs()
        std::function<void(int)> dfs_recycle = [&](int id) {
            prefix_matched += nodes[id].count;
            auto children = nodes[id].children;
            for (auto v: children)
                dfs_recycle(v);
            recycle(id);
        };
        auto children = nodes[id].children;
        for (auto&v: children) dfs_recycle(v);

        // Xóa từ node hiện tại đi lên
        // Tricky: đánh dấu nó hiện tại là lá rồi dùng erase để xóa là xong
        nodes[id].count++;
        erase(s);
        return prefix_matched;
    }

    // Xóa đi 1 string trong trie. false nếu không tìm thấy.
    bool erase(string s) {
        int curid = ROOT_ID;
        for (auto&v: s) {
            curid = nodes[curid].findChild(v);
            if (curid == -1) return false; // không tìm thấy
        }
        if (!nodes[curid].is_leaf())
            return false;

        nodes[curid].count = 0;
        // Nếu còn node bên dưới thì không làm gì cả
        if (nodes[curid].children.size() > 0) {
            return true;
        }
        // Xóa từ dưới ngược trở lên trên
        // Nếu gặp 1 node là lá hoặc 1 node có nhánh khác thì dừng lại
        while (curid != ROOT_ID) {
            recycle(curid);
            curid = nodes[curid].pid;
            if (nodes[curid].is_leaf() or nodes[curid].children.size() > 0)
                break;
        }
        return true;
    }
    // Kiểm tra xem có string nào trong trie là prefix của longStr
    bool prefix_exist(string longStr) {
        int id = ROOT_ID;
        for (auto&v: longStr) {
            id = nodes[id].findChild(v);
            if (id == -1) return false;
            if (nodes[id].is_leaf()) return true;
        }
        return false;
    }
    // Kiểm tra nếu shortStr là prefix của ít nhất 1 string trong trie
    bool is_prefix(string shortStr) {
        return (nodes[ROOT_ID].findDescendant(shortStr) != -1);
    }
// Debug
    // số lượng node đã sử dụng (bao gồm cả root)
    int usedNum() {
        return MAX_SZ - (int) freeNodeIds.size();
    }
};

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    X = {at}
    Số string trong Y mà không có string nào trong X match
    Một khi string trong Y match rồi sẽ không bao giờ đếm trở lại nữa
    Khi match rồi thì sẽ remove nó ra khỏi trie bên Y
    Dựng 2 trie cho X và Y
    Khi X được thêm vào, chạy nó vào Y xem có match không?
        Nhưng nó chỉ chạy được có 1 phần nhỏ chưa tới lá được
        Từ đó chạy thẳng xuống lá rồi xóa các lá đó đi + xóa 1 phần ngọn thừa đi nữa
    Khi Y được thêm vào, chạy vào X xem nó tới được lá không
        Nếu tới được lá thì loại bỏ nó luôn
    */
    int q;
    cin >> q;
    int ans = 0;
    Trie X(0), Y(1000000);
    while (q--) {
        int t;
        string s;
        cin >> t >> s;
        if (t == 1) {
            // Thêm vào x
            X.insert(s);
            ans -= Y.erase_by_prefix(s);
        } else {
            // Thêm vào y
            if (!X.prefix_exist(s)) {
                ans++;
                Y.insert(s);
            }
        }
        assert(ans >= 0);
        cout << ans << '\n';
    }
}
/*
Bài này chú ý việc các string Y có thể trùng nhau
*/
