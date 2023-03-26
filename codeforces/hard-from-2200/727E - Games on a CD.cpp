// https://codeforces.com/contest/727/submission/195569516
// https://codeforces.com/contest/727/problem/E
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
    ll n, k;
    cin >> n >> k;
    n = n * k;
    string s;
    cin >> s;
    ll q;
    cin >> q;
    Hash<string> hash;
    hash.build(s.size() + 5);
    hash.load(s);
    unordered_map<pair<ll, ll>, ll, IntPairHash> m; // hash value to index

    for (ll i = 0; i < q; i++) {
        string sub;
        cin >> sub;
        m[hash.hash(sub)] = i + 1;
    }
    dbg(m);
    for (ll i = 0; i < k; i++) {
        ll end = (i + k >= n) ? (i + k - n - 1) : (i + k - 1);
        if (m.find(hash.substr(i, k)) == m.end()) {
            continue;
        }
        vector<ll> check; // chứa index
        check.push_back(m[hash.substr(i, k)]);
        ll start = i + k;
        if (start >= n)
            start -= n;
        while (start != i) {
            ll end = (start + k >= n) ? (start + k - n - 1) : (start + k - 1);
            if (m.find(hash.substr(start, k)) != m.end()) {
                check.push_back(m[hash.substr(start, k)]);
                start += k;
                if (start >= n)
                    start -= n;
            } else
                break;
        }
        if (start == i) {
            unordered_set<ll> sc(check.begin(), check.end());
            if (sc.size() == check.size()) {
                cout << "YES\n";
                for (auto v : check) {
                    cout << v << ' ';
                }
                return 0;
            }
        }
    }
    cout << "NO\n";

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Several years ago Tolya had n computer games and at some point of time he decided to burn them to CD. After that he wrote down the names of the games one after another in a circle on the CD in clockwise order. The names were distinct, the length of each name was equal to k. The names didn't overlap.

Thus, there is a cyclic string of length n·k written on the CD.

Several years have passed and now Tolya can't remember which games he burned to his CD. He knows that there were g popular games that days. All of the games he burned were among these g games, and no game was burned more than once.

You have to restore any valid list of games Tolya could burn to the CD several years ago.

Input
The first line of the input contains two positive integers n and k (1 ≤ n ≤ 105, 1 ≤ k ≤ 105) — the amount of games Tolya burned to the CD, and the length of each of the names.

The second line of the input contains one string consisting of lowercase English letters — the string Tolya wrote on the CD, split in arbitrary place. The length of the string is n·k. It is guaranteed that the length is not greater than 106.

The third line of the input contains one positive integer g (n ≤ g ≤ 105) — the amount of popular games that could be written on the CD. It is guaranteed that the total length of names of all popular games is not greater than 2·106.

Each of the next g lines contains a single string — the name of some popular game. Each name consists of lowercase English letters and has length k. It is guaranteed that the names are distinct.

Output
If there is no answer, print "NO" (without quotes).

Otherwise, print two lines. In the first line print "YES" (without quotes). In the second line, print n integers — the games which names were written on the CD. You should print games in the order they could have been written on the CD, it means, in clockwise order. You can print games starting from any position. Remember, that no game was burned to the CD more than once. If there are several possible answers, print any of them.
input
3 1
abc
4
b
a
c
d
output
YES
2 1 3 

input
4 2
aabbccdd
4
dd
ab
bc
cd
output
NO
*/
