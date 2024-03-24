// https://atcoder.jp/contests/abc346/tasks/abc346_e
#include<bits/stdc++.h>

#define int long long // __int128

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
    int h, w, n;
    cin >> h >> w >> n;
    vector<tuple<int, int, int>> a;
    for (int i=0;i<n;i++) {
        int t, rc, color;
        cin >> t >> rc >> color;
        a.push_back({t, --rc, color});
    }
    reverse(a.begin(), a.end());
    dbg(a);
    /*
    1 ô sẽ có màu phụ thuộc vào thao tác cuối cùng áp lên nó
    Lật ngược lại toàn bộ thao tác. Khi này 1 màu đã được tô sẽ không bị đổi màu
    do các thao tác trước đó.
    Xét theo thao tác ngược này ta sẽ tính được số lượng ô sẽ bị đổi màu tại thao tác đó
    */
    map<int, int> m;
    set<int> r, c;
    for (auto [t, rc, color]: a) {
        if (t == 1) {
            // row
            if (r.contains(rc)) continue;
            m[color] += w - (int) c.size();
            r.insert(rc);
        } else {
            // col
            if (c.contains(rc)) continue;
            m[color] += h - (int) r.size();
            c.insert(rc);
        }
    }
    int zero = h * w;
    for (auto v: m) {
        if (v.first != 0)
            zero -= v.second;
    }
    m[0] = zero;
    int cnt = 0;
    for (auto [color, num]: m) {
        if (num != 0) cnt++;
    }
    cout << cnt << '\n';
    for (auto [color, num]: m)
        if (num != 0)
            cout << color << ' ' << num << '\n';
    show_exec_time();
}
