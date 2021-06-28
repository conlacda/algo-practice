// Shortest path - graph no weight
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main()
{
    // freopen("inp.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int N,M;
    cin >> N>>M;
    vector<vector<int>> graph;
    vector<bool> visited;
    vector<int> parent;
    for (int i=0;i<=N;i++){
        vector<int> x={};
        graph.push_back(x);
        visited.push_back(false);
        parent.push_back(-1);
    }
    for (int i=0;i<M;i++){
        int a,b;
        cin >>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> Q= {1};
    visited[1] = true;
    while (Q.size()>0){
        int p = Q.front();
        Q.erase(Q.begin()+0);
        for (int i=0;i<graph[p].size();i++){
            if (!visited[graph[p][i]]){
                parent[graph[p][i]] = p;
                visited[graph[p][i]]= true;
                Q.push_back(graph[p][i]);
            }
        }
    }
    if (visited[N]){
        vector<int> path = {N};
        while (N!=1){
            path.push_back(parent[N]);
            N = parent[N];
        }
        cout << path.size() << '\n';
        for (int i=path.size()-1;i>=0;i--){
            cout << path[i] << ' ';
        }
    } else cout << "IMPOSSIBLE";
}
