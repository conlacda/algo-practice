// https://atcoder.jp/contests/abc319/tasks/abc319_e
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

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    cout << std::fixed << setprecision(15);
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> p(n) , t(n);
    for (int i=0;i<n-1;i++) {
        cin >> p[i] >> t[i];
    }
    std::function<int(int)> calTime = [&](int start){
        // Bat dau tai start, sau bao lau thi toi noi
        int st = start;
        start = start + x;
        for (int i=0;i<n-1;i++) {
            if (start % p[i] != 0) start = (start / p[i] + 1) * p[i];
            start += t[i]; 
        }
        start += y;
        return start - st;
    };
    vector<int> time(840);
    for (int i=0;i<840;i++) {
        time[i] = calTime(i);
    }
    int q;
    cin >> q;
    while (q--) {
        int start;
        cin >> start;
        dbg(start);
        // Tinh toan dua ra ket qua tai day
        cout << start + time[start % 840] << '\n';
    }
    
    show_exec_time();
}
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??

note:
Cái này mỗi thời điểm chỉ khác nhau điểm xuất phát
Còn lại bên trong thì lúc nào bus cũng đi cùng 1 lượng thời gian giống nhau
-> Tư duy: chắc chắn sẽ có vòng tuần hoàn để thời gian xuất phát thứ 1 và N+1, 2 & N+2, ... có tổng thời gian đi như nhau
-> vòng tuần hoàn đó là LCM của toàn bộ P từ 1->8 sẽ là 840 thế thì tính trước 840 kết quả đầu vào -> 840 *N phép tính

Với mỗi đầu vào -> Lấy mod cho 840 rồi in ra kết quả tương ứng

Khó nhất ở đây là nhìn ra được là lcm(1->8) thay vì là 8!
*/
