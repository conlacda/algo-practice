// https://www.hackerearth.com/practice/data-structures/disjoint-data-strutures/basics-of-disjoint-data-structures/practice-problems/algorithm/website-0317dd3a/
/*
Problem
On a website, there are  users and they want to change their names. You will be given  lines consisting of two strings  and B, where username  wants to change his username to . But the website does not support multiple users with the same username that is No two users can have the same username at the same time. A user can change his username from his current name to any name (X) if there is no user named X.
Every change in the username costs 1 unit of money. Find minimum cost to achieve these changes.

Notes

If user X wants to change his username from a to b while user Y wants to change his username from b to a neither of the users can directly change as if a changes his name to b now there will be two users having the username b.
If user X wants to change his username from a to a, so the user doesn't need to do anything.
It is guaranteed that no two users have the same username initially and no two users will have the same once all the changes are done.
It can be proved that the changes can always be done.
Input format

The first line consists of an integer  denoting the number of test cases.
The first line of each test case contains an integer  denoting the number of users.
Each of the next  lines of every test case contain two strings  and  where the  user wants to change his username from  to .
Output format

For each test case:

Print a single line denoting the minimum cost for completing the changes in usernames.
Constraints

Each string consists of lower case Latin letters and has a length between 5 and 10.
The sum of  over all test cases will not exceed 200000.

INP
1
3
abcdef bcdfe
bcdfe abcdef
ramesh suresh
OUT
4
*/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

class DSU {
 public:
  vector<int> parent, _rank;
  int N;
  DSU(int N) {
    this->N = N;
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
    assert(0 <= v && v < N);
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
void solve(){
    int n; cin >> n;
    int edge = 0;
    unordered_map<string, int> ms;
    int vnum = 0;
    vector<pair<int, int>> inp;
    for (int i=0;i<n;i++){
        string left, right;
        cin >> left >> right;
        if (left == right) continue;
        edge++;
        if (ms.find(left) == ms.end()){
            // chưa tồn tại
            vnum++;
            ms[left] = vnum;
        }
        if (ms.find(right) == ms.end()){
            // chưa tồn tại
            vnum++;
            ms[right] = vnum;
        }
        inp.push_back({ms[left] - 1, ms[right] - 1});
    }
    dbg(inp);
    dbg(vnum);
    DSU dsu(vnum);
    int cycle = 0;
    for (auto p: inp){
        if (dsu.find_set(p.first) != dsu.find_set(p.second)) {
            dsu.merge_set(p.first, p.second);
        } else {
            cycle++;
        }
    }
    dbg(cycle, edge);
    cout << edge + cycle <<'\n';
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while(n--) solve();
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
