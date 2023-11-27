// https://cses.fi/problemset/task/1734
// https://cses.fi/problemset/task/1734
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
 
template<typename T = int>
struct Compress {
    vector<T> rcv; // recover - giá trị mảng ban đầu đã sort và xóa unique
    vector<T> cpr; // compressed - giá trị đã nén của mảng a
    vector<T> a;
    Compress() {}
    Compress(vector<T> v) { build(v);}
    void build(vector<T> v) {
        this->a = v;
        rcv = v;
        sort(rcv.begin(), rcv.end());
        rcv.resize(unique(rcv.begin(), rcv.end()) - rcv.begin());
 
        cpr = v;
        for (int i = 0; i < (int) cpr.size(); ++i) {
            cpr[i] = lower_bound(rcv.begin(), rcv.end(), cpr[i]) - rcv.begin(); // O(logN) thay cho map
        }
    }
    T compressed_val(T originalVal) { // giá trị ban đầu sang giá trị đã compress
        T i = lower_bound(rcv.begin(), rcv.end(), originalVal) - rcv.begin();
        if (rcv[i] != originalVal) return -1;
        return i;
    }
    T operator[] (int index) {
        return cpr[index];
    }
    T original_val(T compressedVal) {
        return rcv[compressedVal];
    }   
};
 

inline int64_t hilbertOrder(int x, int y, int pow = 21, int rotate = 0) {
  if (pow == 0) {
    return 0;
  }
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
    friend bool operator<(Ans a, Ans b) {
        return a.index < b.index;
    }
    friend std::ostream& operator<<(std::ostream& os, const Ans &s) { return os << destructure(s);}
};

struct Mo {
private:
    vector<ll> a; // mảng đầu vào
public:
    vector<ll> data; // lưu trạng thái hiện tại - lưu tần số của từng số có trong range [left, right] hiện tại
    vector<Ans> ans; // index, val
    ll cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    Compress<int> c;
    Mo(vector<ll>& a) {
        this->a = a;
        data.resize((int) a.size(), 0);
        c.build(a);
    }
    void add(ll index) {
        ll val = c[index];
        if (data[val] == 0) cur_result++;
        data[val]++;
    }
    void remove(ll index) {
        ll val = c[index];
        if (data[val] == 1) cur_result--;
        data[val]--;
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
        Query q = Query{l, r, i};
        queries.push_back(q);
    }
    // dbg(queries);
    Mo mo(a);
    mo.solve(queries);
    for (auto v: mo.ans) {
        cout << v.val << '\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Dùng Mo's algorithm nhưng đoạn kia nhất thiết không được dùng map để xử lý, map -> vector + compress
*/
