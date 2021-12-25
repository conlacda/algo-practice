# Div 3: https://codeforces.com/problemset/problem/1538/C
# cho a, l,r. Hỏi có bao nhiêu i,j thỏa mãn l<=ai+aj<=r
# Thuật toán: Với bài toán tính tổng 2 phần tử -> Sắp xếp mảng
# Sau khi sắp xếp mảng sử dụng 2 pointers method
# Phân tích: l<= ai+aj<=r
# Xét ai+aj sẽ có 3 khoảng ai+aj<l, l<=ai+aj<=r, r<ai+aj.
# Với ai+aj<=r sẽ có giá trị <l hoặc >=l
# Kết quả sẽ bằng pair(ai+aj<=r) - pair(ai+aj<l)
# Sử dụng 2 pointer left,right -> a[left] + a[right] < r. Nếu >r -> right-- vì left tiến thì càng lớn
def pair(a, x):
    p = 0
    l, r = 0, len(a)-1
    while l < r:
        if a[l] + a[r] <=x:
            p += r-l
        else:
            while a[l] + a[r] > x and r > l:
                r -=1
            if r>l:
                p+= r-l
        l+=1
    return p

for _ in range(int(input())):
    n ,l, r = [int(i) for i in input().split()]
    a = [int(i) for i in input().split()]
    a.sort()
    print(pair(a, r)-pair(a, l-1))