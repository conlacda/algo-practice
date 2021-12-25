//Statement: https://codeforces.com/contest/1620/problem/E
//Submission: https://codeforces.com/contest/1620/submission/140599471

#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Full example:
// https://github.com/conlacda/algo-practice/blob/master/atcoder/beginner-acl/disjoint-union-set.md
class DSU {
 public:
  vector<int> parent, _rank;
  DSU(int N) {
    this->parent.resize(N);
    this->_rank.resize(N);
    for (int i = 0; i < N; i++) {
      this->make_set(i);
    }
  }

  void make_set(int v) {
    this->parent[v] = v;
    this->_rank[v] = 0;
  }

  int find_set(int v) {
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = find_set(parent[v]);
  }

  void merge_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (_rank[a] < _rank[b]) {
        swap(a, b);
      }
      parent[b] = a;
      if (_rank[a] == _rank[b]) {
        _rank[a]++;
      }
    }
  }
};
/*
DSU dsu(N);
dsu.merge_set(u,v);
dsu.find_set(u) == dsu.find_set(v); // check if u,v in the same SCC
*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N;
    cin >> N;
    int length=0;
    vector<array<int,3>> qrs;
    for(int i=0;i<N;i++){
        int x,y,z=0;
        cin >> x;
        if (x==1){
            cin>>y;
            length++;
        } else cin >> y>>z;
        qrs.push_back({x,y,z});
    }
    DSU dsu(length);
    vector<int> a;
    map<int, int>val2id;
    int cur = 0;
    for (auto q: qrs){
        if (q[0] == 1){
            int val = q[1];
            a.push_back(val);
            if (val2id.count(val) ==0){
                val2id[val] = cur;
            } else{
                int old = val2id[val];
                dsu.merge_set(old, cur);
                int newid = dsu.find_set(old);
                val2id.erase(val);
                val2id[val] = newid;
                a[newid] = val;
            }
            cur++;
        } else{
            // q==2;
            if (val2id.count(q[1]) == 0) continue;
            if (val2id.count(q[2]) == 0){
                int p = dsu.find_set(val2id[q[1]]);
                a[p] = q[2];
                val2id.erase(q[1]);
                val2id[q[2]] =p;
            } else{
                int id1 = val2id[q[1]];
                int id2 = val2id[q[2]];
                dsu.merge_set(id1, id2);
                int newid = dsu.find_set(id1);
                val2id.erase(q[1]); val2id.erase(q[2]);
                val2id[q[2]] = newid;
                a[newid] = q[2];
            }
        }
    }
    for (int i=0;i<length;i++){
        int p = dsu.find_set(i);
        cout << a[p]<< ' ';
    }
}
// Bài này dùng val2id dạng map để lưu trữ giá trị nào đang ở id nào - id ở đây là đỉnh của cây trong DSU
// Mỗi lần merge sẽ luôn xóa hết các giá trị cũ đi rồi lấy ra đỉnh mới sau đó gán val2id[new_value] = new_index
// Ngược lại với val2id từ giá trị ra index thì mảng a sẽ lưu giá trị của mảng ban đầu
// Với việc thêm phần tử thì giá trị a không thay đổi
// Với việc cập nhật thì sẽ luôn lấy ra parent sau khi merge rồi gán giá trị mới vào cho nó
// Ví dụ a = [.., 2,.., 3,2,..];
// Replace 2->3 thì khi này p1 = 1 (giá trị 2), p2 = 3 (giá trị)
// dsu.merge(1,3); parent mới sẽ là 1 hoặc 3. Khi này parent = dsu.findset(1); a[parent] = 3; 
// a sẽ luôn giữ GIÁ TRỊ ĐÚNG của PARENT 