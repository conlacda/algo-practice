# a =[]
# for i in range(1,10000):
#     a.append(i**3)
# https://codeforces.com/problemset/problem/1490/C
def is_cube(n):
    return round(n**(1/3)) **3 == n

def solve(n):
    global a
    x = round((n//2)**(1/3))
    # print(x)
    for i in range(1, x+1):
        if is_cube(n-i**3) and n-i**3>0:
            # print(n-i**3)
            print('YES')
            return
    print('NO')

for _ in range(int(input())):
    n = int(input())
    solve(n)
# print(is_cube(8))