// https://codeforces.com/contest/25/problem/E
// https://codeforces.com/contest/25/my
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

<hash-string without changing any things>

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
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
