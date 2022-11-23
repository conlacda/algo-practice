#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif

// Extended euclid algorithm
ll x, y; // https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
ll extended_gcd(ll a, ll b) {
    x = 1, y = 0;
    ll x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        ll q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1; // a1 chính là std::gcd(a, b);
}
/*
ax + by = gcd(a,b);
-> gọi gcd(a,b) sẽ được x,y,gcd(a, b)
*/
void solve(){
    ll a, b, n, m;
    cin >> a >> n >> b >> m;
    a = a % n;
    b = b % m;
    /*
    x = a + n * k1
    x = b + m * k2
    => a + n *k1 = b + m *k2
    => n * k1 + m * k2 = ba
    => n * (k1/ba) + m * (k2/ba) = 1 // tại đây có thể có trường hợp m chia hết cho (b-a) và k2 ko chia hết
    // nhưng mình bỏ qua trường hợp đó mà chỉ xét tới đoạn k1 và k2 chia hết cho b-a. Khi này trở thành dạng ax + by = 1 cho a,b (n,m) nguyên tố cùng nhau
    */
    extended_gcd(n, m);
    // -1 * 2 + 1 * 3 = 1
    // 5 = 2 * 2 + 1 = 3* 1 + 2
    // x = n *k1 + a = m*k2 + b
    dbg(x, y);
    ll k1 = x * (b-a); // tới đoạn này có thể k1 âm, k2 dương
    // k1*n+k2*m = 1 => n * (k1+m) + m *(k2-n) = 0 -> k1 có thể cộng thêm m để dần trở thành số dương
    k1 = k1 % m;
    if (k1<=0) k1+=m;
    cout << a + n * k1 << ' ' << n*m << '\n';
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
