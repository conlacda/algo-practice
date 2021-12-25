/*
Bài này đơn giản dùng thuật toán BellManFord
BellmanFord để tính đường đi ngắn nhất từ u->v.
bài này cần tính đường đi dài nhất thì sẽ đảo ngược giá trị các cạnh w -> -w
Khi này trở thành bài toán tìm đường đi ngắn nhất dùng nguyên BellmanFord
*/
#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

class WeightedDirectedGraph{
public:
    int V;
    vector<vector<pair<int,int>>> G;
    vector<bool> visited;
    WeightedDirectedGraph(int V){
        for (int i=0;i<=V;i++){
            G.push_back({});
            this->visited.push_back(false);
        }
        this->V = V;
    }
    void addEdge(int a, int b, ll w){
        G[a].push_back(make_pair(b,w));
    }

    void BellmanFord(int start){
        // BellmanFord - tương tự như Dijkstra nhưng dành cho đồ thị có cạnh âm
        vector<ll> dist(V+1, LLONG_MAX);
        dist[start] = 0;
        for (int _=0; _<=V;_++){
            for (int i=0;i<=V;i++){ // for vertex: verticies
                for (int j=0;j<G[i].size();j++){
                    int u = i, v = G[i][j].first; ll w = G[i][j].second;
                    if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                        // tại đây dist[u] != LLONG_MAX là để chắc chắn đỉnh start có chạm tới được u
                        // Khi có start->u thì mọi khoảng cách từ u đi mới đc
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }
        for (int _=0;_<=V;_++){
            for (int i=0;i<=V;i++){ // for vertex: verticies
                for (int j=0;j<G[i].size();j++){
                    int u = i, v = G[i][j].first; ll w = G[i][j].second;
                    if (dist[u] == -LLONG_MAX) dist[v] = -LLONG_MAX;
                    else if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                        dist[v] = -LLONG_MAX;
                        // dist[v] = dist[u] + w;
                    }
                }
            }
        }
        if (dist[V] == -LLONG_MAX) {
            cout << -1;
        } else cout << -dist[V];
    }
};
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, M;
    cin >> N >> M;
    WeightedDirectedGraph g(N);
    for(int i=0;i<M;i++){
        int u, v; ll w;
        cin >> u >> v>> w;
        g.addEdge(u, v, -w);
    }
    g.BellmanFord(1);

}
