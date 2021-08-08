
```c++
// Verification: https://atcoder.jp/contests/practice2/tasks/practice2_a
// Reference: https://cp-algorithms.com/data_structures/disjoint_set_union.html#toc-tgt-0
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
/*

DSU dsu(N);
dsu.merge_set(u,v);
dsu.find_set(u) == dsu.find_set(v); // check if u,v in the same SCC
*/
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
```

Lưu ý: khi merge 2 SCC lại thì chỉ có 2 đỉnh đầu nối vào nhau - nghĩa là chỉ có parent[a] = b còn mọi children của a vẫn giữ nguyên parent là a. Cần chạy find_set cho từng đỉnh khi so sánh 2 con thay vì so sánh mỗi parent