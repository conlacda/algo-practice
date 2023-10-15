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

// Reference: https://www.geeksforgeeks.org/templates-cpp/
template<class U>
class Counter{
    public:
        map<U, int> data = {};
        template <typename T>
        Counter(T val){
            for (auto v: val){
                data[v]++;  
            }
            // for (auto v: data) cout << v.first<< ' ' << v.second << '\n';
        }
};
/*
string s ="hello";
Counter<char> x(s);
vector<int> a{1,2,3,4};
Counter<int> z(a);
for (auto v: x.data) cout << v.first << ' '<< v.second<<'\n';
*/
void solve() {
    string s;
    cin >> s;
    Counter<char> c(s);
    dbg(c.data);
    int cnt = 0;
    for (auto v: c.data) {
        if (v.second >=2) cnt++;
    }
    if (cnt >=2) cout << "YES\n";
    else cout << "NO\n";
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    while (n--) solve();
    
    show_exec_time();
}
