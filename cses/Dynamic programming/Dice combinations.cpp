#include<bits/stdc++.h>
 
const int mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define int long long
 
using namespace std;
 
signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    Với sum = k, có thể xúc bằng sum=k-1 và xúc thêm 1, k-2 và xúc thêm 1 viên 2,... k-6 và xúc được 1 lần 6.
    ways[k] = ways[k-1] + ways[k-2] + ways[k-3] + ways[k-4] + ways[k-5] + ways[k-6]    
    */
    int n;
    cin >> n;
    // Pull DP
    // vector<int> ways(n+1, 0);
    // ways[0] =1; // initital state cho dp
    // for (int i=1;i<=n;i++) { // tính cho từng điểm k (ways[k])
    //     for (int dice = 1;dice<=6;dice++) { // ways[k] += ways[k-dice]
    //         ways[i] += (i-dice>= 0) ? ways[i-dice] : 0;
    //         ways[i] %= mod; 
    //     }
    // }
 
    // Push dp
    // Với mỗi giá trị k, ta có thể xúc thêm 1 xúc với giá trị 1->6. ways[i+dice] += ways[i]
    vector<int> ways(n+7, 0);
    ways[0] = 1;
    for (int i=0;i<=n;i++) {
        for (int dice = 1;dice <=6;dice++) {
            ways[i+dice] += ways[i];
            ways[i+dice] %= mod;
        }
    }
    cout << ways[n];
}
// https://cses.fi/problemset/task/1633
