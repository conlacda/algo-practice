// https://codeforces.com/problemset/problem/1744/E2
/*Tóm tắt:
    Cho 4 số a, b, c, d
    tìm x, y thỏa mãn:
    a<x<=c
    b<y<=d
    x*y chia hết a*b
Độ khó: 1900 - math
*/
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

void solve(){
    ll a, b, c, d;
    cin >> a >> b >> c>> d;
    ll mul = a*b;
    /*
    Tìm mọi ước số của mul rồi lấy ra số y 
    Có y rồi thì x chia hết cho x1 là được.
    Tìm x1 là ước của a*b (1 triệu kết quả)
    Từ x1 thì tìm ra y = (d/k)*k
    rồi x chỉ cần chia hết cho x1 là xong

    x*y % (a*b) = 0
    tách x = x1*x2 và y = y1*y2 với xi * yi = a*b - chắc chắn tồn tại x1, x2, y1, y2 
    x1*x2*y % a*b = 0
    Giả sử xi trên kìa là x1.
    a*b = x1*yi -> a*b chia hết cho x1
    x = x1*x2 -> x chia hết cho x1
    -> tìm x1 -> x = (a, c] và chia hết cho x1 thì lấy c/x1 *x1 là ra số gần nhất với c chia hết cho x1
    Khi này y * x1 % (a*b) = 0 -> y chia hết cho a*b/x1
    Với x1 ta có thể tìm được y. 1 số trong khoảng (b, d] chia hết cho a*b/x1 = k-> lấy d/k *k là xong
    Kiểm tra x, y sau khi tìm có thỏa mãn trong khoảng ko là xong
    */
    vector<ll> uoca, uocb;
    for (ll i=1;i<=round(sqrt(a));i++){
        if (a % i ==0){
            uoca.push_back(i);
            uoca.push_back(a/i);
        }
    }
    for (ll i=1;i<=round(sqrt(b));i++){
        if (b % i ==0){
            uocb.push_back(i);
            uocb.push_back(b/i);
        }
    }
    dbg(uoca , uocb);
    for (auto i: uoca){
        for (auto j: uocb){
            ll xc = i*j;
            ll s = (a*b) / (i*j);
            ll yc = (d/s) *s;
            xc = (c/xc) * xc;
            if (yc > b && xc > a) {
                cout << xc << ' '<< yc<< '\n';
                return;
            }
        }
    }
    cout << -1 <<' ' <<-1<<'\n';
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    // cout << setprecision(2);
    int n;
    cin >> n;
    while (n--) solve();
    
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
