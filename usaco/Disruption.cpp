#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
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

// depth_of_tree
vector<ll> depth_of_tree(vector<vector<ll>>&tree) {
    vector<ll> depth((ll) tree.size(), -1);
    depth[0] = 0;
    std::function<void(ll, ll)> dfs = [&](ll u, ll p){
        for (auto v: tree.at(u)) {
            if (v == p) continue;
            depth.at(v) = depth.at(u)+ 1;
            dfs(v, u);
        }
    };
    dfs(0, 0);
    return depth;
}

struct Node {
    int w, v;
    friend bool operator<(const Node &a, const Node &b){
        return a.w > b.w;
    }
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        freopen("disrupt.in", "r", stdin);
        freopen("disrupt.out", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edge_order;
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge_order.push_back({u, v});
    }
    auto depth = depth_of_tree(adj);
    vector<int> order;
    for (auto v: edge_order) {
        int deeper_node = (depth[v.first] > depth[v.second]) ? v.first: v.second;
        order.push_back(deeper_node);
    }
    vector<vector<Node>> a(n);
    for (int i=0;i<q;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        a[u].push_back({w, v});
        a[v].push_back({w, u});
    }
    makeEulerTour(adj);
    vector<int> ans(n, 0);
    std::function<priority_queue<Node>(int, int)> cal = [&](int u, int p){
        int _min = first[u];
        int _max = second[u];
        priority_queue<Node> res;
        for (auto wv: a[u])
            res.push(wv);
        for (auto v: adj[u]) {
            if (v == p) continue;
            auto calV = cal(v, u);
            if ((int) res.size() < (int) calV.size()) res.swap(calV);
            while (!calV.empty()) {
                res.push(calV.top());
                calV.pop();
            }
        }
        while (!res.empty()) {
            auto top = res.top();
            if (_min <= first[top.v] && second[top.v] <= _max) {
                res.pop();
            } else {
                ans[u] = top.w;
                break;
            }
        }
        if (res.empty()) ans[u] = -1;
        return res;
    };
    cal(0, -1);
    dbg(ans);
    for (auto node: order) {
        cout << ans[node] << '\n';
    }

    show_exec_time();
}
/*
Bài này sử dụng "Small to large merging" + eulertour (xác định v thuộc subtree u/con của u) + depth để dồn order + dồn cạnh xuống bên node dưới

khi mất đi 1 edge thì cạnh nhỏ nhất bù vào có trọng số là bao nhiêu 
=> thay đổi cách hỏi: edge u->v sử dụng technique vẫn hay dùng là dồn
trọng số xuống bên dưới. Khi này bản chất là subtree của node u có thể kết nối
ra bên ngoài với những cạnh nào. Sử dụng priorty_queue lấy ra phần tử đầu có
trọng số nhỏ nhất

Với mỗi node sẽ lưu trữ 1 priority_queue<Node>
chứa những node và trọng số mà nó có thể tới.
Key point tại đây là đừng vội xử lý priority_queue tại thời điểm merge, hay 
xử lý toàn bộ khi kết thúc duyệt node mà chỉ xử lý để lấy ra kết quả.
queue này chứa các node có thể tới.
Khi merge u->v thì bản chất là 2 queue cộng vào nhau.
u tới được k
v tới được x
=> u+v tới được k+x
Khi lấy kết quả, ta sẽ lấy ra những node k tới được mà nằm ngoài khối.
Sau khi merge u+v vào rồi thì phải tìm ra đỉnh nào mà khối này kết nối tới và
có trọng số nhỏ nhất.
Đỉnh sẽ được gói vào Node {w, vertex};
Lưu ý tại đây sẽ order theo w.
Sử dụng vertex xét first, second[vertex] sẽ biết được v có là con của u không (tính chất euler tour)
Nếu node này là con của u đang xét thì đẩy ra khỏi queue.
Nếu không thì lấy luôn ra kết quả. *** Tại đây lấy ra kết quả chứ ko đẩy toàn
bộ con của u ra khỏi queue. Đoạn này làm cho thao tác xóa khỏi queue chỉ là N thao tác
*/
