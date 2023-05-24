/*
Tách thành các phần có đầu là B/E giữa là F, cuối là B/E
Tính cho 1 phần nhỏ đó thì có các trường hợp:
* BFF...B
* BFF...E
* BF..F
* EF..F
Mỗi khối sẽ có 1 khoảng giá trị -> giá trị cuối = min->max
BFF..B - đầu cuối giống nhau
BB -> 1
BFB -> 0, 2
BFFB -> 1, 3
BFFFB -> 0, 2, 4
Cùng F lẻ thì [0, F+1], F chẵn thì [1->F+1]
BFF...E - đầu cuối khác nhau
BE -> 0
BFE -> 1
BFFE -> 0, 2
BFFFE -> 1, 3
F lẻ -> [1->F], F chẵn thì [0->F]
BF -> 0, 1
BFF-> 0, 1, 2
BFFF -> 0, 1, 2, 3
E, B đầu cuối đều giống nhau
[0,1,..F]
nếu có đầu cắt đuôi thì nó chạy từ đầu tới cuối
ko thì chạy nhảy bậc 2
FFF..FF
FF -> 0, 1
FFF->0,1,2
[0->F-1]
*/
#include<bits/stdc++.h>

typedef long long ll;
using uint = unsigned int;
using ull = unsigned long long;
const ull mod = 1e9 + 7; // 998244353  1000000009  1000000007
#define ld long double

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#define show_exec_time()
#define destructure(a) #a
#endif

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    int n;
    cin >> n;
    string s;
    cin >> s;
    /*
    Tách string ban đầu thành các string nhỏ hơn theo pattern
    Xử lý từng string nhỏ đó, tính luôn min, max
    in ra từ min->max, nếu có đuôi/đầu là F thì in liền mạch
    không thì cách quãng 2
    */
    int _min = 0, _max = 0;
    int step = 2;
    string sub = "";
    std::function<void(string)> cal = [&](string sub){
        if (sub.size() < 1) return 0;
        int f = count(sub.begin(), sub.end(), 'F');
        // Full F
        if (sub[0] == sub[sub.size()-1] && sub[0] == 'F') {
            _max += f-1;
            step = 1;
            return 0;
        }
        // 1 phần F [0->F] BF..F
        if ((sub[0] != 'F' && sub[sub.size()-1] == 'F') || (sub[0] == 'F' && sub[sub.size()-1] != 'F')) {
            _max += f;
            step = 1;
            return 0;
        }
        // BFFB - F lẻ thì từ 0->F+1, F chẵn 1->F+1
        if (sub[0] == sub[sub.size() -1]) {
            _max += f+1;
            if (f%2== 0) _min +=1;
            return 0;
        }
        // F lẻ -> 1->F, chẵn 0->F
        _max += f;
        _min += (f%2);
    };
    for (auto v: s) {
        sub += v;
        if (sub.size() >1 && v != 'F') {
            cal(sub);
            sub = sub.substr(sub.size() -1);
        }
    }
    if (sub.size() > 1) {
        cal(sub);
    }
    dbg(_min, _max, step);
    cout << (_max - _min) / step + 1<< '\n';
    for (int i=_min;i<=_max;i+=step) {
        cout << i <<'\n';
    }
    show_exec_time();
}
// http://www.usaco.org/index.php?page=viewproblem2&cpid=1323
