/*
https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/containers-of-choclates-1/
Easy
Bài toán chỉ đơn thuần là bài toán đánh dấu màu sau đó đếm màu
*/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
int maxN = 20002;

using namespace std;
class DirectedGraph{
public:
    int V;
    vector<vector<int>> G;
    vector<bool> visited;
    DirectedGraph(int V){
        for (int i=0;i<=V;i++){
            G.push_back({});
            this->visited.push_back(false);
        }
        this->V = V;
    }
    void addEdge(int a, int b){
        G[a].push_back(b);
    }
    int ans=0;
    int white = 0, black = 0;
    void explore(int u, int color){
        if (!visited[u]){
            visited[u] = true;
            if (color == 0) white++;
            else black++;
            for (int i=0; i<G[u].size();i++){
                int sig = 1-color; // switch between 0 and 1
                if (!visited[G[u][i]]) {
                    explore(G[u][i], sig);
                }
            }
        }
    }
    void DFS(){
        for (int i=0;i<maxN;i++){
            if (!visited[i] && G[i].size() > 0) {
                explore(i, 0);
                // cout << "i="<< i<< " white=" << white << " black=" << black << '\n'; 
                ans += max(white, black);
            }
            // cout << white << ' ' << black << '\n';
            black = 0;
            white = 0;
        }
    }
};

void solve(int _i){
    cout << "Case "<< _i << ": ";
    int ans=0;
    int q;
    cin >> q;
    
    DirectedGraph g(maxN);
    while (q--){
        int u,v;
        cin >> u >> v;
        g.addEdge(u,v);
        g.addEdge(v,u);
    }
    g.DFS();
    cout << g.ans;
    cout <<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int t;
    cin >> t;
    for (int i=1;i<=t;i++){
        solve(i);
    }
}
/*
Duyệt DFS cho mọi đỉnh, đánh dấu đỉnh nào màu gì rồi tăng biến đếm lên 1

*/