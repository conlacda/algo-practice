// https://atcoder.jp/contests/abc268/tasks/abc268_e
// https://atcoder.jp/contests/abc268/tasks/abc268_e
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

struct Lznode {
    int val = 0; // Node x; assert(x.apply(LzNode()) == x) // ***
    bool is_null = false;
    // Apply 1 node lần thứ 2
    static Lznode composition(Lznode first, Lznode second) {
        if (first.is_null) return second;
        if (second.is_null) return first;
        return Lznode {
            first.val + second.val, // ***
        };
    }
};

struct Node {
    int val = 0; // ***
    bool is_null = false;
    // Hàm merge: thể hiện việc merge 2 node từ dưới lên trên
    static Node merge(Node l, Node r) {
        if (l.is_null) return r;
        if (r.is_null) return l;
        return Node {
            0, // bài không yêu cầu range query thì để là 0 // ***
        };
    }
    friend Node operator+(Node l, Node r) { return Node::merge(l, r); }

    // Apply cho 1 node to bự - hình dung nó là apply cho 1 range. Ví dụ fx = ax+b. Khi apply cho 1 range thì b sẽ được tính bằng sizeof(range)
    void apply(Lznode lz) {
        if (lz.is_null) return;
        val = val + lz.val; // ***
    }
    Node operator!() { return *this; } // dùng cho thao tác query có xét chiều. Node a + Node b = !(Node b + Node a)
    friend std::ostream& operator<<(std::ostream& os, const Node& s) { return os << destructure(s);}
};

struct LazySegtree {
  private:
    int N, size, log;
    vector<Node> data;
    vector<Lznode> lz;

    void update(int k) { data[k] = Node::merge(data[2 * k], data[2 * k + 1]); }
    void all_apply(int k, Lznode lzn) {
        data[k].apply(lzn);
        if (k < size) lz[k] = Lznode::composition(lz[k], lzn);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = Lznode{.is_null = true};
    }
  public:
    LazySegtree() {}
    LazySegtree(std::vector<Node>& v) {build(v);}
    void build(const std::vector<Node>& v) {
        this->N = (int) v.size();
        log = 0; while ((1U << log) < (unsigned int)(N)) log++; 
        size = 1 << log;
        data.resize(2 * size, Node{.is_null = true});
        lz.resize(size, Lznode{.is_null = true});
        for (int i = 0; i < N; i++) data[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    void set(int p, Node x) {
        assert(0 <= p && p < N);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        data[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    template<class... P> void set(int index, P... params) { set(index, Node{params...});}

    Node query(int l, int r) {
        r++;
        assert(0 <= l && l <= r && r <= N);
        if (l == r) return Node{.is_null = true};

        l += size; r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        Node sml = Node{.is_null = true}, smr = Node{.is_null = true};
        while (l < r) {
            if (l & 1) sml = Node::merge(sml, data[l++]);
            if (r & 1) smr = Node::merge(data[--r], smr);
            l >>= 1; r >>= 1;
        }

        return Node::merge(sml, smr);
    }

    Node query_all() { return data[1]; }

    void update(int l, int r, Lznode lznode) {
        r++; assert(0 <= l && l <= r && r <= N);
        if (l == r) return;
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, lznode);
            if (r & 1) all_apply(--r, lznode);
            l >>= 1; r >>= 1;
        }
        l = l2; r = r2;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    template<class... P> void update(int l, int r, P... params) { update(l, r, Lznode{params...});}

    vector<Node> original() {
        vector<Node> result;
        for (int i=0;i<N;i++) {
            result.push_back(query(i, i));
        }
        return result;
    }
};
// http://localhost:3000/docs/competitive-programming/range-queries/lazy-segment-tree

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) cin >> v;
    LazySegtree seg;
    vector<Node> sega(n, Node{0});
    seg.build(sega);
    // Từng số 1 lấy ra 3 đoạn đưa vào segmentree
    for (int i=0;i<n;i++) {
        int val = a[i];
        int index = i;
        int diff = val - index;
        if (diff < 0) diff += n;
        // cal half
        int half_down = n/2;
        int half_up = n/2;
        if (half_up * 2 < n) half_up++;
        // lấy ra 3 đoạn khi quay nó 1 vòng
        if (diff <= half_down) {
            // giảm -> tăng -> giảm
            seg.update(1, diff, -1);
            seg.update(diff + 1, min(n-1, diff + n - half_up), 1);
            if (diff + n - half_down + 1 <= n -1)
                seg.update(diff + n - half_down + 1, n-1, -1);
        } else if (diff == half_up) {
            if (half_up != half_down) {
                // skip -> giảm -> tăng
                seg.update(2, half_up, -1);
                seg.update(half_up +1, n-1, 1);
            }
        } else {
            // diff > half_up
            seg.update(1, diff - half_up, 1);
            dbg(diff, half_up, half_down);
            seg.update(diff - half_down + 1, diff, -1);
            seg.update(diff + 1, n-1, 1);
        }
    }

    // tính sum ban đầu
    int ans = 0;
    for (int i=0;i<n;i++) {
        int diff = abs(a[i] - i);
        diff = min(diff, n-diff);
        ans += diff;
    }
    // tính sum khi dịch từng bước 1
    int cur = ans;
    for (int i=0;i<n;i++) {
        cur += seg.query(i, i).val;
        ans = min(ans, cur);
    }
    // lấy ra kết quả
    cout << ans;
    show_exec_time();
}

/*
Tưởng tượng trong quá trình làm: ta sẽ có 1 vòng tròn với 4 điểm như sau
            half
             .
half_down  .   .  half_up
         .       .
      diff .   .
             . n
Ta sẽ có 4 điểm half_down, half_up, diff, n
half được cho thêm vào biểu tượng chứ ko có ý nghĩa gì.
    Khi n lẻ thì half_up và half_down cách nhau 1 đơn vị khi này thì hình tròn sẽ mất half
    n chẵn thì half_up = half_down = half

diff là số vòng quay để đưa giá trị k về đúng index k (frustration = 0)

Cách giải:
* Ta sẽ xét từng người 1. Mỗi người sẽ có 1 diff nằm 1 trong các khoảng [half_down ->n], [half_up -> half_down], [n->half_down]
* tại hình trên có diff < half_down < half_up < n
    Với mỗi lần quay thì diff sẽ đi ngược kim đồng hồ chạy về phía n.
* Sẽ có tổng cộng 3 khoảng cần xét cho 1 diff.
    Ví dụ ở hình trên sẽ có diff đi về phía n. Khi này frustration sẽ giảm đi -1 mỗi lần quay (mỗi step)
        Sau đó khi đi từ n->half_up thì frustration + 1 mỗi step
        Sau đó từ half_down -> diff thì frustration - 1 mỗi step
        Lưu ý: half_up và half_down có frustration như nhau nên ko cần xét
    Với mỗi diff ta sẽ biết được các khoảng nào nó +1 và khoảng nào -1
    1 ví dụ khác: diff nằm trong khoảng n->half_up
        diff sẽ tiến về half_up với diff - half_up bước. Mỗi step frustration tăng 1 (do đi xa điểm n - hay chính là điểm 0)
        diff từ half_up -> half_down bỏ qua
        diff từ half_down -> n sẽ giảm 1 mỗi bước
        diff từ n -> diff -1 sẽ tăng 1 mỗi bước
Tổng cộng có tối đa n - 1 lần xoay cần xét. Quay n lần thì về vị trí ban đầu. Vị trí ban đầu sẽ được tính với O(N)
Mỗi step mk đã biết được 1 người sẽ tăng hay giảm frustration tại bước tiếp theo đó.
=> Tính giá trị ban đầu = cur.
Index tiếp theo cur = cur + seg.query(index, index);
Lấy ra cur nhỏ nhất là được.
Mảng đầu vào của seg sẽ có độ dài là n với mỗi index tương ứng với 1 lần quay, tối đa n-1 lần quay
Mỗi index sẽ chứa giá trị thay đổi so với index trước đó = tổng giá trị thay đổi của toàn bộ người trong bàn
Mỗi người xét 3 khoảng tăng giảm thì từng index sẽ được thay đổi với seg.update(l, r, 1/-1)
*/
