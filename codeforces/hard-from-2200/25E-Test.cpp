// https://codeforces.com/contest/25/submission/195569890
// https://codeforces.com/contest/25/problem/E
#include <bits/stdc++.h>

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef DEBUG
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s1, s2, s3;
    Hash<string> hash;
    hash.build();
    // while (cin >> s1){
    cin >> s1 >> s2 >> s3;
    auto two_string = [&](string a, string b) -> string {
        Hash<string> ha = hash;
        ha.load(a);
        Hash<string> hb = hash;
        hb.load(b);
        ll ans = 0;
        for (ll i = min(a.size(), b.size()); i > 0; i--) {
            if (ha.substr(a.size() - i, i) == hb.substr(0, i)) {
                ans = i;
                break;
            }
        }
        return a + b.substr(min(ans, (ll)b.size()));
    };
    auto cal = [&](string s1, string s2, string s3) -> ll {
        return min(two_string(s1, two_string(s2, s3)).size(),
                   two_string(two_string(s1, s2), s3).size());
    };
    ll ans = LLONG_MAX;
    ans = min(ans, cal(s1, s2, s3));
    ans = min(ans, cal(s1, s3, s2));
    ans = min(ans, cal(s2, s1, s3));
    ans = min(ans, cal(s2, s3, s1));
    ans = min(ans, cal(s3, s2, s1));
    ans = min(ans, cal(s3, s1, s2));
    cout << ans;
    // }
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Sometimes it is hard to prepare tests for programming problems. Now Bob is preparing tests to new problem about strings — input data to his problem is one string. Bob has 3 wrong solutions to this problem. The first gives the wrong answer if the input data contains the substring s1, the second enters an infinite loop if the input data contains the substring s2, and the third requires too much memory if the input data contains the substring s3. Bob wants these solutions to fail single test. What is the minimal length of test, which couldn't be passed by all three Bob's solutions?

Input
There are exactly 3 lines in the input data. The i-th line contains string si. All the strings are non-empty, consists of lowercase Latin letters, the length of each string doesn't exceed 105.

Output
Output one number — what is minimal length of the string, containing s1, s2 and s3 as substrings.

Examples
input
ab
bc
cd
output
4

input
abacaba
abaaba
x
output
11
*/
