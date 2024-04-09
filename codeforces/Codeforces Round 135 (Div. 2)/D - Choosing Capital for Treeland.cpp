// https://codeforces.com/contest/219/problem/D
// Rerooting technique - 1k7
#include<bits/stdc++.h>

#define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    map<pair<int,int>, int> edges;
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
        edges[{u, v}] = 1;
    }
    // calculate subtree
    vector<int> subtree(n, 0);
    std::function<int(int, int)> cal = [&](int u, int p) {
        int st = 0;
        for (auto v: adj[u]) {
            if (v == p) continue;
            if (edges[{u, v}] == 0) {
                // nếu không có cạnh từ u->v mà có cạnh v->u thì phải đảo ngược
                st++;
            }
            st += cal(v, u);
        }
        subtree[u] = st;
        return subtree[u];
    };
    cal(0, -1);
    // reroot
    vector<int> ans(n);
    ans[0] = subtree[0];
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            if (v == p) continue;
            ans[v] = ans[u];
            if (edges[{u, v}] == 1) ans[v]++;
            else ans[v]--;
            dfs(v, u);
        }
    };
    dfs(0, -1);
    // answer
    dbg(ans);
    int mincost = *min_element(ans.begin(), ans.end());
    cout << mincost << '\n';
    for (int i=0;i<n;i++) {
        if (ans[i] == mincost) cout << i + 1 << ' ';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
/*
Bài này nếu suy nghĩ bình thường thì thấy hơi khó nghĩ.
Nhưng nếu xác định theo hướng rerooting thì sẽ dễ hơn nhiều.
Khi này tính subtree cho điểm root. - cost để root làm thủ đô.
Đơn giản chỉ dfs() từ root qua các node con, node con nào ngược hướng thì mất
cost là 1.
Từ root tính cho các node khác. Xét X1<-u->v->X2 với u hiện tại là root, v là
neighbor và X là phần đồ thị còn lại nối với u, v
Ta thấy nếu v là root thì đồ thị chỉ thay đổi việc u->v và v->u.
cost[u] +- 1 sẽ ra cost[v] từ vào việc có cạnh u->v hay v->u
*/
