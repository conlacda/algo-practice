#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

struct Node {
    int val1 = 0, val2 = 0; // giá trị mặc định nên để là 0
    bool is_null = true;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return Node {
            (a.val1 + b.val1) % mod,
            (a.val2 + b.val2) % mod,
            false
        };
    }
    static Node v(int val1, int val2) {
        return Node{val1, val2, false};
    }

    friend std::ostream& operator<<(std::ostream& os, const Node s) { return os << destructure(s);}
};

class SegmentTree {
private:
    int n;
    vector<Node> dat;
public:
    SegmentTree() {}
    SegmentTree(vector<Node> v){ build(v);}
    void build(vector<Node> v) {
        n = 1;
        while (n < (int) v.size()) n *= 2;
        dat.resize(2 * n - 1);
        for (int i=0;i<(int) v.size();i++) dat[n + i - 1] = v[i];
        for (int i = n - 2; i >= 0; i--) dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
    }
    void set_val(int i, Node x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }
    Node query(int l, int r){
        assert(l <= r);
        Node left = Node(), right = Node();
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

int toInt(char x) {
    return x - 'a' + 1;
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    SegmentTree seg;
    vector<Node> a(n);
    vector<int> pc;
    int cur = 1;
    for (int i=0;i<n;i++) {
        pc.push_back(cur);
        cur *= 256;
        cur %= mod;
    }
    for (int i=0;i<n;i++) {
        a[i] = Node:: v(pc[i] * toInt(s[i]) % mod, pc[n-1-i] * toInt(s[i]) % mod);
    }
    seg.build(a);
    /*
    */
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            // update
            int index; char c;
            cin >> index >> c;
            index--;
            seg.set_val(index, Node::v(pc[index] * toInt(c) %mod, pc[n-1-index] * toInt(c) %mod));
        } else if (t == 2) {
            // query
            int u, v;
            cin >> u >> v;
            u--; v--;
            auto node = seg.query(u, v);
            dbg(node);
            int delta = (u) - (n-1-v);
            dbg(delta);
            if (delta != 0) {
                if (delta < 0) {
                    node.val1 = (node.val1 * pc[-delta]) % mod;
                } else {
                    node.val2 = (node.val2 * pc[delta]) % mod;
                }
            } 
            if (node.val1 == node.val2) {
                cout << "Yes\n";
            } else cout << "No\n";
        }
    }
    /*
    Dung segment tree cap nhat prefix, suffix -> tinh tuong tu hash la duoc
    */
    show_exec_time();
}
/*
Bài này đơn giản là sử dụng segment tree. với mỗi node là 1 kí tự của string.
Nhưng do so sánh 2 string mất O(N) nên kí tự này sẽ được chuyển thành 1 số (giống như ở Hash-string).
abc thì a->1
       b->2 * 256
       c->3 * 256*2
Hàm merge() đơn giản là hàm cộng 2 số.
Để so sánh tính ngược xuôi thì 1 node sẽ lưu 2 giá trị như thế.
1 giá trị cho chiều xuôi, 1 cho ngược. Ví dụ abc -> {hash(abc), hash(cba)}
Query thì chỉ cần query range đó rồi so kết quả chiều xuôi với chiều ngược là xong. Lưu ý khi so sánh là chênh lệch hệ số nên cần biến delta để cho nó về cùng 1 hệ số
*/
