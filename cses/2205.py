n = int(input())
# n = 4
 
# print(type(format(10, 'b')))
def f(number):
    binary_number = format(number, 'b')
    for i in range(len(binary_number)-1, -1,-1):
        if binary_number[i] == '1':
            return len(binary_number) - i-1
def assign(s, index, value):
    return s[:index] + value + s[index+1:]
s = "0" * n
for i in range(1,2**n):
    print(s)
    # s[f(i)] = str(1-int(s[f(i)])) 
    s = assign(s, f(i), str(1-int(s[f(i)])))
print(s)

"""
Đề bài yêu cầu in ra dãy số từ 1->2^n dạng nhị phân với điều kiện số đằng trước với 
số sát ngay sau khác nhau 1 kí tự
Ví dụ 1001 -> 1101, khác nhau số thứ 2 0->1
F(number)  sẽ trả về vị trí đầu tiên kí tự 1 xuất hiện theo thứ tự cuối lên
-> ví dụ 1010 -> xét từ cuối lên thì vị trí số 2 -> trả về index = 3
0101 -> index = 4 -> có thể coi là số 1 cuối cùng xuất hiện cũng dc
Số 3: 0100. Tới số 4 là 0100. Xét ngược thì số 1 xuất hiện tại index 2
-> số tiếp theo thì index 2 sẽ đổi từ 0<->1 -> 0110
số 5 = 0101 -> index 0 -> từ 0110 sẽ thành 1110 (index 0 số 0 sẽ thành số 1)
"""