// https://atcoder.jp/contests/abc369/tasks/abc369_e
// [Atcoder|Codeforces].abcxxx.F
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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
#endif

struct Node {
    int id; ll dist;
    friend bool operator<(const Node &a, const Node &b){
        return a.dist > b.dist;
    }
};
vector<ll> dijkstra(vector<vector<pair<int, ll>>>& adj, int root = 0) {
    int n = (int) adj.size();
    priority_queue<Node> Q;
    vector<ll> dist(n, INF); // LLONG_MAX
    dist[root] = 0;
    
    // Thêm các neighbor của root vào queue
    for (auto uw: adj[root]) {
        int u = uw.first; ll root_to_u = uw.second;
        // Có dòng này bởi vì có thể có nhiều cạnh từ u->v
        if (dist[u] > root_to_u) dist[u] = root_to_u;
        Q.push({u, dist[u]});
    }

    // Mở rộng dần từ các điểm đã có ra
    while (!Q.empty()) {
        ll d = Q.top().dist;
        int u = Q.top().id;
        Q.pop();
        if (d > dist[u]) continue;
        for (auto vw: adj[u]) {
            ll w = vw.second; int v = vw.first;
            if (d + w < dist[v]) {
                dist[v] = d + w;
                Q.push({v, dist[v]});
            }
        }
    }
    // Nếu !hasEdge(start, i) thì dist[i] = -1
    for (int i=0;i< n;i++)
        if (dist[i] == INF) dist[i] =-1;
    return dist;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n);
    vector<vector<int>> bridges;
    map<pair<int,int>, int> min_bridge;
    for (int i=0;i<m;i++) {
        int a, b, w;
        cin >> a >> b >> w;
        a--;b--;
        if (a > b) swap(a, b);
        bridges.push_back({a, b, w});
        if (min_bridge.find({a, b}) == min_bridge.end()) {
            min_bridge[{a, b}] = w;       
            g[a].push_back({b, 0});
            g[b].push_back({a, 0});     
        } else {
            min_bridge[{a, b}] = min(min_bridge[{a, b}], w);
        }
    }
    for (int i=0;i<n;i++) {
        for (auto& vw: g[i]) {
            vw.second = min_bridge[{min(vw.first, i), max(vw.first, i)}];
        }
    }
    dbg(g);
    int q;
    cin >> q;
    vector<vector<int>> D(n);
    for (int i=0;i<n;i++) {
        D[i] = dijkstra(g, i);
    }
    while (q--) { 
        int k;
        cin >> k;
        vector<int> bi(k);
        for (auto&v: bi) {
            cin >> v;
            v--;
        }
        /*
        Nối các cây cầu lại thì có được 1 đồ thị mới
        K chỉ có 5 rất nhỏ
        lần lượt chọn cây cầu tiếp theo để đi -> 5! = 120 cách chọn
        Bắt đầu từ điểm số 1 -> chọn điểm tới tiếp theo là 1 trong 2 đầu cây cầu
        rồi đi qua cầu.
        Để tìm đường đi ngắn nhất từ 1 điểm tới 1 điểm khác thì tại đây dùng dijkstra
        dijkstra bắt đầu từ mọi đỉnh sẽ được tính trước -> D. D[root] sẽ là dijstra(g, root)
        */
        int cost = INF/2;
        sort(bi.begin(), bi.end()); // sort trước khi dùng, vì nó dùng giá trị hiện tại để tính giá trị tiếp theo
        std::function<int(vector<int>, int)> move = [&](vector<int> bi, int mask) {
            int cur = 0;
            int res = 0;
            for (int i=0;i<(int) bi.size();i++) {
                int u = bridges[bi[i]][0];
                int v = bridges[bi[i]][1];
                int w = bridges[bi[i]][2];
                int target = u;
                if (mask & (1<< i)) target = v;
                res += D[cur][target];
                res += w;
                cur = (target == u) ? v: u;
            }
            res += D[cur][n-1];
            return res;
        };
        do {
            for (int mask=0;mask<(1<<k);mask++) {
                cost = min(cost, move(bi, mask));
            }            
        } while (std::next_permutation(bi.begin(), bi.end()));
        cout << cost << '\n';
    }

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
