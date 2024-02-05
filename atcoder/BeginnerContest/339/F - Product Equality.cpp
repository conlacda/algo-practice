n = int(input())
a = []
for i in range(n):
	k = int(input())
	a.append(k)
a.sort()
adict = dict()
for i in range(len(a)):
	if (a[i] not in adict):
		adict[a[i]] = 1
	else:
		adict[a[i]] += 1

ans = 0

# for i in range(n):
# 	for j in range(n):
# 		mul = a[i] * a[j]
# 		if (mul in adict):
# 			ans += adict[mul]

maxElement = a[-1]
for i in range(n):
	for j in range(i, n):
		mul = a[i] * a[j]
		if (mul > maxElement):
			break
		if mul in adict:
			if (i == j):
				ans += adict[mul]
			else:
				ans += adict[mul] * 2

print(ans)
