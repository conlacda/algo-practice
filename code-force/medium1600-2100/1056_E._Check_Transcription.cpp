// https://codeforces.com/contest/1056/problem/E
// https://codeforces.com/contest/1056/submission/195570323
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

<hash-string.snippet>
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
    dbg(zero, one);
    ll ans = 0;
    Hash<string> hash; hash.build(s.size());
    hash.load(s);

    std::function<bool(int, int)> check = [&](int a, int b){
        int cur = 0;
        pair<ll, ll> hone = {-1, -1}, hzero = {-1, -1};
        for (auto v: t){
            if (v == '0'){
                if (hzero.first == -1){
                    hzero = hash.substr(cur, a);
                } else {
                    if (hzero != hash.substr(cur, a)){
                        return false;
                    }
                }
                cur += a;
            } else {
                // v == 1
                if (hone.first == -1){
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
        if (hzero.first == hone.first && hzero.second == hone.second) return false;
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

/*
One of Arkady's friends works at a huge radio telescope. A few decades ago the telescope has sent a signal s towards a faraway galaxy. Recently they've received a response t which they believe to be a response from aliens! The scientists now want to check if the signal t is similar to s.
The original signal s was a sequence of zeros and ones (everyone knows that binary code is the universe-wide language). The returned signal t, however, does not look as easy as s, but the scientists don't give up! They represented t as a sequence of English letters and say that t is similar to s if you can replace all zeros in s with some string r0 and all ones in s with some other string r1 and obtain t. The strings r0 and r1 must be different and non-empty.
Please help Arkady's friend and find the number of possible replacements for zeros and ones (the number of pairs of strings r0 and r1) that transform s to t.
Input
The first line contains a string s (2≤|s|≤105) consisting of zeros and ones — the original signal.
The second line contains a string t (1≤|t|≤106) consisting of lowercase English letters only — the received signal.
It is guaranteed, that the string s contains at least one '0' and at least one '1'.
Output
Print a single integer — the number of pairs of strings r0 and r1 that transform s to t.
In case there are no such pairs, print 0.
Examples
input
01
aaaaaa
output
4
input
001
kokokokotlin
output
2
Note
In the first example, the possible pairs (r0,r1) are as follows:
"a", "aaaaa"
"aa", "aaaa"
"aaaa", "aa"
"aaaaa", "a"
The pair "aaa", "aaa" is not allowed, since r0 and r1 must be different.
In the second example, the following pairs are possible:
"ko", "kokotlin"
"koko", "tlin"
*/
