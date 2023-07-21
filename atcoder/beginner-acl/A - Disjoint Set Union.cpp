#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

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

int main() {
    int N, Q;
    cin >> N >> Q;
    DSU dsu(N);
    while (Q--) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 0) {
            dsu.merge_set(u, v);
        } else {
            if (dsu.find_set(u) == dsu.find_set(v)) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }
}