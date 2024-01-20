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
    vector<int> a(n);
    for (auto &v: a) {
        cin >> v;
        v--;
    }
    map<int, int> behind;
    for (int i=0;i<n;i++) {
        behind[a[i]] = i;
    }
    int cur = behind[-2];
    for (int i=0;i<n;i++) {
        cout << cur+1 << ' ';
        cur = behind[cur];
    }


    show_exec_time();
}
