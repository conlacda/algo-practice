// https://timus.online/problem.aspx?space=1&num=1752
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

<hld>
<dijkstra>

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v; u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto d0 = dijkstra(adj);
    int f1 = std::distance(d0.begin(),std::max_element(d0.begin(), d0.end()));
    auto d1 = dijkstra(adj, f1);
    int f2 = std::distance(d1.begin(),std::max_element(d1.begin(), d1.end()));
    auto d2 = dijkstra(adj, f2);
    dbg(f1, f2);
    HeavyLightDecomposition<int> hld(adj);
    vector<int> weight(n, 1);
    hld.buildSegTree(weight);
    for (int i=0;i<q;i++) {
        int u, d;
        cin >> u >> d;
        u--;
        int f = f1, distf = d1[u];
        if (distf < d2[u]) {
            f = f2;
            distf = d2[u];
        }
        if (distf < d) {
            cout << 0 <<'\n';
            continue;
        }
        int lca = hld.lca.lca(u, f);
        int ulca = hld.query_any(u, lca);
        if (ulca >= d) {
            cout << hld.kth_ancestor(u, d) +1<< '\n';
        } else {
            cout << hld.kth_ancestor(f, hld.query_any(u, f) - d) +1<< '\n';
        }
    }

    show_exec_time();
}
/*
Bài này cạnh đều là 1 chứ ko có trọng số,
Lấy f1, f2 là đường kinh của đồ thị.
Với 1 đỉnh u và khoảng cách d. Lấy đỉnh f là 1 trong 2 đỉnh f1, f2
Vì f1, f2 là 2 điểm của đường kính (như đường tròn) nên f (là f1 hoặc f2) là
điểm xa u nhất.
nếu khoảng cách u->f mà nhỏ hơn d tức là ko có điểm thỏa mãn.
Ngược lại.
lca là lca(u, f). điểm cần tìm nằm trên u->lca hoặc f->lca
Nếu nằm trên u->lca điểm cần tìm là kth_ancestor của u với k = d.
Nếu điểm cần tìm vượt quá lca thì nó sẽ là kth_ancestor của f với k = uf - d
*/
