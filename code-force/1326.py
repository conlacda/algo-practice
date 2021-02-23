# https://codeforces.com/problemset/problem/1326/B

x= int(input())
b = []
t = input()
b = [int(i) for i in t.split()]

a = []
_max = b[0]
a.append(b[0])
for i in range(1,x):
    a.append(b[i]+ _max)
    _max = max(a[i], _max)
for i in range(len(a)):
    print(a[i], end=" ")