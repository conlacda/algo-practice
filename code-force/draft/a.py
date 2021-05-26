t = int(input())
rs = []

import math
def distance(p1,p2):
    return math.sqrt( (p1[0] -p2[0])**2 + (p1[1] -p2[1])**2)
for i in range(t):
    cor = []
    z = input()
    n,k = z.split(' ')
    n, k = int(n),int(k)
    for i in range(n):
        z = input()
        x,y = z.split(' ')
        x,y = int(x), int(y)
        cor.append([x,y])
    # cor = sorted(cor, key=lambda i:i[0])
    
    max_1 = cor[0]
    max_2 = cor[0]
    max_3 = cor[0]
    max_4 = cor[0]
    for item in cor:
        if item[0] > max_1[0]:
            max_1 = item
        if item[0] < max_2[0]:
            max_2 = item
        if item[1] > max_3[1]:
            max_3 = item
        if item[1] < max_3[1]:
            max_3 = item
    m = False
    for item in cor:
        if distance(max_1, item) <=k and distance(max_2, item) <=k:
            if distance(max_3, item) <=k and distance(max_4, item)<=k:
                rs.append(1)
                m = True
                break
    if not m:
        rs.append(-1)    

for item in rs:
    print(item)