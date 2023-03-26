#https://codeforces.com/problemset/problem/1263/B
# Yêu cầu không được thay đổi vị trí in ra
# Đánh dấu phần tử duplicate cần thay đổi và giữ nguyên
# Phần tử cần thay đổi thì sẽ đuổi đuôi khác với các phần tử giữ nguyên có sẵn
# Ví dụ 1111,1112,1111 -> cần thay đổi 1111 ở vtri 3. Các đuôi có sẵn là 1,2 -> thay đổi thành 0->9 khác 1,2
t = int(input())
for _ in range(t):
    n = int(input())
    pincodes = []
    for i in range(n):
        pincodes.append(input())
    duplicate = [False] * n
    lst = []
    change = 0
    for i in range(len(pincodes)):
        if pincodes[i] not in lst:
            lst.append(pincodes[i])
        else:
            duplicate[i] = True
            change +=1
    digits = []
    for i in range(len(pincodes)):
        if not duplicate[i]:
            digits.append(pincodes[i][3])
    
    for i in range(1, len(pincodes)):
        if duplicate[i]:
            for j in range(0,10):
                if str(j) not in digits:
                    digits.append(str(j))
                    pincodes[i] = pincodes[i][0:3] + str(j)
                    break
        else:
            digits.append(pincodes[i][3])
    print(change)
    for p in pincodes:
        print(p)