// https://timus.online/problem.aspx?space=1&num=1208
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Node {
    int id; ll dist;
    friend bool operator<(const Node &a, const Node &b){
        return a.dist > b.dist;
    }
};
vector<ll> dijkstra(vector<vector<pair<int, ll>>> adj, int root = 0){
    int n = (int) adj.size();
    vector<bool> visited(n, false);
    priority_queue<Node> Q;
    vector<ll> dist(n, LLONG_MAX);
    dist[root] = 0; visited[root] = true;

    for (int i=0;i< (int) adj[root].size();i++){
        int u = adj[root][i].first; ll start_to_u = adj[root][i].second;
        if (dist[u] > start_to_u)
            dist[u] = start_to_u;
        visited[u] = true;
        Q.push({u, dist[u]});
    }

    while (!Q.empty()){
        ll d = Q.top().dist;
        int u = Q.top().id;
        Q.pop();
        if (d > dist[u]) continue;
        for (int i=0;i< (int) adj[u].size();i++){
            ll w = adj[u][i].second; int v = adj[u][i].first;
            if (d+ w < dist[v]){
                dist[v] = d + w;
                Q.push({v, dist[v]});
            }
        }
    }
    for (int i=0;i< n;i++) if (dist[i] == INF) dist[i] =-1;
    return dist;
}
vector<ll> dijkstra(vector<vector<int>> adj, int root = 0){
    int n = (int) adj.size();
    const int defaultw = 1;
    vector<vector<pair<int, ll>>> ans(n);
    for (int i=0;i<n;i++) {
        for (auto v: adj[i]) {
            ans[i].push_back({v, defaultw});
        }
    }
    return dijkstra(ans, root);
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    // Luu lai 1 nguoi o nhung team nao
    // Tu team cua tung nguoi, ket noi tao ra do thi vo huong
    // Dung dijkstra dung khoang cach cac node
    // mang distance[i][j] se la khoang cach tu i->j. distance[i][j] == 1 -> 2 team co chung nguoi, == 0 -> i == j, > 1 nghia la ko co chung nhau nguoi nao ca
    // Dau vao la 1 day cac team duoc chon, duyet 18*18 xem co 2 team nao trung nhau khong
    // isGood(teams[]) - kiem tra xem danh sach team da chon nay thi co thoa man khong.
    // TLE: do thoi gian gioi han 0.5s nen ban dau dung map/set de check teams[] co trung ai khong mat ~0.9s
    // TLE: unordered_set<string> s; for (member in teams) s.insert(member); if (s.size() = teams.size() *3) return 'ok'; so luong team * 3 = so luong nguoi nghia la ko co ai trung nhau trong cac team do

    unordered_map<string, std::vector<int>> teams; // who to which team?
    for (int i=0;i<n;i++) {
        string s1, s2, s3;
        cin >> s1 >> s2 >> s3;
        teams[s1].push_back(i);
        teams[s2].push_back(i);
        teams[s3].push_back(i);
    }
    vector<vector<int>> adj(n);
    for (auto v: teams) {
        auto team = v.second;
        auto person = v.first;
        for (int i=0;i<team.size();i++) {
            for (int j=0;j<team.size();j++) {
                if (i != j) adj[team[i]].push_back(team[j]);
            }
        }
    }
    for (int i=0;i<n;i++) {
        set<int> s( adj[i].begin(), adj[i].end());
        adj[i].assign( s.begin(), s.end());
    }
    vector<vector<int>> distance(n, vector<int>(n));
    for (int i=0;i<n;i++) {
        distance[i] = dijkstra(adj, i);
    }

    int ans = 0;
    std::function<bool(vector<int>)> isGood = [&](vector<int> steams){
        for (int i=0;i<(int)steams.size()-1;i++) {
            for (int j=i+1;j<(int)steams.size();j++) {
                if (distance.at(steams[i]).at(steams[j]) == 1) return false;
            }
        }
        return true;
    };
    for (int i=0;i<1<<n;i++){
        vector<int> selected_teams;
        for (int j=0;j<n;j++){
            if (i&(1<<j)) {
                selected_teams.push_back(j);
            }
        }
        if (isGood(selected_teams)) {
            ans = max(ans, (int) selected_teams.size());
        }
    }
    cout << ans;
    show_exec_time();
}
