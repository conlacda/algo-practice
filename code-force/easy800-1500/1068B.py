import math
b = int(input())

# Number of divisors of b

count = 0
if b ==1:
    print(1)
else:
    for i in range(1, round(math.sqrt(b))+1):
        if b%i ==0:
            count +=1
            # print(f"i={i}")
    # print(f'count= {count}')
    if round(math.sqrt(b)) * round(math.sqrt(b)) == b:
        print(count * 2-1)
    else:
        print(count *2)