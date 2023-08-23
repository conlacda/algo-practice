// https://atcoder.jp/contests/abc305/tasks/abc305_e
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
// #define int long long
// const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Node {
    int num, health;
    friend bool operator<(const Node &a, const Node &b){
        return a.health < b.health;
    }
    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Dùng small to large technique??
    Duyệt cái có độ phủ lớn nhất, di chuyển nó tới các node bên cạnh, độ phủ nhỏ đi 1.
    Khi chọn cái to nhất thì chắc chắn sẽ ko có việc 1 node khác di chuyển và có độ phủ to hơn độ phủ hiện tại -> ko cần xét lại - tương tự như Dijkstra
    Dùng 1 cái priority queue để nó tự động sắp xếp
    */
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n);
    for (int i=0;i<m;i++) {
        int u, v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    priority_queue<Node> Q;
    for (int i=0;i<k;i++) {
        int u, v;
        cin >> u >> v;
        u--;
        Q.push(Node{u, v});
    }
    // Large to small
    vector<bool> vis(n, false);
    vector<int> ans;
    while (!Q.empty()) {
        auto f = Q.top();
        Q.pop();
        if (vis[f.num]) continue;
        vis[f.num] = true;
        ans.push_back(f.num);
        for (auto neighbor: g[f.num]) {
            if (!vis[neighbor]) {
                if (f.health >= 1) {
                    Q.push(Node{neighbor, f.health -1});
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() <<'\n';
    for (auto v: ans) cout << v+1 << ' ';
    show_exec_time();
}
/*
Bài này có technique tương tự dijkstra
Với dijkstra ta lấy cạnh nhỏ nhất trong các cạnh đang xét và mở rộng node.
Cạnh nhỏ nhất đó đi tới node k. Node k ko có đường nào ngắn hết từ root tới đó mà ko thông qua cạnh nhỏ nhất đang xét
Tại bài này, thì ta lấy node có health lớn nhất, rồi lan đi. 
Node lớn nhất đó lan ra các node bên cạnh, nếu các node bên cạnh có trọng số thì 
trọng số lớn hơn sẽ được giữ lại. Node lớn nhất đó sẽ ko thể có 1 node khác lan tới mà trọng số lớn hơn được nữa.
Ví dụ: 1 có trọng số 3, 2 có trọng số 1. 1 lan ra 2 thì 2 có trọng số là 2 (2 > 1 ban đầu)
Mọi node khác đều có trọng số < node 1 nên khi lan tới 1 chắc chắn sẽ càng nhỏ hơn 1 và 1 ko cần đc xét lại.
Tương tự mỗi node sẽ được xét 1 lần và lan ra các node xung quanh.

*/
