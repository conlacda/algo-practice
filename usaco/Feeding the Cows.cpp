// Feeding the Cows
// http://www.usaco.org/index.php?page=viewproblem2&cpid=1252
#include<bits/stdc++.h>

typedef long long ll;
const ll mod = 1e9 + 7;
#define ld long double
#define int long long

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
    /*
    Cho 1 string s gồm G,H
    G,H có thể di chuyển tối đa k bước.
    Tìm xem trồng cỏ ở đâu để mọi con đều ăn được nhưng trồng ít nhất.
    1 điểm mà 2 con H với tới (điểm giữa) thì có trọng số cao hơn.
    Dựa vào khoảng cách tăng trọng số của nó lên. 
    HGHGH
    Tại điểm i=3 (giữa) thì trọng số = 2+2+0.
    Thế thì có thể tìm cho con H trước rồi mới tìm cho con G.
    Bắt đầu từ con H ngoài cùng, đám cỏ sẽ được đặt cách nó k đơn vị.
    Greedy algorithm??
    */
    int _;
    cin >> _;
    while (_--) {
        int n; cin >> n;
        int k; cin >> k;
        string s; cin >> s;
        string ans = "";
        for (int i=0;i<n;i++) {
            ans+='.';
        }
        // xu ly cho H, G, tai 1 diem ko bi bao phu, lay diem xa nhat
        int curH = -k-1;
        int curG = -k-1;
        int cnt = 0;
        /*
        Nếu nó được bao phủ thì bỏ qua
        Nếu nó chưa được bao phủ
            Lấy điểm xa nhất, nếu điểm xa nhất đã có thì dịch dần giá trị ngược về
        */
        for (int i=0;i<n;i++) {
            if (s[i] == 'H') {
                if (curH + k < i) {
                    // ko cover
                    curH = i+k;
                    if (curH >=n) curH = n-1;
                    while (ans[curH] == 'G') curH--;
                    cnt++;
                    ans[curH] = 'H';
                }
            } else if (s[i] == 'G') {
                if (curG + k < i) {
                    // ko cover
                    curG = i+k;
                    if (curG >=n) curG = n-1;
                    while (ans[curG] == 'H') curG--;
                    cnt++;
                    ans.at(curG) = 'G';
                }
            }
            dbg(i, ans);
        }
        cout << cnt <<'\n';
        cout << ans <<'\n';
    }
    
    show_exec_time();
}
