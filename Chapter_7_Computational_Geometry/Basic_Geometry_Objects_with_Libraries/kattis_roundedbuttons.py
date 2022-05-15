'''
Kattis - Rounded Buttons
We can segment the rounded rectangle into 5 rectangles and 4 circles such that their union
will form the rounded rectangle. Then we just detect for clicks on each of the individual
shapes.

Kinda tedious, but not too bad.

Time: O(1), Space: O(1) {per click per object}
'''
num_tc = int(input())
def click_in_rect(rect, click):
    if rect[0] <= click[0] <= rect[2] and rect[1] <= click[1] <= rect[3]:
        return True
    return False

def click_in_circle(circle, click): # circle = (x, y, r)
    if (click[0] - circle[0])**2 + (click[1] - circle[1])**2 <= circle[2]**2:
        return True
    return False
    
for tc in range(num_tc):
    line = input().split()
    x, y, w, h, r = line.pop(0), line.pop(0), line.pop(0), line.pop(0), line.pop(0)
    x, y, w, h, r = float(x), float(y), float(w), float(h), float(r)
    rectangles = []
    rectangles.append((x+r, y+r, x+w-r, y+h-r))
    rectangles.append((x+r, y, x+w-r, y+r))
    rectangles.append((x+w-r, y+r, x+w, y+h-r))
    rectangles.append((x+r, y+h-r, x+w-r, y+h))
    rectangles.append((x, y+r, x+r, y+h-r))
    
    circles = []
    circles.append((x+r, y+r, r))
    circles.append((x+w-r, y+r, r))
    circles.append((x+w-r, y+h-r, r))
    circles.append((x+r, y+h-r, r))
    
    line.pop(0)
    while len(line) > 0:
        x, y = line.pop(0), line.pop(0)
        x, y = float(x), float(y)
        
        in_obj = False
        for rect in rectangles:
            if click_in_rect(rect, (x, y)):
                in_obj = True
                break
        for circle in circles:
            if click_in_circle(circle, (x, y)):
                in_obj = True
                break
        
        if in_obj:
            print("inside")
        else:
            print("outside")
    
    print()