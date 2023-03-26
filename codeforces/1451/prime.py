#https://codeforces.com/problemset/problem/1451/A

def nats(n):
    yield n
    yield from nats(n+1)

s = nats(2)

def sieve(s):
    n = next(s)
    yield n
    yield from sieve(i for i in s if i%n!=0)

p = sieve(nats(2))

# number = input()
# arr = []
# for i in range(int(number)):
#     n = input()
#     arr.append(int(n))

arr = [25]
import math
n = max(arr)
# Danh sách những số nguyên tố nhỏ hơn căn 2 của n
prime = []
i = next(p)

while i <= round(math.sqrt(n)):
    prime.append(i)
    i = next(p)

for i in range(len(arr)):
    n = arr[i]
    count = 0
    if len(prime) == 0:
        print(n-1)
    else:
        while n != 1:
            s = round(math.sqrt(n))
            for pr in prime:
                if pr > s:
                    n -=1
                    count +=1
                    break
                if n%pr == 0:
                    n = pr -1
                    count +=2
                    break
                if pr == prime[-1]:
                    n -=1
                    count+=1
            # print(n, count)
        print(count)