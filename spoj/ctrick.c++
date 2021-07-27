/*
card trick
https://www.spoj.com/problems/CTRICK/
Thuật toán: 
N = 5 -> 3 1 4 5 2
Khởi tạo danh sách index cần điền 
0 1 2 3 4 -> index cần điền sẽ là 1 -> 4 -> 0 -> 2 -> 3
zero = 0 1 2 3 4
p = (0+1) % zero.size() -> 1 | xóa 1 đi zero sẽ còn 0 2 3 4 -> ans = 0 1 0 0 0
p = (1+2) % zero.size() = 3 | index tiếp theo sẽ là zero[3] -> ans = 0 1 0 0 2 | zero = 0 2 3
p = (3+3) % zero.size() = 0 | index tiếp theo là zero[0] -> ans = 3 1 0 0 2 | zero = 2 3
p = (0+4) % zero.size() = 0 | index tiếp theo là zero[0] -> ans = 3 1 4 0 2 | zero = 3
p = (0+5) % zero.size() = 0 | index tiếp là zero[0] -> ans = 3 1 4 5 2

Thuật toán đơn giản chỉ là duy trì 1 mảng các index cần điền. Nhảy k bước để tìm ra vị trí index tiếp theo
rồi điền vào index đó giá trị i
*/
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double

using namespace std;

void solve(){
    int N;
    cin >> N;
    vector<int> ans(N, 0);
    vector<int> zero;
    for (int i=0;i<N;i++){
        zero.push_back(i);
    }
    int p=0;
    for (int i=1;i<=N;i++){
        p = (p+i) % zero.size();
        int x = zero[p];
        ans[x] = i;
        zero.erase(zero.begin()+p);
    }
    for (auto v: ans) cout << v << ' '; cout << '\n';
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
    while (N--) solve();
}