# Algo practicing

## TODO 

### 1 loạt các bài dp
* [Paiza](https://paiza.jp/challenges/563/show)
* [Atcoder - 319F](https://atcoder.jp/contests/abc319/tasks/abc319_f)
* [Codeforces - F. Equidistant Vertices](https://codeforces.com/problemset/problem/1551/F)

**paiza**:
Mình đang không có hứng code bài dp trên nên tạm thời sẽ ghi lại các ý đang nghĩ:
* Observation: không có trường hợp ngủ 1,2 tiếng mà phải ngủ 3 tiếng, ngủ 1-2 tiếng rồi dậy thì năng lượng giữ nguyên -> vô nghĩa
* dp[time][số dòng code trong 1 giờ] trong đó time là thời gian đang xét - thể hiện có tối đa bao nhiêu dòng code tại thời điểm time, số dòng code trong 1 giờ khi đó là k
* dp[time][k] <= dp[time-3][k - s] - tại thời điểm time, code được k dòng được tính theo thời điểm time-3 code được k-s dòng

## Resources
* [Open katis](https://open.kattis.com/)
* [Cp algorithm](https://cp-algorithms.com/)
* [Cses](https://cses.fi/problemset/)
* [Usaco guide](https://usaco.guide/dashboard/)
* [Codeforces](https://codeforces.com/)
* [Atcoder](https://atcoder.jp/)
* [Timus](https://timus.online/)
