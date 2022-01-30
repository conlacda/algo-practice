// https://www.spoj.com/problems/CHAIN/
// https://www.spoj.com/status/CHAIN,hoanglongvn/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Full example:
// https://github.com/conlacda/algo-practice/blob/master/atcoder/beginner-acl/disjoint-union-set.md
class DSU_has_weight {
 public:
  vector<int> parent, _rank;
  vector<int> weight;
  DSU_has_weight(int N) {
    this->parent.resize(N);
    this->_rank.resize(N);
    this->weight.resize(N);
    for (int i = 0; i < N; i++) {
      this->make_set(i);
    }
  }

  void make_set(int v) {
    this->parent[v] = v;
    this->_rank[v] = 0;
    this->weight[v] = 0;
  }

  int find_set(int v) {
    if (v == parent[v]) {
      return v;
    }
    int root = find_set(parent[v]);
    weight[v] += weight[parent[v]];
    parent[v] = root;
    return root;
  }

  void merge_set(int a, int b, int d) {
    assert(find_set(a) != find_set(b)); // dsu này không chấp nhận việc merge 2 phần tử đã có rồi. nếu không sẽ làm hỏng trọng số khi có đường tròn vd 1 là root, 2->1=1 3->1=2 thì 2->3 tính được bằng distance(). Nếu có 2->3=x thêm vào sẽ lỗi.
    int newd = -distance(a, find_set(a)) + d + distance(b, find_set(b));
    int ra = find_set(a); a = ra;
    int rb = find_set(b); b = rb;
    if (ra != rb) {
      if (_rank[ra] < _rank[rb]) {
        swap(ra, rb);
      }
      parent[rb] = ra;
      if (_rank[ra] == _rank[rb]) {
        _rank[ra]++;
      }
    }
    int r = find_set(ra);
    if (r==a){
        weight[a] = 0;
        weight[b] = -newd;
    } else {
        weight[a] = newd;
        weight[b] = 0;
    }
  }

  // tính khoảng cách của 2 node. (a->b = 0 - b->a)
  int distance(int a, int b){
    int pa = find_set(a);
    int pb = find_set(b);
    if (pa != pb) return -INT_MAX;
    else return weight[a] - weight[b];
  }
};
/*
DSU_has_weight dsu(N); // dsu này chiều 1->2 khác 2->1
if (dsu.find_set(u) != dsu.find_set(v)) {
    dsu.merge_set(u,v, w); 
}
dsu.distance(u, v); // tính khoảng cách 2 điểm
dsu.find_set(u) == dsu.find_set(v); // check if u,v in the same SCC
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
        int pa = dsu.find_set(a);
        int pb = dsu.find_set(b);
        if (t==0){
            if (pa == pb) {
                if (dsu.distance(a, b)%3 != 0) ans++;
            } else {
                dsu.merge_set(a, b, 0);
            }
        } else {
            if (pa == pb){
                if (((dsu.distance(a, b)%3)+3)%3!=1 ) ans++;
            } else{
                dsu.merge_set(a, b, 1);
            }
        }
    }
    cout << ans<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N;
    cin >> N;
    while (N--) solve();
}