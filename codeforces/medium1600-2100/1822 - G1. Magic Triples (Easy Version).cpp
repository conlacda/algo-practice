// https://codeforces.com/contest/1822/problem/G1
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
// #define int long long
// const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif
vector<int> v(1000005, 0); // Key - việc cấp phát liên tục v làm chương trình chạy cực chậm
// 1 cách làm ngay từ hồi đầu mình mới học đã dùng là ném tất cả biến dùng chung ra bên ngoài, dùng chung.
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i=0;i<n;i++) {
        cin >> a[i];
        v[a[i]] ++;
    }
    // Check b[i] là số chính phương trước??
    // vector<int> v(*max_element(a.begin(), a.end())+1, 0);
    // for (auto i: a) v.at(i)++;
    sort(a.begin(), a.end());
    a.erase( unique( a.begin(), a.end() ), a.end() );
    int _max = a[(int) a.size() -1];
    ll ans = 0;
    std::function<ll(int)> cal = [&](int u){
        // Tinh doan trung nhau truoc
        ll res = 0;
        if (v[u] >= 3) {
            res += 1LL* (v[u]-1) * (v[u]-2) * v[u];
        }
        for (int i=2;i<1001;i++) {
            int b = u * i * i;
            if (b > _max) break;
            int a = u * i;
            dbg(u, a, b);
            res += 1LL * v[a] * v[b] * v[u];
        }
        return res;
    };
    for (auto x: a) {
        ans += 1LL*cal(x);
    }
    for (auto i: a) v[i] = 0; // key - thay vì fill(all(a), 0) thì giờ chỉ fill lại 1 số phần tử thôi, tổng số phần tử <10^5 nên rất nhanh. Nếu ko thì mỗi lần fill 10^5 * 10^5
    cout << ans <<'\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    /*
    a*x=b, b*x=c;
    a*x^2=c
    a = 1, c = 10^6
    => x ~ 1000
    Sắp xếp rồi gộp các số lại.
    Với các số bằng nhau thì bằng cnt[x] * (cnt[x] - 1) * (cnt[x] -2)
    Với các số khác nhau thì duyệt qua từng số, rồi xem x = [2->1000] có thỏa mãn không
    */
    while (n--) solve();
    
    show_exec_time();
}
