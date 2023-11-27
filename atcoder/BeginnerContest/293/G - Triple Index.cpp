// https://atcoder.jp/contests/abc293/tasks/abc293_g
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define int long long // __int128

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif


inline int64_t hilbertOrder(int x, int y, int pow = 21, int rotate = 0) { // 2**pow là số lượng query sẽ xử lý
    if (pow == 0) return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
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
    int l, r, index;
    ll ord = -1;
    friend bool operator<(Query& a, Query& b) {
        return a.ord < b.ord;
    }
    friend std::ostream& operator<<(std::ostream& os, const Query &s) { return os << destructure(s);}
};
struct Ans {
    ll index, val;
    friend bool operator<(Ans& a, Ans& b) {
        return a.index < b.index;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ans &s) { return os << destructure(s);}
};

struct Mo {
private:
    vector<int> a; // mảng đầu vào
public:
    vector<int> data; // lưu trạng thái hiện tại - lưu tần số của từng số có trong range [left, right] hiện tại
    vector<Ans> ans; // index, val
    int cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    Mo(vector<int>& a) {
        this->a = a;
        data.resize(200005, 0);
    }
    void add(ll index) {
        cur_result -= data[a[index]] * (data[a[index]]-1) * (data[a[index]]-2) /6;
        data[a[index]]++;
        cur_result += data[a[index]] * (data[a[index]]-1) * (data[a[index]]-2) /6;
    }
    void remove(ll index) {
        cur_result -= data[a[index]] * (data[a[index]]-1) * (data[a[index]]-2) /6;
        data[a[index]]--;
        cur_result += data[a[index]] * (data[a[index]]-1) * (data[a[index]]-2) /6;
    }
    ll getResult() {
        return this->cur_result;
    }
    void solve(vector<Query>& queries) {
        for (auto& q: queries) q.ord = hilbertOrder(q.l, q.r);
        sort(queries.begin(), queries.end());
        ll left = 0, right = -1;
        for (auto query: queries) {
            while (left > query.l) left--, add(left);
            while (right < query.r) right++, add(right);
            while (left < query.l) remove(left), left++;
            while (right > query.r) remove(right), right--;
            ans.push_back({query.index, getResult()});
        }
        sort(ans.begin(), ans.end());
    }
};

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i=0;i<n;i++) cin >> a[i];
    vector<Query> queries;
    for (ll i=0;i<q;i++) {
        ll l, r;
        cin >> l >> r;l--;r--;
        Query q = Query {l, r, i};
        queries.push_back(q);
    }
    Mo mo(a);
    mo.solve(queries);
    for (auto v: mo.ans) {
        cout << v.val << '\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
