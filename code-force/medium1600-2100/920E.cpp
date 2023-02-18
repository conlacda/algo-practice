// https://codeforces.com/contest/920/problem/E
// E. Connected Components? - Educational Codeforces Round 37 (Rated for Div. 2)
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


int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    vector<set<int>> g(n);
    for (int i=0;i<m;i++){
        int u, v; cin >> u >> v; u--; v--;
        g[u].insert(v);
        g[v].insert(u);
    }
    dbg(g);
    // Duyệt DFS() nhưng mảng visited thay vì để là vector thì chuyển thành set cho phần tìm kiếm từ N -> O(logN)
    set<int> vis;
    for (int i=0;i<n;i++) vis.insert(i);
    auto it = vis.begin();
    int cur = 0;
    std::function<void(int)> dfs = [&](int u){
        // Với đỉnh u, xét xem nó có thể kết nối với đỉnh nào chưa vis ko
        auto it = vis.begin();
        while (it != vis.end()){
            if (!g[u].count(*it)) {
                int val = *it;
                vis.erase(val);
                cur++;
                dfs(val);
                it = vis.upper_bound(val);
            } else it = next(it);
        }
    };
    /*
    DFS() ở đây có khác 1 chút.
    Tại đây với mỗi đỉnh u sẽ duyệt v trên vis để xem u-v có kết nối hay ko
    Nếu duyệt thông thường thì độ phức tạp là n^2
    Do đó tại đây mk chỉ duyệt những cạnh chưa vis chứ ko duyệt theo dạng
    for (auto v: vis) if (!v && !u->v) // v: vis mất O(N)
    -> cứ duyệt tới đâu thì xóa tại vis tới đó.
    Thế nhưng thao tác xóa trên vector là ko khuyến khích vì mất O(N).
    Nếu vis là vector thì suy cho cùng complexity vẫn là O(N^2)
    -> Dùng 1 datastructure khác cho thao tác xóa và duyệt được
    -> Set
    Tại DFS(u) -> mk duyệt tất cả các đỉnh trong vis và nếu !u->v (g[u].count(v) == 0)
    thì duyệt tới v. Đồng thời trước đó v được đánh dấu là visited nên cần xóa
    nó khỏi set. 
    Việc xóa 1 phần tử khỏi set sẽ ảnh hưởng tới việc duyệt nên mk dùng val = *it
    và lúc sau lấy upper_bound(val) là ra phần tử tiếp theo trong set chứ ko dùng next(it)
    vì sau khi xóa it ko còn tồn tại và next(it) sẽ sai lệch
    */
    vector<int> ans;
    for (int i=0;i<n;i++){
        dfs(i);
        if (cur != 0) ans.push_back(cur);
        cur = 0;
    }
    sort(ans.begin(), ans.end());
    cout << ans.size()<<'\n';
    for (auto v: ans) {
        cout << v << ' ';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}

/*
E. Connected Components?
time limit per test2 seconds
memory limit per test256 megabytes

You are given an undirected graph consisting of n vertices and (N(N-1)/2 -m) edges. Instead of giving you the edges that exist in the graph, we give you m unordered pairs (x, y) such that there is no edge between x and y, and if some pair of vertices is not listed in the input, then there is an edge between these vertices.

You have to find the number of connected components in the graph and the size of each component. A connected component is a set of vertices X such that for every two vertices from this set there exists at least one path in the graph connecting these vertices, but adding any other vertex to X violates this rule.

Input
The first line contains two integers n and m (1 ≤ n ≤ 200000, 0<=m<=min((N-1)*N/2,200000)).

Then m lines follow, each containing a pair of integers x and y (1 ≤ x, y ≤ n, x ≠ y) denoting that there is no edge between x and y. Each pair is listed at most once; (x, y) and (y, x) are considered the same (so they are never listed in the same test). If some pair of vertices is not listed in the input, then there exists an edge between those vertices.

Output
Firstly print k — the number of connected components in this graph.

Then print k integers — the sizes of components. You should output these integers in non-descending order.

Example
input
5 5
1 2
3 4
3 2
4 2
2 5
output
2
1 4 
*/