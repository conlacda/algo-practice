// http://www.usaco.org/index.php?page=viewproblem2&cpid=741
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

<hash-string-without-changes>

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        ifstream cin("cownomics.in");
        ofstream cout("cownomics.out");
    #endif
/*
Yêu cầu bài toán. 
Tìm ra range [l-r] sao cho đoạn từ l-r của phần trên và phần dưới không trùng nhau
Check lần lượt từ trái qua phải
Tại mỗi index tính xem giá trị tối thiểu tại đó là bao nhiêu
*/
    int n, m;
    cin >> n >> m;
    vector<string> spot(n), nospot(n);
    string spot_string = "", nospot_string = "";
    for (int i=0;i<n;i++) {
        cin >> spot[i];
        spot_string += spot[i];
    }
    for (int i=0;i<n;i++) {
        cin >> nospot[i];
        nospot_string += nospot[i];
    }
    Hash<string> hash;
    hash.build(spot_string.size());
    Hash<string> hspot = hash;
    Hash<string> hnospot = hash;
    hspot.load(spot_string);
    hnospot.load(nospot_string);
    std::function<bool(int, int)> check = [&](int index, int len){
        // Kiểm tra xem index và len này có được không
        unordered_map<ll, bool> um;        
        // Kiểm tra xem đoạn này có được không
        /*Dùng binary search để xem 
        Nếu index to được thì giảm đi 1 nửa*/
        for (int i=0;i<n;i++){
            um[hspot.substr(index + i*m, len)] = true;
        }
        for (int i=0;i<n;i++){
            if (um.find(hnospot.substr(index + i*m, len)) != um.end()){
                return false;
            }
        }
        return true;
    };
    int ans = INT_MAX;
    for (int i=0;i<m;i++){
        // Tìm ra giá trị phù hợp
        int left = 1, right = m-i;
        while (left < right-1){
            int mid = (left + right) /2;
            if (!check(i, mid)){
                left = mid + 1;
            } else right = mid;
        }
        if (check(i, left)){
            ans = min(ans, left);
        } else if (check(i, right)){
            ans = min(ans, right);
        }
    }
    cout << ans;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
/*
Problem: http://www.usaco.org/index.php?page=viewproblem2&cpid=741
Bài này cần tìm ra range [l:r] sao cho các đoạn từ [l:r] của các string có spot và
các string không có spot không có string nào trùng nhau
Ví dụ:
3 8
AATCCCAT
ACTTGCAA
GGTCGCAA
ACTCCCAG
ACTCGCAT
ACTTCCAT

Xét bất kỳ 1 đoạn string độ dài 3 nào thì 3 string trên và 3 string dưới luôn trùng nhau
Ví dụ: l=0, r=2 -> trùng ACT
       l=1, r=3 -> trùng CTT
       l=2, r=4 -> trùng TCC
       l=3, r=5 -> trùng CGC
       ...
Với độ dài = 4 thì đoạn l=1, r = 4 là không trùng nhau -> kết quả là 4
( [ATCC,CTTG,GTCG] x [CTCC, CTCG, CTTC] = {}  x là giao nhau/intersect)
Ban đầu mình tính với mỗi index tìm ra độ dài tối thiểu cần để nó ko intersect là bao nhiêu
Tăng dần length lên, đạt thì dừng và cập nhật ans = min(ans, result)
Nhưng với cách này với mỗi index O(N) sẽ có length = 1->N là N^2 phép kiểm tra
-> Tối ưu:
Dễ nhận thấy nếu với (index, len) thỏa mãn điều kiện thì (index, s.size()) cũng thỏa mãn điều kiện
Nghĩa là nếu index =1 và độ dài trên kia là 4 thỏa mãn thì index =1 và độ dài >4 cũng thỏa mãn
-> Dùng binary search để tìm. left = 1, right = m-i. Khi này kiểm tra mid có thỏa mãn hay không để điều chỉnh lại left, right  

Nói ngắn gọn:
Với mỗi index (O(N))ta dùng binary search để tìm ra len thỏa mãn (O(logN))
-> độ phức tạp O(NlogN)
*/
