/*
Date: 2022-10-23
LANG: C++
TASK: friday
*/

#include<bits/stdc++.h>

typedef long long ll;

using namespace std;

#ifdef DEBUG
#include "debug.cpp"
#else
#define dbg(...)
#endif


int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    #ifdef DEBUG
        freopen("inp.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #else
        ofstream cout("friday.out");
        ifstream cin("friday.in");
    #endif
    /*
    Bắt đầu từ 1/1/1900 - thứ 2 - 13 -> thứ 7
    Các tháng thì có số ngày theo quy định
    Có N năm
    Tính xem qua N năm đó ngày 13 rơi vào thứ nào
    */
    int n; cin >> n;
    unordered_map<int, int> ans;
    ans[0] = 0;
    ans[1] = 0;
    ans[2] = 0;
    ans[3] = 0;
    ans[4] = 0;
    ans[5] = 0;
    ans[6] = 0;
    /*
    Từ ngày 13 tháng này tìm tới ngày 13 tháng sau
    */
    std::function<int(int, int, int)> next = [&](int year, int month, int dayofweek){
        // Từ ngày 13 tháng này tìm tới ngày 13 tháng sau với năm
        // Trả về thứ trong tuần của ngày 13 tháng sau
        bool is_leap = false;
        if (year % 4==0){
            if (year % 400 == 0) is_leap = true;
            else {
                if (year %100 != 0) is_leap = true;
            }
        }
        // dbg(year, is_leap);
        int daynum = 0;
        vector<int> d = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    
        if (is_leap && month == 2) {
            daynum = 29;
        } else {
            daynum = d[month - 1];
        }
        dayofweek = (dayofweek + daynum) % 7;
        return dayofweek;
    };
    ans[5] = 1;
    int year = 1900;
    int month = 1;
    int dayofweek = 5;
    while (year <= 1900-1+n){
        int new_dayofweek = next(year, month, dayofweek);
        dayofweek = new_dayofweek;
        month++;
        if (month > 12){
            month = 1;
            year++;
        }
        if (year <= 1900-1+n) ans[new_dayofweek]++;
    }
    cout << ans[5] << ' ';
    cout << ans[6] << ' ';
    cout << ans[0] << ' ';
    cout << ans[1] << ' ';
    cout << ans[2] << ' ';
    cout << ans[3] << ' ';
    cout << ans[4] << endl;

    cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n";
    return 0;
}