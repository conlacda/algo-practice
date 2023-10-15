#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
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

void solve(){
    /*
    Tim kich thuoc lon nhat cua b la subsequence cua a.
    co f(b) = f(a)
    Bo so bang nhau di
    Bo so dang len lien tuc di
    Bo so xuong lien tuc di
    Dang khuc khuyu thi 2 lan so o giua se them vao hay mat di.
    */
    int n; cin >> n;
    vector<int> a(n);
    for (auto& v: a) cin >> v;
    vector<int> _a;
    _a.push_back(a[0]);
    for (int i=1;i<n;i++) {
        if (a[i] != a[i-1]) _a.push_back(a[i]);
    }
    a = _a;
    vector<bool> rm((int) a.size(), false);
    _a = {};
    n = (int) a.size();
    for (int i=1;i<n-1;i++) {
        if (a[i-1] < a[i] && a[i] < a[i+1]) rm[i] = true;
        if (a[i-1] > a[i] && a[i] > a[i+1]) rm[i] = true;
    }
    for (int i=0;i<(int) a.size();i++) {
        if (!rm[i]) _a.push_back(a[i]);
    }
    dbg(_a);
    cout<< _a.size() <<'\n';
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n; cin >> n;
    while (n--) solve();
    
    show_exec_time();
}
