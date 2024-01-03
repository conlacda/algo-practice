#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Chuyen doi grid sang graph
vector<vector<int>> grid2Graph(vector<string>& grid, char node = '#') {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> adj(n*m+1);
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            if (grid[i][j] != node) continue;
            if (i+1 < n && grid[i+1][j] == node) {
                adj[i*m + j].push_back((i+1)*m + j); 
                adj[(i+1)*m + j].push_back(i*m + j); 
            }
            if (j+1 < m && grid[i][j+1] == node) {
                adj[i*m + j].push_back(i*m + j+1);
                adj[i*m + j+1].push_back(i*m + j);
            }
        }
    }
    return adj;
}

/*
Lấy ra các cutpoint của đồ thị vô hướng
*/
vector<int> findCutPoints(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> vis(n, false);
    vector<int> tin(n, -1), low(n, -1);
    int clock = 0;
    set<int> cutpoints;
    std::function<void(int, int)> dfs = [&](int v, int p = -1) {
        vis[v] = true;
        tin[v] = low[v] = clock++;
        int children=0;
        for (int to : adj[v]) {
            if (to == p) continue;
            if (vis[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] >= tin[v] && p!=-1)
                    cutpoints.insert(v);
                ++children;
            }
        }
        if (p == -1 && children > 1)
            cutpoints.insert(v);
    };
    for (int i=0;i<n;i++) {
        if (!vis[i]) dfs(i, -1);
    }
    return vector<int>(cutpoints.begin(), cutpoints.end());
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int row, col;
    cin >> row >> col;
    vector<string> grid(row);
    for (int i=0;i<row;i++) cin >> grid[i];
    vector<vector<int>> adj = grid2Graph(grid);
    auto cutpoints = findCutPoints(adj);
    int edge_num = 0;
    for (int i=0;i<row*col+1;i++) {
        edge_num += (int) adj[i].size();
    }
    edge_num /=2;
    if (edge_num <= 1){
        cout << -1;
    } else {
        if (cutpoints.size() == 0) {
            cout << 2;
        } else{
            if (cutpoints.size() >= 1){
                cout << 1;
            }
        }
    }
}
