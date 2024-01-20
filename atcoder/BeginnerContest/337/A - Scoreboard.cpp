#include<bits/stdc++.h>

typedef long long ll; 
const ll mod = 1000000007; 
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
    int n;
    cin >> n;
    int t1 = 0, t2 = 0;
    while (n--) {
        int l, r;
        cin >> l >> r;
        t1 += l;
        t2 += r;
    }

if (t1 > t2) {
    cout << "Takahashi";
} else if (t1 == t2) {
    cout << "Draw";
} else cout << "Aoki";

    show_exec_time();
}
