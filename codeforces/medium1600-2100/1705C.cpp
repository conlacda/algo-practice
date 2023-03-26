// https://codeforces.com/contest/1705/submission/164431732
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

// Copy from nealwu's template - http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template<class Fun> class y_combinator_result { Fun fun_; public:template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {} template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }}; template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif
void solve(){
	ll n, c, q;
	cin >> n >> c>> q;
	string s;
	cin >> s;
	vector<ll> l(c), r(c), len(c+1);
	len[0] = n;
	for (ll i=0;i<c;i++){
		cin >> l[i] >> r[i];
		len[i+1] = len[i] + (r[i] - l[i] +1);
	}
	dbg(len);
	dbg(l, r);
	/*
	Cách giải đúng - hiện tại:
		Dùng đệ quy để dịch ngược.
		p tại lớp c sẽ tương ứng với p' tại lớp (c-1)
		Cuối cùng suy ra được c==1 thì trả ra s[p]
	Cách giải sai:
		Theo như cách giải: https://codeforces.com/contest/1705/submission/164393304
		thì mình dựng hàng loạt các pair
		[(1,4),(1,4),(3,4),(1,3)]
		Với 1 thao tác copy paste thì mình lại tính toán xem thao tác đó chứa các khoảng nào
		dựa vào khoảng đã cho. Ví dụ (2->6) thì mình xác định là lấy ở a[0] (1,4) ra 1 khoảng
		(2->4) và khoảng a[1] (1,4) ra nốt 2 phần tử nữa là (1,2)
		-> a = [(1,4),(1,4),(3,4),(1,3),(2,4),(1,2)] thao tác này khá phức tạp
		Và sau cùng với 40 thao tác copy. Ví dụ 1->a.size() liên tục. Ta sẽ có a.size()*2^40 làm
		quá tải.
	*/
	auto cal = y_combinator([&] (auto cal, ll p, ll c) -> ll {
		dbg(p, c);
		while (p <= len[c-1] && c>0) c--;
		if (c == 0) return p-1;
		return cal(p - len[c-1] + l[c-1] -1 ,c-1);
	});
	while (q--) {
		ll p; cin >> p;
		cout << s[cal(p, c)] <<'\n';
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
		freopen("out.txt", "w", stdout);
    #endif
	// cout << setprecision(2);
	int N;
	cin >> N;
	while (N--) solve();

	cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
