"""
https://codeforces.com/problemset/problem/1538/G
Bài này 2100 điểm là bài cuối của Div 3
bài yêu cầu tìm max(n1+n2) biết
a*n1+b*n2=x (*1)
a*n2+b*n1=y (*2)
n1>=0
n2>=0
"""
n = int(input())
for _ in range(n):
    x,y,a,b = [int(i) for i in input().split()]
    if (a==b):
        print(min(x//a,y//a))
    else:    # print(min((x+y)//(a+b), x//min(a,b), y//min(a,b)))
        n2 = (y*a-x*b)//(a**2-b**2)
        n1 = (x*a-y*b)//(a**2-b**2)
        if (n2<0): # n2>=0
            print(min(x//a,y//b))
        elif (n1<0): #n1>=0
            print(min(x//b,y//a))
        else:
            ans1 = min((x-a*n1)//b, (y-b*n1)//a) + n1 # min bởi vì là số nguyên ->hàm min làm tròn n2
            ans2 = min((y-a*n2)//b, (x-b*n2)//a) + n2 # hàm min làm tròn n1. Ví dụ n1 với phương trình (*1) là 3 (*2) là 2.5 -> lấy 2 vì max nhất là 2.5
            print(max(ans1,ans2))