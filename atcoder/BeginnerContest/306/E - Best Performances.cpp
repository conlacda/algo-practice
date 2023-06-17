// https://atcoder.jp/contests/abc306/tasks/abc306_e
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1000000007; // 998244353  1000000009  1000000007
#define ld long double
#define int long long
// const int INF = std::numeric_limits<int>::max();

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
    int n, k, q;
    cin >> n >> k >> q;
    /*
    Dùng 2 muliple set để lưu trữ selected và unselected
    Thay thế giá trị có các thao tác:
    * Nếu giá trị đó nằm trong selected
        * Nếu không thì xóa trong unselected
    * xóa tại đâu thì thêm giá trị mới tại đó
    * trao đổi 2 giá trị lớn nhất, nhỏ nhất của 2 tập cho nhau
    * Tính lại sum
    */
    vector<int> a(n, 0);
    multiset<int> selected, unselected;
    for (int i=0;i<k;i++) selected.insert(0);
    for (int i=0;i<n-k;i++) unselected.insert(0);
    if (unselected.size() == 0) unselected.insert(-1); // chống việc k = n làm unselected rỗng, khi này unselected chạy các hàm sẽ bị RE
    int cursum = 0;
    for (int i=0;i<q;i++) {
        int index, val;
        cin >> index >> val;
        index--;
        int oldval = a[index];
        if (selected.find(oldval) != selected.end()) {
            selected.erase(selected.find(oldval));
            selected.insert(val);
            cursum = cursum - oldval + val;
        } else {
            unselected.erase(unselected.find(oldval));
            unselected.insert(val);
        }
        if (*selected.begin() < *prev(unselected.end())) {
            int s = *selected.begin();
            selected.erase(selected.begin());
            int u = *unselected.rbegin();
            unselected.erase(prev(unselected.end()));
            selected.insert(u);
            unselected.insert(s);
            cursum = cursum - s + u;
        }
        a[index] = val;
        cout << cursum<<'\n';
    }
    show_exec_time();
}
