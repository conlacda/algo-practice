// https://www.spoj.com/problems/CHAIN/
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
// #define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

// Full example: https://github.com/conlacda/algo-practice/blob/master/atcoder/beginner-acl/disjoint-union-set.md
// Verification: https://www.spoj.com/status/ns=29074396 -- chạy với dsu ko trọng số (default_w =0) https://atcoder.jp/contests/practice2/submissions/28973788
class DSU_has_weight {
 public:
  vector<int> parent, rank, weight;
  DSU_has_weight(int N) {
    parent.resize(N);
    rank.resize(N, 0);
    weight.resize(N, 0);
    for (int i = 0; i < N; i++) parent[i] = i;
  }

  int find(int v) {
    if (v == parent[v]) return v;
    int root = find(parent[v]);
    weight[v] += weight[parent[v]];
    parent[v] = root;
    return root;
  }

  void merge(int a, int b, int d=0) {
    assert(find(a) != find(b)); // dsu này không chấp nhận việc merge 2 phần tử đã có rồi. nếu không sẽ làm hỏng trọng số khi có đường tròn vd 1 là root, 2->1=1 3->1=2 thì 2->3 tính được bằng distance(). Nếu có 2->3=x thêm vào sẽ lỗi.
    int dist = -distance(a, find(a)) + d + distance(b, find(b));
    int ra = find(a); a = ra;
    int rb = find(b); b = rb;
    if (ra != rb) {
      if (rank[ra] < rank[rb]) swap(ra, rb);
      parent[rb] = ra;
      if (rank[ra] == rank[rb]) rank[ra]++;
    }
    int r = find(ra);    
    if (r==a){
        weight[a] = 0;
        weight[b] = -dist;
    } else {
        weight[a] = dist;
        weight[b] = 0;
    }
  }

  // tính khoảng cách của 2 node. (a->b = 0 - b->a)
  int distance(int a, int b){
    if (find(a) != find(b)) return INF;
    else return weight[a] - weight[b];
  }
};
/*
DSU_has_weight dsu(N); // dsu này chiều 1->2 khác 2->1
if (dsu.find(u) != dsu.find(v)) { (1)
//if (dsu.distance(u, v) == INT_MAX){ (2) 
    dsu.merge(u,v, w); 
}
//(1) và (2) tương đương nhau
dsu.distance(u, v); // tính khoảng cách 2 điểm
dsu.find(u) == dsu.find(v); // check if u,v in the same SCC
*/
void solve(){
    int n, q;
    cin>>n>>q;
    int ans=0;
    DSU_has_weight dsu(n+1);
    for (int i=0;i<q;i++){
        int t, a, b;
        cin>> t>>a>>b;
        t--;
        if (a>n || b>n) { ans++; continue;}
        if (t==1 && a==b) { ans++; continue;}
        int d = dsu.distance(a, b);
        if (t==0){
            if (d != INT_MAX){
                if (d%3!=0) ans++;
                continue;
            }
            dsu.merge(a, b, 0);
        } else {
            if (d!= INT_MAX) {
                if (((d%3)+3)%3!=1) ans++;
                continue;
            }
            dsu.merge(a, b, 1);
        }
    }
    cout << ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N;
    cin >> N;
    while (N--) solve();

    show_exec_time();
}
