'''
Kattis - pachydermpeanutpacking
Kinda like a super super easy version of kattis - windows. Just use a simple for loop.

Time: O(m + n), Space: O(n)
'''
class crate:
    def __init__(self, x1, y1, x2, y2, size):
        self.x1 = float(x1)
        self.y1 = float(y1)
        self.x2 = float(x2)
        self.y2 = float(y2)
        self.size = size
    
    def __str__(self):
        return "({}, {}) - ({}, {})".format(self.x1, self.y1, self.x2, self.y2)

    def __repr__(self):
        return "({}, {}) - ({}, {})".format(self.x1, self.y1, self.x2, self.y2)
    
    def check_within(self, x, y, peanut_size): 
        if self.x1 <= x <= self.x2 and self.y1 <= y <= self.y2:
            return True, "correct" if peanut_size == self.size else self.size
        else:
            return False, "not in crate"

while True:
    n = int(input())
    if n == 0: exit()
    
    boxes = [crate(*input().split()) for _ in range(n)]
    m = int(input())
    
    for _ in range(m):
        x, y, size = input().split()
        x, y = float(x), float(y)
        
        for box in boxes:
            in_box, msg = box.check_within(x, y, size)
            if in_box:
                print(size, msg)
                break
        else:
            print(size, "floor")
    
    print()