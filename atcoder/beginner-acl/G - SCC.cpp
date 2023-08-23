#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif


// Full doc: https://github.com/conlacda/docc/blob/dev/docs/competitive-programming/graph/basic/toposort.md
vector<vector<int>> findSCC(vector<vector<int>> G){
    // Tạo ra reversed graph
    std::function<vector<vector<int>>(vector<vector<int>>)> getReversedGraph = [&](vector<vector<int>> G){
        vector<vector<int>> rG((int) G.size());
        for (int i=0;i<G.size();i++){
            for (auto v: G[i]){
                rG[v].push_back(i);
            }
        }
        return rG;
    };
    // Topo order
    std::function<vector<int>(vector<vector<int>>)> toposort = [&](vector<vector<int>>G){
        vector<bool> vis(G.size(), false);
        vector<int> order;
        std::function<void(int)> dfs = [&](int u){
            if (!vis[u]) {
                vis[u] = true;
                for (auto v: G[u]){
                    if (!vis[v]) dfs(v);
                }
                order.push_back(u);
            }
        };
        for (int i=0;i<(int) G.size();i++) {
            dfs(i);
        }

        reverse(order.begin(), order.end());
        return order;
    };

    vector<int> post_orders_reversed_graph = toposort(getReversedGraph(G)); // topo sort on reversed graph
    vector<vector<int>> result;
    std::vector<bool> vis((int) G.size(), false);
    vector<int> scc;
    std::function<void(int)> dfs = [&](int u){
        vis[u] = true;
        for (auto v: G[u]){
            if (!vis[v]){
                dfs(v);
            }
        }
        scc.push_back(u);
    };
    for (auto i: post_orders_reversed_graph){
        if (!vis[i]) dfs(i);
        if (scc.size() > 0){
            result.push_back(scc);
            scc = {};
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n>> m;
    vector<vector<int>> adj(n);
    for (int i=0;i<m;i++){
        int u, v;
        cin >> u>>v;
        adj[u].push_back(v);
    }
    dbg(adj);
    vector<vector<int>> sccs = findSCC(adj);
    cout << sccs.size() <<'\n';
    for (auto scc: sccs){
        cout << scc.size()<< ' ';
        for (auto v: scc) cout << v<< ' ';
        cout << '\n';
    }
}
