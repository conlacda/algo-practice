#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

void test_case(){
    int n,m,k;
    cin >> n>>m>>k;
    vector<vector<char>> table (n, vector<char>(m, '0'));
    int horizontal=0;
    if (n%2==1) horizontal = m/2;
    int max_h = n*(m/2);
    if (max_h < k) cout <<"NO\n"; else
    if (k>=horizontal && (k-horizontal)%2==0){
        cout <<"YES\n";
    } else cout << "NO\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int N;
    cin >> N;
    while (N--){
        test_case();
    }
}