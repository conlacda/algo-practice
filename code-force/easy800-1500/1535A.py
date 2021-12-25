t = int(input())
for _ in range(t):
    a = [int(x) for x in input().split(' ')]
    max1 = max(a[0],a[1])
    max2 = max(a[2],a[3])
    if max1 > min(a[2], a[3]) and max2 > min(a[0], a[1]):
        print('YES')
    else:
        print('NO')