# https://codeforces.com/problemset/problem/1539/B
# Bài này 800 điểm. 
# Đối với bài có dạng sub array từ a-> b. Tính sum(sub_array)
# Sau đó nếu lấy giá trị từ a-> b = sum_sub[b-1] - sum_sub[a-2]
from collections import Counter
s = "abcdefghijklmnopqrstuvwxyz"
n,m = [int(i) for i in input().split()]
str = input()
max_subarr = []
for i in range(len(str)):
    value = (s.index(str[i])+1)
    if len(max_subarr) > 0:
        max_subarr.append(max_subarr[-1] + value)
    else:
        max_subarr.append(value)
# print(max_subarr)

for _ in range(m):
    a,b = [int(i) for i in input().split()]
    if a ==1:
        print(max_subarr[b-1])
    else:
        print(max_subarr[b-1] - max_subarr[a-2])