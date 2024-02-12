// https://cses.fi/problemset/task/1711
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
 
class Dinic_Maxflow{
private:
    int n, len; // n: tổng số node, len cho đồ thị bipartite - độ dài 1 bên left/right
public:
    vector<vector<int>> graph, residualGraph;
    Dinic_Maxflow(vector<vector<int>>& graph){
        this->graph = graph;
        this->n = graph.size();
        this->len = (this->n-2)/2;
    }

    int max_flow(int source, int sink) {
        vector<int> cnt(n, 0), level(n, -1);
        std::function<bool(int, int)> bfs = [&](int source, int sink){ // on residualGraph
            fill(level.begin(), level.end(), -1); level[source] = 0;
            queue<int> Q; Q.push(source);
            while (!Q.empty()) {
                int u = Q.front(); Q.pop();
                for (int v = 0; v < n; v++) {
                    if (u != v && residualGraph[u][v] > 0 && level[v] < 0) {
                        // Level of current vertex is level of parent + 1
                        level[v] = level[u] + 1; Q.push(v);
                    }
                }
            }
            // if we can not reach to the sink we return false else true
            return level[sink] >= 0;
        };
        std::function<int(int, int, int)> sendFlow = [&](int u, int sink, int flow){ // on residualGraph
            if (u == sink) return flow; // Sink reached
            if (cnt[u] >= (int) residualGraph[u].size()) return (int) 0;         
            // Traverse aint adjacent edges one-by-one.
            for (int v=0; v < n; v++) {
                if (residualGraph[u][v] > 0) {
                    cnt[u]++;
                    if (level[v] == level[u]+1) {
                        // find minimum flow from u to sink
                        int curr_flow = min(flow, residualGraph[u][v]);
                        int min_cap = sendFlow(v, sink, curr_flow);
                        if (min_cap > 0){
                            residualGraph[u][v] -= min_cap;
                            residualGraph[v][u] += min_cap;
                            return min_cap;
                        }
                    }
                }
            }
            return (int) 0;
        };
        
        if (source == sink) return -1;
        int max_flow = 0;
        residualGraph = graph;
        // Augment the flow while there is path from source to sink
        while (bfs(source, sink) == true) {
            // store how many neighbors are visited
            fill(cnt.begin(), cnt.end(), 0);
            // while flow is not zero in graph from source to sink
            while (int flow = sendFlow(source, sink, INF)) max_flow += flow;
        }
        return max_flow;
    }

    vector<pair<int, int>> normal_mincut(int source, int sink) {
        this->max_flow(source, sink);
        vector<pair<int, int>> mincut_edges;
        vector<bool> vis(this->n, false);
        queue<int> Q;
        Q.push(source); vis[source] = true;
        while (!Q.empty()){
            int p = Q.front(); Q.pop();
            for (int v=0; v<n;v++){
                if (residualGraph[p][v] > 0 && !vis[v]){
                    Q.push(v); vis[v] = true;
                }
            }
        }
        for (int i = 0;i<n;i++){
            for (int j =0;j<n;j++){
                if (graph[i][j] > 0 && vis[i] && !vis[j]){
                    mincut_edges.push_back({i, j});
                }
            }
        }
        return mincut_edges;
    }
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, q;
    cin >> n >> q;
    vector<vector<ll>> graph(n, vector<ll>(n, 0));
    for (int i=0;i<q;i++){
        ll u, v; cin >> u>> v;
        u--; v--;
        graph[u][v] =1;
    }
    Dinic_Maxflow dinic(graph);
    int max_flow = dinic.max_flow(0, n-1);
    cout << max_flow << '\n';
    /*
    In ra toàn bộ augument path là xong
    Distinct route bản chất chính là các augument path
    Augument path sẽ là tập hợp 1 loạt các cạnh [u, v] mà graph[u][v] = 1 còn residualGraph[u][v] = 0
    Đơn giản chỉ cần dfs(root) max_flow lần để lấy ra max_flow số augument path là xong
    dfs(u) duyệt tới v khi graph[u][v] = 1 còn residualGraph[u][v] = 0
    sau khi từ u->v thì đặt residualGraph[u][v] = 1 để lần sau ko duyệt lại nữa.
    khi v = n-1 thì in ra augument path
    */
    vector<int> agument_path;
    std::function<void(int)> dfs = [&](int u) {
        agument_path.push_back(u+1);
        if (u == n-1) {
            return;
        }
        for (int i=0;i<n;i++) {
            if (u == i) continue;
            if (graph[u][i] == 1 && dinic.residualGraph[u][i] == 0) {
                dinic.residualGraph[u][i] = 1;
                dfs(i);
                break;
            }
        }
    };
    while (max_flow--) {
        agument_path.clear();
        dfs(0);
        cout << agument_path.size() << '\n';
        for (auto v: agument_path) {
            cout << v << ' ';
        }
        cout << '\n';
    }
    show_exec_time();
}
