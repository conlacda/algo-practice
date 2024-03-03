// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // INT32_MAX  DBL_MAX

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Node {
    int largest = 0; // giá trị mặc định nên để là 0 // ***
    int largest_cnt = 0;
    int second_largest = 0;
    int second_largest_cnt = 0;
    bool is_null = false;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        map<int, int, greater<int>> m;
        m[a.largest] += a.largest_cnt;
        m[b.largest] += b.largest_cnt;
        m[a.second_largest] += a.second_largest_cnt;
        m[b.second_largest] += b.second_largest_cnt;
        auto [largest, largest_cnt] = *m.begin();
        auto [second_largest, second_largest_cnt] = *std::next(m.begin());
        return Node {
            largest,
            largest_cnt,
            second_largest,
            second_largest_cnt
        }; // ***
    }
    Node operator!() { return *this; }

    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

template<typename Node = Node>
class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(vector<Node>& v){ build(v);}
    void build(vector<Node>& v) {
        n = 1; while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1, Node{.is_null = true});
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
    void set(int index, Node x) {
        index += n - 1;
        dat[index] = x;
        while (index > 0) {
            index = (index - 1) / 2;
            dat[index] = dat[index * 2 + 1] + dat[index * 2 + 2];
        }
    }
    template<class... P> void set(int index, P... params) { set(index, Node{params...});}
    Node query(int l, int r){
        assert(l <= r);
        Node left = Node{.is_null = true}, right = Node{.is_null = true};
        l += n - 1; r += n;
        while (l < r) {
            if ((l & 1) == 0) left = left + dat[l];
            if ((r & 1) == 0) right = dat[r - 1] + right;
            l = l / 2; r = (r - 1) / 2;
        }
        return left + right;
    }
    // Retrieve current state of vector
    vector<Node> original() {
        vector<Node> res;
        for (int i=0;i<n;i++){
            res.push_back(query(i, i));
        }
        return res;
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<Node> sega;
    for (auto&v:a) {
        cin >> v;
        sega.push_back(Node{v, 1, 0, 0});
    }
    dbg(sega);
    SegmentTree seg(sega);
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            seg.set(--l, Node{r, 1, 0, 0});
        } else {
            auto node = seg.query(--l, --r);
            cout << node.second_largest_cnt << '\n';
        }

    }
    /*
    Dùng segtree -> mỗi node duy trì 1 cặp 2 số
    */


    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
    int vs long long
RE:
    binary search - INF ??
friend std::ostream& operator<<(std::ostream& os, const S s) { return os << destructure(s);}
cout << std::fixed << setprecision(15);
*/
