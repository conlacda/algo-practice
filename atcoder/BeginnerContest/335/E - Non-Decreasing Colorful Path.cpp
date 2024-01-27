// https://atcoder.jp/contests/abc335/tasks/abc335_e
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

struct Node {
    int id; ll w;
    friend bool operator<(const Node &a, const Node &b){
        return a.w > b.w;
    }
    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for (auto&v : w) cin >> v;
    vector<vector<int>> adj(n);
    /*
    Distinct -> dùng dijkstra mở rộng node, chưa có giá trị thì mở rộng
    */
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    priority_queue<Node> Q;
    Q.push(Node{0, w[0]});
    vector<int> ans(n, 0);
    ans[0] = 1;
    while (!Q.empty()) {
        dbg(Q);
        Node node = Q.top();
        Q.pop();
        for (auto u: adj[node.id]) {
            if (w[u] == w[node.id] && ans[u] < ans[node.id]) {
                ans[u] = ans[node.id];
                Q.push(Node{u, w[u]});
            }
            if (w[u] > w[node.id]) {
                if (ans[u] < ans[node.id] + 1) {
                    ans[u] = ans[node.id] + 1;
                    Q.push(Node{u, w[u]});
                }
            }
        }
    }
    cout << ans[n-1];
    show_exec_time();
}
