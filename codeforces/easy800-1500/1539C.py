from math import ceil
n, add, diff = [int(i) for i in input().split()]
a = [int(i) for i in input().split()]
a.sort()
dis = []
for i in range(1, len(a)):
    if a[i] - a[i-1] > diff:
        dis.append((a[i] -a[i-1]-1)//diff) # ính luôn số lượng số cần lấp đầy khoảng cách này

ans = len(dis)+1
dis.sort()
for it in dis:
    if it <= add:
        ans -=1
        add -= it
        if add <=0:
            break
    
print(ans)
"""
bài này cho 1 dãy số a[]
dãy số stable là khi sắp xếp, 2 số cạnh nhau ko lệch quá diff đơn vị.
Từ dãy số a[], thêm k số bất kì vào a để a tạo ra số dãy stable ít nhất
Ví dụ a = [1,4,7, 15, 21] với diff = 4 thì có 3 dãy stable là [1,4,7] [15] , [21]
Thêm số 11 vào thì sẽ chỉ còn 2 dãy [1,4,7,15] , [21]
Cho a,k, diff. Đưa ra số dãy stable ít nhất
Thuật toán:
* Sắp xếp dãy a
* Duyệt a, nếu 2 số cạnh nhau cách nhau quá diff (ko thuộc cùng 1 stable arr) thì thêm a[i]-a[i-1] vào distance[]
* Sắp xếp distance. Duyệt từng phần tử, nếu lấp đầy distance đó cần 1 số lượng số <= k thì trừ k đi 1 đồng thời số stable arr cũng giảm đi 1
"""