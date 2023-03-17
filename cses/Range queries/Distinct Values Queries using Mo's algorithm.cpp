// https://cses.fi/problemset/task/1734
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

template<typename T>
struct Compress {
    vector<T> rcv; // recover - giá trị mảng ban đầu đã sort và xóa unique
    vector<T> cpr; // compressed - giá trị đã nén của mảng a
    Compress() {}
    Compress(vector<T> v) { build(v);}
    void build(vector<T> v) {
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
    T compressed_val_by_index(T index) {
        return cpr[index];
    }
    ll recover(T compressedVal) {
        return rcv[compressedVal];
    }
};

const ll blockSize = 1000;
 
struct Query {
    ll l, r, index;
    friend bool operator<(Query a, Query b) {
        // những cái thuộc cùng 1 block sẽ đứng cạnh nhau, những cái cùng block thì r sẽ xếp từ bé tới lớn
        if (a.l/blockSize == b.l/blockSize) return a.r < b.r;
        return a.l/blockSize < b.l/blockSize;
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
    vector<ll> data; // lưu trạng thái hiện tại - lưu tần số của từng số có trong range [left, right] hiện tại
    vector<Ans> ans; // index, val
    ll cur_result = 0; // giá trị hiện tại, đối với những bài giá trị tuyến tính khi add, remove thì dùng, ko thì tính trực tiếp từ mảng data
    Compress<ll> c;
    Mo(vector<ll> a, vector<Query> queries) {
        this->a = a;
        data.resize(a.size(), 0);
        this->queries = queries;
        c.build(a);
    }
    void add(ll index) {
        ll val = c.compressed_val_by_index(index);
        if (data[val] == 0) cur_result++;
        data[val]++;
    }
    void remove(ll index) {
        ll val = c.compressed_val_by_index(index);
        if (data[val] == 1) cur_result--;
        data[val]--;
    }
    ll getResult() {
        return this->cur_result;
    }
    void solve() {
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
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll i=0;i<n;i++) cin >> a[i];
    vector<Query> queries;
    for (ll i=0;i<q;i++) {
        ll l, r;
        cin >> l >> r;l--;r--;
        queries.push_back(Query{l, r, i});
    }
    // dbg(queries);
    Mo mo(a, queries);
    mo.solve();
    for (auto v: mo.ans) {
        cout << v.val << '\n';
    }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Dùng Mo's algorithm nhưng đoạn kia nhất thiết không được dùng map để xử lý, map -> vector + compress
*/