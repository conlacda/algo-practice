// https://cses.fi/problemset/result/2888625/  Game Routes - CSES
// Cho đồ thị vô hướng, có bao nhiêu cách đi từ 1->N 
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

class Graph{ // graph chung cho tất cả
public:
    // General part
    int V; // vertex num 0->V-1
    vector<vector<pair<int,int>>> G;
    vector<bool> visited;
    Graph(int V){
        this->V  = V +1;
        G.resize(this->V, {});
        visited.resize(this->V, false);
    }
    void addEdge(int u, int v, int w = -1){
        G.at(u).push_back({v, w});
    }
    /*
    bài này đơn giản dùng toposort do không có cycle + không trọng số.
    Duyệt từ đầu tới cuối. Cho ways[1] = 1
    if (hasEdge(u->v)) ways[v] += ways[u]
    ways[1] = 1. 1->2 1->3 -> ways[2] = ways[3] = 1
    2->3 -> ways[3] += ways[2] => 2. 
    */
    // Topo sort
    // Verification: https://cses.fi/problemset/result/2886656/ Longest Flight Route- CSES
    vector<int> topo;
    void topo_explore(int start){
        if (!visited[start]) {
            visited[start] = true;
            for (auto p: G[start]){
                int v = p.first;
                if (!visited[v]) topo_explore(v);
            }
            topo.push_back(start);
        }
    }
    void toposort(int start){
        topo_explore(start);
        reverse(topo.begin(), topo.end());
    }

    void solve(){
        vector<ll> ways(V, 0);
        ways[1] = 1;
        for (auto t: topo){
            // u = t
            for (auto p: G[t]){
                int v = p.first;
                ways[v] += ways[t];
                ways[v] = ways[v] % mod;
            }
        }
        cout << ways[V-1];
    }
};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, M;
    cin >> N >> M;
    Graph g(N);
    for (int i=0;i<M;i++){
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }
    g.toposort(1);
    g.solve();
}
