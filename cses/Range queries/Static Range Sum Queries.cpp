// https://cses.fi/problemset/task/1646/
#include<bits/stdc++.h>
 
typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
 
using namespace std;
 
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N, Q;
    cin >> N >> Q;
    vector<ll> a{0};
    ll sum =0;
    for (int i=0;i<N;i++){
        int x; cin >> x;
        sum +=x;
        a.push_back(sum);
    }
    // for (auto v: a) cout << v<< ' '; cout << '\n';
    while (Q--){
        int i, j;
        cin >> i>>j;
        cout << a[j]-a[i-1]<<'\n';
    }
}
