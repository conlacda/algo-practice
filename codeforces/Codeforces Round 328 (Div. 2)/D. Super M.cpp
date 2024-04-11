// https://codeforces.com/contest/592/problem/D
#include<bits/stdc++.h>

typedef long long ll; // double long double
#define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

// diameter of tree
int dep1, dep2; // diameter end point
int diameter(const vector<vector<int>>&tree, int root = 0) {
    int n = tree.size();
    // Dùng BFS() dể duyệt rồi lấy ra điểm xa nhất
    vector<int> layer(n, -1);
    std::function<int(int)> furthestNode = [&](int u) {
        layer.assign(n, -1);
        queue<int> Q;
        layer[u] = 0;
        Q.push(u);
        while (!Q.empty()) {
            auto u = Q.front();
            Q.pop();
            for (auto&v: tree[u]) {
                if (layer[v] != -1) continue;
                Q.push(v);
                layer[v] = layer[u] + 1;
            }
        }
        return max_element(layer.begin(), layer.end()) - layer.begin();
    };
    dep1 = furthestNode(root);
    dep2 = furthestNode(dep1);
    return *max_element(layer.begin(), layer.end());
}
vector<vector<int>> getSubtree(const vector<vector<int>>& adj, vector<int> keptNodes) {
    if ((int) keptNodes.size() == 0) return {};
    // chạy dfs() từ 1 node được giữ lại
    int n = adj.size();
    vector<bool> keep(n, false);
    for (auto v: keptNodes) keep[v] = true;
    int root = keptNodes[0];
    dbg(root);
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            if (keep[v]) keep[u] = true;
        }
    };
    dfs(root, -1);
    vector<vector<int>> subtree(keep.size());
    for (int i=0;i<n;i++) {
        for (auto&v: adj[i]) {
            if (i < v && keep[i] && keep[v]) {
                subtree[i].push_back(v);
                subtree[v].push_back(i);
            }
        }
    }
    return subtree;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    /*
    Trên tree cho 1 loạt các node bị tấn công
    Từ 1 node bất kỳ trên cây đi tới toàn bộ các node bị tấn công
    thì cost tối thiểu là bao nhiêu.
    => rerooting
    * Pick 1 node trên cây rồi tính cost
    * Move node đó dần qua các node khác rồi tính cost cho các node đó
    */
    vector<int> attacked;
    for (int i=0;i<m;i++) {
        int v;
        cin >> v; v--;
        attacked.push_back(v);
    }
    sort(attacked.begin(), attacked.end());
    /*
    Bài này phần khoảng cách duyệt từ 1 node root -> 1 subtree có 3 node
     */
    dbg(attacked);
    auto subtree = getSubtree(adj, attacked);
    dbg(subtree);
    int node_num = 0;
    for (auto v: subtree)
        if ((int) v.size() > 0) node_num++;

    int diameterOfSubtree = diameter(subtree, attacked[0]);
    dbg(dep1, dep2);
    cout << min(dep1, dep2) + 1 << '\n';
    cout << max((node_num - 1) * 2 - diameterOfSubtree, (int) 0);
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này có thể giải bằng rerooting nhưng tại đây không cần
Yêu cầu bài toán: chọn 1 điểm trên tree và đi qua toàn bộ các điểm đó với quãng
đường ngắn nhất -> điểm bắt đầu và độ dài đường đi là bao nhiêu
Dễ dàng nhận thấy:
* điểm bắt đầu nên là 1 trong các điểm cần đi qua
    * Nếu điểm bắt đầu là điểm ko cần đi qua thì nếu nó nằm trên optimal path thì kết quả như nhau
    * Nếu nằm ngoài optimal path thì lại mất 1 đoạn để đi vào path
* đi từ 1 điểm qua toàn bộ các điểm cần tới nhưng không quay về
    * Xét đoạn đi qua mọi điểm. Lấy được chỉ subtree cần thiết. Ví dụ 1->2->3->4
    với 1,3 cần thiết thì ta có thể loại bỏ 4 khỏi tree
    Dùng dfs() post order với 3 là điểm cần thiết ta có thể đánh dấu 2 là điểm cần thiết
    * Sau khi có được subtree rồi thì ta thấy bắt đầu từ 1 điểm u đi 1 vòng chu trình quay về
    thì sẽ mất cost = (node_num - 1) * 2. Why??
    Xét u->v->X. Với u tới v và X là subtree của v. Khi này cost = 2 + cost(X)
    vì đi từ u->v rồi quay từ v->u. Bất kể X là gì thì tương tự ta cũng mất 2 * node_num trong X
    Thế thì điểm bắt đầu ko quan trọng -> chỉ cần đi rồi quay về thì độ dài luôn như nhau
    * Bài toán yêu cầu đi qua nk ko cần quay lại -> cost = cost_go_then_back - diameter
    vì diameter là độ dài dài nhất giữa 2 node trong tree. Nếu pick 2 điểm chân diameter
    làm điểm bắt đầu và kết thúc thì tiết kiệm được đoạn quay về dài nhất.

=> Lời giải có 3 phần:
* Lấy subtree của tree ban đầu
* Lấy diameter của subtree
* ans = (node_num-1) * 2 - diameter
*/
