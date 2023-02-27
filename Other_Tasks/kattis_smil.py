# Kattis -smil
# Simply find all occurances of the 4 types of substrings which don't overlap. This is done easily with regex.
# Time: O(n), Mem: O(n)
import re
for i in [m.start() for m in re.finditer(':\)|;\)|:-\)|;-\)', input())]:
    print(i)
