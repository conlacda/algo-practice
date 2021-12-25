//https://codeforces.com/contest/25/problem/D
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Full example: https://github.com/conlacda/algo-practice/blob/master/atcoder/beginner-acl/disjoint-union-set.md
class DSU {
public:
    vector < int > parent, _rank;
    DSU(int N) {
        this -> parent.resize(N);
        this -> _rank.resize(N);
        for (int i = 0; i < N; i++) {
            this -> make_set(i);
        }
    }
    
    void make_set(int v) {
        this -> parent[v] = v;
        this -> _rank[v] = 0;
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
    /* Cach 1:
    Dùng DFS/BFS để tìm ra cycle. Từ cycle sẽ loại bỏ cạnh đó
    Tìm SCC sau đó nối SCC vào nhau là đc
    Cách 2:
    Tạo ra DSU
    Nếu cùng set thì bỏ cạnh đó
    Duyệt parent - nếu khác cha thì nối vào nhau
    Or duyệt cặp cạnh (N^2) để nối vào nhau
    */
    DSU dsu(N+1);
    vector<pair<int,int>> closure, new_build;
    while (N-->1){
        int a,b;
        cin >> a>>b;
        int f1 = dsu.find_set(a), f2 = dsu.find_set(b);
        if (f1 == f2){
            closure.push_back({a,b});
        } else {
            dsu.merge_set(a,b);
        }
    }
    // for (auto v: dsu.parent) cout << v << ' ';
    for (int i=2;i<dsu.parent.size();i++){
        if (dsu.parent[i] != dsu.parent[i-1]){
            dsu.find_set(i);
            dsu.find_set(i-1);
            if (dsu.parent[i] != dsu.parent[i-1]){
                new_build.push_back({i, i-1});
                dsu.merge_set(i, i-1);
            }
        }
    }
    assert(new_build.size() == closure.size());
    cout << new_build.size() << '\n';
    for (int i=0;i< new_build.size(); i++){
        cout << closure[i].first << ' '<<closure[i].second << ' '<< new_build[i].first << ' ' <<new_build[i].second<<'\n';
    }
}
