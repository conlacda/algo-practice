"""
https://codeforces.com/problemset/problem/1501/B
Duyệt ngược mảng, thay vì xử lý luôn hết giá trị cho mảng out khi duyệt thì
chỉ tính đến phần giá trị của mảng out tại chính đó rồi trừ giá trị cur tại mảng in đi 1
-> Từ O(nlogn) -> O(n)
"""
for _ in range(int(input())):
    __ = input()
    l = [int(i) for i in input().split(' ')]
    a = [0] * len(l)
    cur = 0
    for i in range(len(l)-1, -1, -1):
        cur = max(l[i], cur)
        if cur > 0:
            a[i] = 1
            cur -=1
    print(*a)