// https://codeforces.com/problemset/problem/1833/E

#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

class DSU {
 public:
    vector<int> parent, size;
    int n;
    DSU(int _n) {
        n = _n;
        parent.resize(n);
        size.resize(n, 1);
        std::iota(parent.begin(), parent.end(), 0);   
    }

    int find(int v) {
        assert(0 <= v && v < n);
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
    bool isSame(int a, int b) {
        return find(a) == find(b);
    }
};

struct Node {
    int nodeNum = 1, connectionNum = 0;
    bool isFull() {
        return this->nodeNum * 2 == this->connectionNum;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    /*
    Tạo ra 1 đồ thị 2 chiều, a->b cũng có b->a
    Từ đây duyệt qua từng node để tính nodeNum và connection
    */
    vector<Node> nodes(n);
    vector<unordered_set<int>> adj(n);
    for (int i=0;i<n;i++) {
        cin >> a[i]; a[i]--;
        adj[i].insert(a[i]);
        adj[a[i]].insert(i);
    }
    DSU dsu(n);
    for (int u=0;u<n;u++) {
        for (auto v: adj[u]) {
            int ru = dsu.find(u);
            int rv = dsu.find(v);
            if (ru == rv) {
                nodes[ru] = Node{nodes[ru].nodeNum, nodes[ru].connectionNum + 1};
            } else {
                dsu.merge(ru, rv);
                int r = dsu.find(ru);
                nodes[r] = Node{nodes[ru].nodeNum + nodes[rv].nodeNum, nodes[ru].connectionNum + nodes[rv].connectionNum + 1};
            }
        }
    }
    unordered_set<int> roots;
    for (int i=0;i<n;i++) {
        roots.insert(dsu.find(i));
    }
    int full = 0, notFull = 0;
    for (auto v: roots) {
        if (nodes[v].isFull()) full++;
        else notFull = 1;
    }
    cout << full + notFull << ' '<< (int) roots.size() << '\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
