https://atcoder.jp/contests/abc306/tasks/abc306_g
Bài này mình không làm mà chỉ suy nghĩ rồi ghi lại suy nghĩ ra đây
Hiện tại mình có làm thì nó cũng mất thời gian mà rank cũng 
sẽ không tăng vì nếu gặp bài mức này mình cũng ko thể nghĩ nhanh được

Giả sử đi từ 1 rồi quay về 1. Tưởng tượng nó có 1 cái vòng tròn to 
1->2->3->4->5->1

Tại vòng tròn này xuất hiện vài vòng tròn nhỏ 
2->3->6->2

4->5->7->8->4

Khi này 1 vòng tròn to sẽ có 2 vòng tròn nhỏ ở giữa nó.

Mình sẽ tính được độ dài 2 vòng tròn nhỏ khi DFS duyệt nó quay lại - dùng clock để tính thời điểm bắt đầu đi tới khi quay lại

Giả sử có 2 độ dài cycle đó là a, b

Ta có extended euclid: ax+by= gcd(a, b) luôn có nghiệm x, y

Với a, b nguyên tố cùng nhau thì chắc chắn ra Yes.
a b không nguyên tố cùng nhau thì có nghiệm gcd(a, b) = k.
-> ax+by= 10^10^1000. Khi này 10^10^1000 phải chia hết cho k.
Dễ dàng nhận ra nếu k chia hết cho 2, 5 hoàn toàn thì sẽ Yes.
k chia hết cho số ngoài 2, 5 thì sẽ No vì 10^10^1000 không thể chia hết. 1 vế chia hết k = 1 vế ko chia hết cho k sẽ ko có nghiệm
