// https://codeforces.com/contest/1056/problem/E
// 
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif
<hash-string without changing anything>
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string t, s;
    cin >> t >> s;
    /*
    Dùng hash 1 cách thô bỉ để đếm
    */
    ll zero = 0, one = 0;
    for (auto v: t) {
        if (v == '0') {
            zero++;
        } else one++;
    }
    ll ans = 0;
    Hash<string> hash; hash.build(s.size());
    hash.load(s);

    std::function<bool(int, int)> check = [&](int a, int b){
        int cur = 0;
        ll hone = -1, hzero = -1;
        for (auto v: t){
            if (v == '0'){
                if (hzero == -1){
                    hzero = hash.substr(cur, a);
                } else {
                    if (hzero != hash.substr(cur, a)){
                        return false;
                    }
                }
                cur += a;
            } else {
                // v == 1
                if (hone == -1){
                    hone = hash.substr(cur, b);
                } else {
                    if (hone != hash.substr(cur, b)){
                        return false;
                    }
                }
                cur += b;
            }
        }
        dbg(hone, hzero);
        if (hzero == hone) return false;
        return true;
    };
    for (int i=1;i<=s.size()/zero;i++){
        // s.size = i*zero + j*one;
        if ((s.size() - i*zero) % one !=0) continue;
        int j = (s.size() - i*zero) / one;
        if (j == 0) continue;
        if (check(i, j)) {
            ans++;
            dbg(i, j);
        }
    }
    cout << ans;
    /*
    Bài này chỉ đơn giản bruteforce với độ dài của 0 và độ dài của 1
    Xét độ dài của 0 là i, của 1 là j
    thế thì 0_num * i + 1_num *j == s.size()
    Với mỗi i ta tính ra j rồi dùng check(i, j) xem như thế có thỏa mãn không.
    */
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
