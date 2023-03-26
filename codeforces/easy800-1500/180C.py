# https://codeforces.com/problemset/problem/180/C 1400

s = input()
start = 0
end = len(s) - 1

while 'A' <= s[start] <= 'Z':
    start += 1
    if start == len(s):
        break

while 'a' <= s[end] <= 'z':
    end -= 1
    if end == -1:
        break

upper = 0
lower = 0
upper_c = []
lower_c = []
print(s[start:end+1])
for i in range(start, end+1):
    if 'a' <= s[i] <= 'z':
        lower += 1
    elif 'A' <= s[i] <= 'Z':
        upper += 1

print(min(upper, lower))
