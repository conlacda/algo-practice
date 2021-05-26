n = input()
n = int(n)
a = []
for i in range(n):
    m = input()
    t = input()
    a.append([int(i) for i in t.split()])

for l in a:
    if len(l) == 1:
        print(0)
    else:
        clone = []
        for i in range(len(l) -1):
            if l[i] != l[i+1]:
                clone.append(l[i])
        clone.append(l[-1])
        c = list(set(clone))
        _count = []
        for i in c:
            _count.append(clone.count(i))
        max_count = min(_count)
        count_l0 = clone.count(clone[0])
        count_ls = clone.count(clone[-1])
        if l[0] == l[-1]:
            if max_count == count_l0:
                print(max_count -1)
            else:
                print(max_count +1)
        else:
            if max_count == count_l0 or max_count == count_ls:
                print(max_count)