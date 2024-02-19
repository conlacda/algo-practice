// https://atcoder.jp/contests/abc341/tasks/abc341_f
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

vector<int> toposort(vector<vector<int>>& adj) {
    vector<bool> vis(adj.size(), false);
    vector<int> order;
    std::function<void(int)> dfs = [&](int u) {
        if (vis[u]) return;
        
        vis[u] = true;
        for (auto v: adj[u]) dfs(v);
        order.push_back(u);
    };
    for (int i=0;i<(int) adj.size();i++)
        dfs(i);

    // dfs(0); - 1 số bài chỉ cần toposort cho connected component chứa root = 0 mà thôi.
    reverse(order.begin(), order.end());
    return order;
}

set<int> knapsack(vector<int>& cost, vector<int>& value, int maxCost) {
    set<int> items;
    int n = cost.size();
    vector<vector<int>> maxValue(n+1, vector<int>(maxCost+1, 0)); // ban đầu không chọn gì tất cả đều bằng 0 - initial state
    // maxValue[item_ith][cost] trong i vật phẩm đầu tiên, với cost thì lấy được tối đa bn value
    for (int i=1;i<=n;i++){
        for (int j=0;j<=maxCost;j++){
            // Lấy cái này hoặc ko lấy cái này
            maxValue[i][j] = maxValue[i-1][j];
            if (j - cost[i-1] >= 0) {
                maxValue[i][j] = max(maxValue[i-1][j], maxValue[i-1][j- cost[i-1]] + value[i-1]);
            }
        }
    }
    // reconstruct
    int curCost = maxCost;
    for (int i=n-1;i>=0;i--) {
        if (curCost >= cost[i] && maxValue[i+1][curCost] == maxValue[i][curCost - cost[i]] + value[i]) {
            items.insert(i);
            curCost -= cost[i];
        }
    }
    return items;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> w(n), p(n);
    for (auto&v: w) cin >> v;
    for (auto&v: p) cin >> v;
    // Lấy ra graph chỉ có chiều đi từ to tới bé
    vector<vector<int>> adj(n);
    for (int i=0;i<n;i++) {
        for (auto v: g[i]) {
            if (w[i] > w[v]) adj[i].push_back(v);
        }
    }
    // Tính số lượng hạt tối đa có thể truyền đi của từng node từ dưới lên root
    vector<int> cnt(n, 1); // cnt[i] thể hiện 1 point node i truyền được đi bao nhiêu
    vector<vector<int>> deliverable(n);
    std::function<void(int)> cal = [&](int u) {
        if ((int) adj[u].size() == 0) {
            return;
        }
        // sử dụng knapsack để tính ra được những node nào cần delivery
        // set<int> knapsack(vector<int>& cost, vector<int>& value, int maxCost)
        vector<int> neighbor, cost, value;
        for (auto v: adj[u]) {
            neighbor.push_back(v);
            cost.push_back(w[v]);
            value.push_back(cnt[v]);
        }
        // danh sách các node con của u được chọn để tối đa số lần delivery
        auto nodeIndexes = knapsack(cost, value, w[u] - 1);
        for (auto id: nodeIndexes) {
            deliverable[u].push_back(neighbor[id]);
            cnt[u] += cnt[neighbor[id]];
        }
    };

    // Lấy toposort của adj để biết thứ tự delivery
    auto topo = toposort(adj);
    reverse(topo.begin(), topo.end());
    for (auto node: topo) {
        // mỗi node sẽ chuyển hạt về các node con của nó sao cho
        // sumW < w[node] và các node con có thể chuyển hạt đi nhiều nhất có thể
        cal(node);
    }
    dbg(deliverable, cnt);
    int ans = 0;
    reverse(topo.begin(), topo.end());
    for (auto node: topo) {
        ans += p[node];
        for (auto child: deliverable[node]) {
            p[child] += p[node];
        }
        p[node] = 0;
    }
    cout << ans;
    dbg(ans);
    show_exec_time();
}
/*
Tóm tắt lời giải:
Tại đây mỗi node có 1 w và có thể truyền đi cho các node con với sum w < w node
khi truyền từ node 1 -> các node con thì các node con có thể truyền tiếp cho các node cháu
=> cần phải chọn các node con sao cho có thể truyền đi nhiều nhất có thể.
=> cần tính được 1 node có 1 point thì sẽ truyền đi được tối đa bao nhiêu lần.
Ta thấy node có W lớn truyền tới W nhỏ -> chỉ cần giữ lại đồ thị với cạnh (u, v) với w[u] > w[v]
Dựng toposort. Từ node có depend thấp nhất tính được lượng point có thể truyền đi tại node đó.
node ko có child thì cnt[] = 1.
node khác thì có cnt = tổng cnt của children và thêm chính nó là 1
khi này 1 node ta có 2 thông tin: weight (có từ ban đầu) + cnt là số lần có thể delivery từ nó (số operation)
=> duyệt lần lượt theo toposort
Với node X ta phải chọn 1 tập các node có sum w < w[X] và max cnt
=> đó chính là bài toán knapsack 
Ta có
* w[X] là maxCost
* w[node] là cost của các item cần chọn
* cnt[node] là value tương ứng của item
=> lấy ra các item để sum value max và sum cost nằm trong maxCost
Sau khi chọn được các node cần delivery thì point node hiện tại về 0 còn point của mỗi node con tăng lên lượng point của node đó
Lần lượt từng node theo thứ tự topo là xong
*/
