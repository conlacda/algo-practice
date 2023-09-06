// https://codeforces.com/contest/1856/problem/C
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max();

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    /*
    Binary search cho giá trị k
    */
    int maxAns = 0;
    for (int i=0;i<n;i++) {
        maxAns = max(maxAns, a[i] + i);
    }
    dbg(maxAns);
    std::function<bool(int)> canCreate = [&](int val){
        // Có thể tạo ra được val với k thao tác hay không
        if (val > maxAns) return false;
        // duyệt mỗi index và đặt val vào đó.
        // trượt dần nó về phía phải nếu val mong muốn vẫn lớn hơn val thực tế của nó
        // Đồng thời cộng giá trị
        // Tương ứng sẽ là n^2
        for (int i=0;i<n;i++) {
            int remain = k;
            int v = val;
            for (int j=i;j<n;j++) {
                if (a[j] >= v) {
                    if (remain >= 0){
                        return true;
                    }
                    break;
                }
                remain = remain - (v - a[j]);
                v--;
            }
        }
        /*
        Ban chat la dat 1 vi tri index i la gia tri X.
        Khi nay gia tri i+1 se co gia tri X-1
        i+2 co gia tri X-2....
        Neu gia tri co san cua no lon hon gia tri X-i nay 
        thi tuc la cac gia tri sau ko can thay doi - tuc la ko ton thao 
        tac vao no.
        Kiem tra xem so thao tac k ban dau cho co du de tao ra
        so X khong. Du thi ok, ko du thi gia tri can tim se nho xuong
        */
        return false;
    };
    int left = 1, right = 1e8 + 1005;
    while (left < right -1) {
        int mid = (left + right) / 2;
        if (canCreate(mid)) {
            left = mid;
        } else right = mid -1;
    }
    if (canCreate(right)) {
        cout << right << '\n';
    } else cout << left << '\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n;
    cin >> n;
    while (n--) solve();
    
    show_exec_time();
}
