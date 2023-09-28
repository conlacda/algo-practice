// https://codeforces.com/contest/1861/problem/D
// D. Sorting By Multiplication
// 1800
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define ld long double
#define int long long
const int INF = std::numeric_limits<int>::max(); // use 2147483647 for i32

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v: a) cin >> v;
    int cnt = 0;
    for (int i=0;i<n-1;i++) {
        if (a[i] >= a[i+1]) cnt++;
    }
    int ans = cnt;
    cnt++; // cộng 1 cho phần prefix đảo dấu - mất 1 thao tác
    for (int i=1;i<n;i++) {
        if (a[i-1] >= a[i]) cnt--;
        if (i >=2 && a[i-2] <= a[i-1]) cnt++;
        ans = min(ans, cnt);
    }
    cout << ans << '\n';
    /*
    Pattern sẽ là 1 loạt các số đứng đầu (prefix nhân với -1 để tạo thành số âm)
    Xét dãy đằng sau dương, nhận thấy càng nhân số đó càng to
    Thế thì việc nhân để tạo ra sorted array sẽ chỉ là việc đếm a[i] >= a[i+1]
    cứ số đằng trước mà lớn hơn hoặc bằng số đằng sau thì nhân toàn bộ a[i+1]->a[n-1] lên k lần (k cực kỳ lớn mà ko cần quan tâm giá trị)
    Đó là ý nghĩa đoạn code dòng 27->29
    Ngược lại đoạn prefix âm đằng trước ta sẽ có a[i]<=a[i+1] thì nhân toàn bộ a[0]->a[i] lên k lần thì càng nhân nó càng âm
    -> cũng chỉ cần đếm số cặp a[i] <= a[i+1] ngược lại với phần dương
    Chỉ có 1 lưu ý tại đây là đoạn i >=2 && a[i-2] <= a[i-1]
    Xét i = 1 thì phần âm sẽ là a[0], phần dương là a[i]->a[n-1] thì phần âm ko cần xét
    Tới i>=2 thì phần âm bắt đầu có 2 phần tử thì mới xét a[i-2] và a[i-1]. Nếu a[i-2] <= a[i-1] tức là sau khi đảo dấu có -a[i-2] >= -a[i-1] -> cần phải nhân a[i-2] lên k lần để nó nhỏ đi
    Duy trì cnt tại index 0 rồi dịch index 0->n-1 rồi tính lại cnt là xong. min(cnt) là đáp án
    */
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
/*
Đọc chậm rãi
Viết ra ý tưởng
The pattern from simple input to output.

TLE:
    map vs unordered_map ??
RE:
    binary search - INF ??
*/
