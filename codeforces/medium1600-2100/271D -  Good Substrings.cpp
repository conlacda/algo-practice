// https://codeforces.com/contest/271/problem/D
// Submission: https://codeforces.com/contest/271/my
/*
You've got string s, consisting of small English letters. Some of the English letters are good, the rest are bad.

A substring s[l...r] (1 ≤ l ≤ r ≤ |s|) of string s  =  s1s2...s|s| (where |s| is the length of string s) is string  slsl + 1...sr.

The substring s[l...r] is good, if among the letters  sl, sl + 1, ..., sr there are at most k bad ones (look at the sample's explanation to understand it more clear).

Your task is to find the number of distinct good substrings of the given string s. Two substrings s[x...y] and s[p...q] are considered distinct if their content is different, i.e. s[x...y] ≠ s[p...q].

Input
The first line of the input is the non-empty string s, consisting of small English letters, the string's length is at most 1500 characters.

The second line of the input is the string of characters "0" and "1", the length is exactly 26 characters. If the i-th character of this string equals "1", then the i-th English letter is good, otherwise it's bad. That is, the first character of this string corresponds to letter "a", the second one corresponds to letter "b" and so on.

The third line of the input consists a single integer k (0 ≤ k ≤ |s|) — the maximum acceptable number of bad characters in a good substring.

Output
Print a single integer — the number of distinct good substrings of string s.

Examples
input
ababab
01000000000000000000000000
1
output
5
inputCopy
acbacbacaa
00000000000000000000000000
2
outputCopy
8
Note
In the first example there are following good substrings: "a", "ab", "b", "ba", "bab".

In the second example there are following good substrings: "a", "aa", "ac", "b", "ba", "c", "ca", "cb".
*/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define destructure(a) #a
#endif

<hash-string without any changes>

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    string s; cin >> s;
    string ap; cin >> ap;
    map<char, int> m;
    for (int i=0;i<ap.size();i++){
        m['a' + i] = ap[i] - '0'; 
    }
    int k; cin >> k;
    std::unordered_map<ll, bool> hashed;
    int i=0, j =0;
    int bad = 0;
    Hash<string> hash;
    hash.build(s.size());
    hash.load(s);
    // Dùng 2 pointer để đếm số bad chars
    while (i<s.size()){
        if (m[s[i]] == 0) bad++;
        while (bad > k){
            if (m[s[j]] == 0) bad--;
            j++;
        }
        for (int z=j;z<=i;z++){
            hashed[hash.substr(z, i-z+1)] = true;
        }
        i++;
    }
    cout << hashed.size();
}
