// https://atcoder.jp/contests/arc175/tasks/arc175_a
#include<bits/stdc++.h>

typedef long long ll; // double long double
const ll mod = 998244353; // 998244353  1000000009  1000000007 // đừng dùng ull
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    /*
    dp??
    Xét 1 vòng tròn, 2 người bên cạnh nhau thì ko thể có 2 tay ngả về 2 hướng được
    dp[index][last] = cnt
    */
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto&v: a) {
        cin >> v;
        v--;
    }
    string s;
    cin >> s;
    /*
    Đến lượt 1 thằng bốc thì nó quan tâm tới 2 thằng gần nó nhất đã bốc
    2 thằng đó ko được cùng bốc về hướng nó hoặc cùng bốc ra xa hướng nó
    Nếu số nhỏ hơn 10 thì bruteforce là xong
    Số lớn hơn 10 => giải riêng

    Thay vì giải bằng dp có thể giải bằng recursive??
    Observation: tất cả đều phải lấy theo cùng 1 chiều bất kể tay thuận hay không
    nếu không thì ko thể đáp ứng yêu cầu
    */
    // solve for get left + solve for get right
    dbg(s);
    vector<bool> got(n, false);
    int ans = 0;
    int cnt = 1;
    // ăn right trước
    for (int i=0;i<n;i++) {
        int person = a[i];
        int hand = s[person];
        int next = person, prev = person - 1;
        if (prev < 0) prev = n-1;
        assert(!got[next]);
        if (got[prev]) {
            if (hand == '?') {
                cnt *= 2;
                cnt %= mod;
            }
        }
        else {
            if (hand == 'L') {
                cnt = 0;
                break;
            }
        }
        got[next] = true;
    }
    ans += cnt;
    cnt = 1;
    got = vector<bool>(n, false);
    // ăn left trước
    for (int i=0;i<n;i++) {
        int person = a[i];
        int hand = s[person];
        int next = person-1, prev = person;
        if (next < 0) next = n-1;
        assert(!got[next]);
        if (got[prev]) {
            if (hand == '?') {
                cnt *= 2;
                cnt %= mod;
            }
        }
        else {
            if (hand == 'R') {
                cnt = 0;
                break;
            }
        }
        got[next] = true;
        dbg(person, next, got, cnt);
    }
    dbg(cnt);
    ans += cnt;
    ans %= mod;
    cout << ans;
    show_exec_time();
}
