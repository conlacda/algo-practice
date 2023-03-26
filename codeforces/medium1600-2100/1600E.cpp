// https://codeforces.com/contest/1600/submission/133457720
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

int _count(vector<int> a, bool re = false){
    if (re) {
        reverse(a.begin(), a.end());
    }
    int ans =1;
    for (int i=1;i<a.size();i++){
        if (a[i] > a[i-1]) ans++;
        else break;
    }
    return ans;
}

int cl;
int cr;
vector<int> a;
int solve(int l, int r, int player, int _min, int _cl, int _cr){
    // cout << l << ' ' << r <<' '<<player << ' '<< _min << ' '<< _cr<<' '<< _cl<<'\n';
    if (a[l] <= _min && a[r] <= _min) return 1-player;
    if (a[l] <= _min && a[r] > _min) {
        if (_cr %2 ==1) return player; else return 1-player;
    }
    if (a[r] <= _min && a[l] > _min){
        if (_cl %2 == 1) return player; else return 1-player;
    }
    if (l==r) return player;
    if (a[l] <= a[r] && _cr %2 ==1) return player;
    if (a[l] >= a[r] && _cl %2 ==1) return player;
    if (a[l] <= a[r] && a[l] <= _min) return 1-player;
    if (a[r] >= a[l] && a[r] <= _min) return 1-player;
    if (a[l] <= a[r]) return solve(l+1, r, 1-player, a[l], _cl-1, _cr);
    else return solve(l, r-1, 1-player, a[r], _cl, _cr-1);
}
/*
Thay lai tham so trong ham solve() thay vi truyen vector<int> a thi chi lay a[l] va a[r] thoi
*/
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    
    int N;
    cin >> N;
    a.resize(N);
    for (int i=0;i<N;i++) cin >> a[i];
    cl = _count(a);
    cr = _count(a, true);
    if (solve(0, a.size()-1, 0, -1, cl, cr) == 0) {
        cout << "Alice";
    } else cout << "Bob";
}