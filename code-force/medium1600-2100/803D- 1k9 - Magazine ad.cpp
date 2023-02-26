// https://codeforces.com/contest/803/problem/D
// Difficulty: 1900
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

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    /*
    String được tách tại dấu cách, dấu -
    tách được tối đa thành k đoạn
    độ dài nhỏ nhất đạt được là bao nhiêu
    -
    Bản chất - và space là như nhau
    -> chuyển thành mảng của các số [4,3,5,3,3,5,4,3,3]
    -> tách mảng này thành 4 mảng mà sum là nhỏ nhất
    -> min >= sum(arr)/k
    Binary search trên độ dài -> độ dài là x có ổn ko
    */
    int k;
    string s;
    std::getline (std::cin,s);
    k = stoi(s);
    std::getline (std::cin,s);
    dbg(k, s);
    // Chuyển về mảng
    vector<int> arr;
    int cnt = 0;
    for (int i=0;i<s.size();i++){
        if (s[i] == ' ' || s[i] == '-') {
            arr.push_back(cnt+1);
            cnt = 0;
        } else {
            cnt++;
        }
    }
    arr.push_back(cnt);
    dbg(arr);
    std::function<bool(int)> isGood = [&](int len){
        int sum = 0, cnt = 0;
        if (*max_element(arr.begin(), arr.end()) > len) return false;
        for (int i=0;i<arr.size();i++){
            if (sum + arr[i] > len) {
                cnt++;
                sum = arr[i];
            } else {
                sum += arr[i];
            }
        }
        cnt++;
        if (cnt <= k) return true;
        return false;
    };
    int left = 1;
    int right = (int) s.size();
    while (left < right -1) {
        int mid = (left + right) /2;
        if (isGood(mid)) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
    assert(isGood(left) || isGood(right));
    if (isGood(left)) {
        cout << left;
    } else cout << right;
    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
}
// Ghi chú lại technique này