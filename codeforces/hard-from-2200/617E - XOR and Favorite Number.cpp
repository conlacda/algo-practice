// https://codeforces.com/contest/617/problem/E
// Key: a^b luôn tạo ra số có số chữ số bằng a, b-> int^int->int, tại đây constraint là 10^6 nên cnt là vector sẽ chạy ổn hơn là unordered_map (xem lịch sử submission trên codeforces) từ 0.5s -> 2.9s khi từ vector sang map/unodered_map
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif

inline int64_t hilbertOrder(int x, int y, int pow = 21, int rotate = 0) {
    if (pow == 0) {
        return 0;
    }
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? (
        (y < hpow) ? 0 : 3
    ) : (
        (y < hpow) ? 1 : 2
    );
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2*pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

struct Query {
    ll l, r, index;
    ll ord;
    friend bool operator<(Query& a, Query& b) {
        return a.ord < b.ord;
    }
    friend std::ostream& operator<<(std::ostream& os, const Query &s) { return os << destructure(s);}
};
struct Ans {
    ll index, val;
    friend bool operator<(Ans a, Ans b) {
        return a.index < b.index;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ans &s) { return os << destructure(s);}
};

struct Mo {
private:
    vector<ll> a; // mảng đầu vào
    vector<Query> queries; // l, r, index
public:
    vector<ll> cnt; // lưu trạng thái hiện tại - lưu tần số của từng số có trong range [left, right] hiện tại
    vector<Ans> ans; // index, val
    ll cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    vector<ll> prefix_xor;
    ll k;
    ll left, right;
    ll cur_xor = 0;
    Mo(vector<ll> a, ll k) {
        this->a = a;
        cnt.resize(1<<20, 0);
        this->queries = queries;
        this->k = k;
        calPrefixXor();
        this->left = 0;
        this->right = -1;
    }
    void calPrefixXor() {
        ll cur = 0;
        for (auto v: a) {
            cur = cur ^ v;
            prefix_xor.push_back(cur);
        }
    }
    void add_left(ll index) {
        cur_xor ^= a[index];
        ll preleft = (index == 0) ? 0 : prefix_xor[index-1];
        cnt[prefix_xor[index]]++;
        cur_result += cnt.at(preleft ^ k);
    }
    void add_right(ll index) {
        cur_xor ^= a[index];
        if (cur_xor == k) cur_result++;
        cur_result += cnt.at(prefix_xor[index] ^ k);
        cnt.at(prefix_xor[index])++;
    }
    void remove_left(ll index) {
        ll preleft = (index == 0) ? 0: prefix_xor[index-1];
        cur_result -= cnt[preleft ^ k];
        cnt.at(prefix_xor.at(index))--;
        cur_xor ^= a.at(index);
    }
    void remove_right(ll index) {
        if (cur_xor == k) cur_result--;
        cur_xor ^= a[index];
        cnt.at(prefix_xor[index])--;
        cur_result -= cnt.at(prefix_xor[index] ^ k);
    }
    ll getResult() {
        return this->cur_result;
    }
    void solve(vector<Query>& queries) {
        for (auto &q: queries) q.ord = hilbertOrder(q.l, q.r);
        sort(queries.begin(), queries.end());
        for (auto query: queries) {
            while (left > query.l) left--, add_left(left);
            while (right < query.r) right++, add_right(right);
            while (left < query.l) remove_left(left), left++;
            while (right > query.r) remove_right(right), right--;
            ans.push_back({query.index, getResult()});
        }
        sort(ans.begin(), ans.end());
        for (auto v: ans) cout << v.val << '\n';
    }
};
/*
Mo mo(a, queries);
mo.solve();
for (auto v: mo.ans) cout << v << ' ';
*/
int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, q, k;
    cin >> n >> q >> k;
    vector<ll> a(n);
    for (auto &v: a) cin >> v;
    vector<Query> queries;
    for (ll i=0;i<q;i++) {
        ll l, r; cin >> l >> r; l--; r--;
        queries.push_back(Query{l, r, i});
    }
    Mo mo(a, k);
    mo.solve(queries);

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
bài này tại tutorial: https://codeforces.com/contest/617/submission/15550846
nó làm rất đẹp đoạn add() và remove(), nhưng để ý đoạn query có left--, right++
prefix_xor nó cũng thêm số 0 ở đầu
mình ko làm đc kiểu đó vì sẽ bị rắc rối đoạn index+-1
nên đã tách ra add_left, add_right, remove_left, remove_right
bởi vì prefix_xor bắt đầu từ bên trái nên khi add_left với add_right khác 
nhau vì prefix chỉ bắt đầu từ bên trái.
Ban đầu cứ viết đại theo như bài mẫu rồi sau phải tách ra left, right xử lý riêng
*/
