# t = int(input())
# all = []
# for i in range(t):
#     x = input()
#     a = [int(i) for i in x.split()]
#     all.append(a)

# t = int(input())
# all = []
# for i in range(t):
#     x = int(input())
#     all.append(x)

t= int(input())
all = []
x_arr = []
for i in range(t):
    k = input()
    k = [int(m) for m in k.split()]
    l,x = k
    x_arr.append(x)
    h = input()
    a = [int(z) for z in h.split()]
    all.append(a)

