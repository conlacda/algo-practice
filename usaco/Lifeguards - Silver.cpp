// http://www.usaco.org/index.php?page=viewproblem2&cpid=786
#include<bits/stdc++.h>

typedef long long ll; // ld long double
const ll mod = 1000000007; // 998244353  1000000009  1000000007 // đừng dùng ull
#define int long long // __int128
const int INF = std::numeric_limits<int>::max(); // use INT32_MAX for i32

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
    #else
        freopen("lifeguards.in", "r", stdin);
        freopen("lifeguards.out", "w", stdout);
    #endif
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    int len = 0;
    for (auto& v: a) {
        cin >> v.first >> v.second;
        len = max(len, v.second-1);
    }
    sort(a.begin(), a.end());
    int _r = 1;
    for (auto v: a) {
        if (v.first > _r) len -= v.first - _r;
        _r = max(_r, v.second);
    }
    if (n == 1) {
        cout << 0;
        return 0;
    }
    int empty = a[1].first -1;
    /*
    Tai moi index lay max_right
    */
    int max_right = a[0].second;
    for (int i=1;i<n-1;i++) {
        if (a[i+1].first > a[i].second) {
            empty = min(empty, max((int) 0, a[i].second - max_right));
        } else {
            empty = min(empty, max((int) 0, a[i+1].first - max_right));
        }
        max_right = max(max_right, a[i].second);
    }
    if (a[n-1].first > max_right) {
        empty = min(empty, a[n-1].second - a[n-1].first);
    } else {
        empty = min(empty, max(a[n-1].second - max_right, (int) 0));
    }
    cout << len - empty;
    show_exec_time();
}
/*
Bài này trước tiên thực hiện thao tác tính các phần rỗng sẵn có.
    Sắp xếp rồi duyệt qua từng phần tử. Phần tử hiện tại nếu lớn hơn max_right đã qua thì tồn tại 1 khoảng trống
    Ví dụ: 1->4, 3->7, 8->9
    3->7 có 3 < max_right là 4 thì là overlap.
    8->9 có 8 > max_right là 7 => từ 7->8 có 1 khoảng trống
Số phần tử được lấp đầy hiện tại sẽ là len (max của toàn bộ pair.second) trừ đi empty

Tiếp theo là duyệt để tính xem 1 phần tử đó thiếu thì sẽ tạo ra thêm bao nhiêu khoảng trống.
Khoảng trống này chỉ xét khoảng trống nó giữ (khoảng trống bên ngoài đã được tính ở bên trên)
Xét 3 khoảng
1->4, 3->7, 5->9
Khoảng đầu tiên bỏ đi thì sẽ trống a[1].first - 1 là 2
Xét lần lượt i = 1 -> n-2 tại đây có 3->7
bỏ đi thì sẽ trống điểm đầu là 4. Điểm cuối là min(5, 7). Điểm cuối bản chất là 7.
Nhưng 1 phần range tiếp theo là 5->9 có chồng 1 đoạn 5->7 => min(5, 7)
Khi này trống sẽ là 4->5
a[n-1] thì cũng có 2 trường hợp.
Nếu range này biệt lập (a[n-1].first > max_right) thì nó tạo ra khoảng trống bằng toàn bộ nó = a[n-1].second - a[n-1].first
Nếu nó chồng lấn thì điểm trống ra sẽ là max_right -> a[n-1].second => gộp lại max(max_right, a[n-1].first) -> a[n-1].second
*/
