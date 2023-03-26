# https://codeforces.com/contest/1535/problem/B
# Để the maximum number of good index pairs  -> mảng sẽ có dạng bên trái chẵn, phải toàn bộ lẻ
# -> r*(r-1)/2 + r*l + number of pair in right
from math import gcd

for _ in range(int(input())):
    n = input()
    a = [int(i) for i in input().split(' ')]
    left = []
    right = []
    for i in a:
        if i%2 == 0:
            left.append(i)
        else:
            right.append(i)
    ans = 0
    ans += len(left) * (len(left) -1) //2 + len(left) * len(right)
    for i in range(len(right) - 1):
        for j in range(i+1, len(right)):
            if gcd(right[i], 2* right[j]) > 1:
                ans +=1
    print(ans)