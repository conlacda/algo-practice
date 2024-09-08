// https://atcoder.jp/contests/abc370/tasks/abc370_d
#pragma GCC optimize("O3") // optimize("Ofast,unroll-loops")
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
#endif

struct Node {
    int val = 0; // giá trị mặc định nên để là 0// ***
    bool is_null = false;
    friend Node operator+(Node a, Node b) {
        if (a.is_null) return b;
        if (b.is_null) return a;
        return Node{a.val + b.val};// ***
    }
};

template <typename Node>
struct SegmentTree2D {
private:
    Node internal_query(int h, int w1, int w2) {
        Node res = Node{.is_null = true};
        for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
            if (w1 & 1) {res = res + seg[id(h, w1)]; w1++;}
            if (w2 & 1) {w2--; res = res + seg[id(h, w2)];}
        }
        return res;
    }
    int id(int h, int w) const { return h * 2 * W + w; }

 public:
    int H, W;
    vector<Node> seg;
    SegmentTree2D(int h, int w) { 
        H = W = 1;
        while (H < h) H <<= 1;
        while (W < w) W <<= 1;
        seg.assign(4 * H * W, Node{.is_null = true});
        for (int i=0;i<h;i++)
            for (int j=0;j<w;j++)
                set(i, j, Node{}); 
    }

    // Gán giá trị cho mảng khởi tạo trước khi build
    void set(int h, int w, const Node& x) { seg[id(h + H, w + W)] = x; }
    void build() {
        // dbg(std::numeric_limits<T>::max());
        // w in [W, 2W)
        for (int w = W; w < 2 * W; w++) {
            for (int h = H - 1; h; h--) {
                seg[id(h, w)] = seg[id(2 * h + 0, w)] + seg[id(2 * h + 1, w)];
            }
        }
        // h in [0, 2H)
        for (int h = 0; h < 2 * H; h++) {
            for (int w = W - 1; w; w--) {
                seg[id(h, w)] = seg[id(h, 2 * w + 0)] + seg[id(h, 2 * w + 1)];
            }
        }
    }

    void update(int h, int w, const Node& x) {
        h += H, w += W;
        seg[id(h, w)] = x;
        for (int i = h >> 1; i; i >>= 1) {
            seg[id(i, w)] = seg[id(2 * i + 0, w)] + seg[id(2 * i + 1, w)];
        }
        while (h) {
            for (int j = w >> 1; j; j >>= 1) {
                seg[id(h, j)] = seg[id(h, 2 * j + 0)] + seg[id(h, 2 * j + 1)];
            }
            h >>= 1;
        }
    }

    // Lấy ra giá trị tại 1 điểm
    Node query(int h, int w) { return seg[id(h + H, w + W)]; }

    // query hình chữ nhật (h1, w1) -> (h2, w2)
    Node query(int h1, int w1, int h2, int w2) {
        h2++; w2++; // bản gốc [h1 -> h2) => mk chuyển thành [h1 -> h2]
        // if (h1 >= h2 || w1 >= w2) return I;
        assert(h1 < h2 && w1 < w2);
        Node res = Node{.is_null = true};
        h1 += H, h2 += H, w1 += W, w2 += W;
        for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
            if (h1 & 1) {
                res = res + internal_query(h1, w1, w2); h1++;
            }
            if (h2 & 1) {
                h2--; res = res + internal_query(h2, w1, w2);
            }
        }
        return res;
    }

    // Additional
    Node query_row(int row, int lcol, int rcol) {
        return query(row, lcol, row, rcol);
    }
    Node query_col(int col, int lrow, int rrow) {
        return query(lrow, col, rrow, col);
    }
    Node query_all() {
        return query(0, 0, H-1, W-1);
    }

    int rowFirstGreaterIndex(int row, int index, int K) {
        int l = index, r = W-1;
        while (l < r) {
            int mid = (l + r) /2;
            if (query_row(row, index, mid).val >= K) r = mid;
            else l = mid + 1;
        }
        if (query_row(row, index, r).val < K) return -1;
        return r;
    }
    int colFirstGreaterIndex(int col, int index, int K) {
        int l = index, r = H-1;
        while (l < r) {
            int mid = (l + r) /2;
            if (query_col(col, index, mid).val >= K) r = mid;
            else l = mid + 1;
        }
        if (query_col(col, index, r).val < K) return -1;
        return r;
    }
    int rowFirstLessIndex(int row, int index, int K) {
        int l = 0, r = index;
        while (l < r) {
            int mid = ((l + r) % 2 == 0) ? (l + r) / 2: (l + r + 1) / 2;
            if (query_row(row, mid, index).val >= K) l = mid;
            else r = mid-1;
        }
        if (query_row(row, l, index).val >= K) return l;
        // if (query_row(row, r, index).val >= K) return r;
        // if (query_row(row, l, index).val >= K) return l;
        return -1;
    }
    int colFirstLessIndex(int col, int index, int K) {
        int l = 0, r = index;
        while (l < r) {
            int mid = (l + r) /2;
            if (mid * 2 < l + r) mid++;
            if (query_col(col, mid, index).val >= K) l = mid;
            else r = mid - 1;
        }
        if (query_col(col, l, index).val >= K) return l;
        // if (query_col(col, r, index).val >= K) return r;
        // if (query_col(col, l, index).val >= K) return l;
        return -1;
    }
};
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << std::fixed << setprecision(15);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int h,w,q;
    cin >> h >> w >> q;
    SegmentTree2D<Node> seg(h,w);
    for (int i=0;i<h;i++) {
        for (int j=0;j<w;j++) {
            seg.set(i, j, Node{1}); 
        }
    }
    seg.build();
    while (q--) {
        int r, c;
        cin >> r >> c;
        r--; c--;
        if (seg.query(r, c).val == 1) {
            seg.update(r, c, Node{0});
        } else {
            int ri = seg.rowFirstGreaterIndex(r, c, 1);
            if (ri != -1) seg.update(r, ri, Node{0});
            int rii = seg.colFirstGreaterIndex(c, r, 1);
            if (rii != -1) seg.update(rii, c, Node{0});
            int li = seg.rowFirstLessIndex(r, c, 1);
            if (li != -1) seg.update(r, li, Node{0});
            li = seg.colFirstLessIndex(c, r, 1);
            if (li != -1) seg.update(li, c, Node{0});
        }
    }
    cout <<seg.query(0, 0, h-1,w-1).val;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s✅\n";
}
