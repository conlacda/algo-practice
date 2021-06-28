from collections import Counter

_ = input()
a = [int(i) for i in input().split()]
a.sort()

d = Counter(a)
ans = 0
for it in d:
    ans += d[it] * (len(a)-d[it])
print(ans//2)