// [Atcoder|Codeforces].abcxxx.F
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

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
    int n;
    cin >> n;
    /*
    Kiểm tra xem có bất kỳ cái nào giao nhau không.
    Dùng 1 cái map để nối điểm đầu tới điểm cuối
        1 cái set để lưu những vị trí không được vượt qua
    */
    vector<pair<int,int>> a;
    for (int i=0;i<n;i++) {
        int l, r;
        cin >> l >> r;
        if (l > r) swap(l, r);
        l--; r--;
        a.push_back({l, r});
    }
    dbg(a);
    map<int, int> endOf;
    set<int> s;
    for (auto v: a) {
        endOf[v.first] = v.second;
    }
    dbg(endOf);
    for (int i=0;i<2*n;i++) {
        if (endOf.find(i) != endOf.end()) {
            if ((int) s.size() != 0 && endOf[i] > *s.begin()) {
                dbg(i, s, endOf[i]);
                cout << "Yes";
                return 0;
            }
            s.insert(endOf[i]);    
        }
        if (s.find(i) != s.end()) {
            s.erase(i);
        }
        // dbg(i, s, endOf);
    }
    cout << "No";
    show_exec_time();
}
