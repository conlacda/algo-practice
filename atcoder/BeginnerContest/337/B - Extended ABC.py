import re
s = input()
match = re.findall(r"^A*B*C*$", s)
if len(match) > 0:
    print("Yes")
else:
    print("No")
