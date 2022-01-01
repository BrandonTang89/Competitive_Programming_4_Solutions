'''
Kattis - windows
AMC ICPC World Finals problem. It is expected to be difficult, and it is. Relatively tedious and
very prone to bugs. Approach with that expectation and you won't be too annoyed by it. Important
things to take note of:

- When resizing or opening, check for both overlap and out of bounds.
- When moving, check for selected box before checking if 0 movement.
- Remember to sort windows at the end based on when the window was open

How the moving works is that we have a set of windows that are already part of the moving
block and a set of windows that are not part of the moving block. For each window in the moving
block, we check for the nearest non-moving window that it will collide with. We get the minimum
distance to the next non-moving window that will be hit when we attempt to move the moving
block the required distance. Then, we move the block by this minimum distance and then add the
collided window into the moving block. We repeat until we stop colliding into boxes / reach
the edge of the screen. Refer to the code for more details.

Time: O(n^3) for the move instruction where n is the number of open windows
The rest of the commands operate in O(n)

Space: O(n)
'''
from sys import stdin
import copy
class window:
    def __init__(self, x, y, w, h, index):
        self.x = x
        self.y = y
        self.h = h
        self.w = w
        self.index = index
    def __repr__(self):
        return self.__str__()
    def __str__(self):
        return "(%d, %d, %d, %d)" % (self.x, self.y, self.w, self.h)
    def detect_click(self, cx, cy):
        # Determine if (cx, cy) is inside the box
        if self.x <= cx <= self.x + self.w -1 and self.y <= cy <= self.y + self.h -1:
            return True
        else:
            return False
    def get_resized_box(self, w, h):
        return window(self.x, self.y, w, h, self.index)
    
def is_overlap(b1, b2):
    if b1.x <= b2.x + b2.w -1 and b1.x + b1.w -1 >= b2.x and b1.y <= b2.y + b2.h -1 and b1.y + b1.h -1 >= b2.y:
        return True
    else:
        return False
    
def get_selected_box(cx, cy):
    selected_box = None
    for box in boxes:
        if box.detect_click(cx, cy):
            selected_box = box
            break
    return selected_box

lines = stdin.readlines()
max_x, max_y = lines.pop(0).split()
max_x, max_y = int(max_x), int(max_y)

boxes = []


# Attempts to open a new box, returns True if successful
cur_new_window_index = 0
def open_cmd(args):
    global cur_new_window_index
    x, y, w, h = map(int, args.split())
    new_box = window(x, y, w, h, cur_new_window_index)
    
    for box in boxes:
        if is_overlap(new_box, box):
            return False, "window does not fit"

    # Check if new window gets out of bounds
    if new_box.x + new_box.w > max_x or new_box.y + new_box.h > max_y:
        return False, "window does not fit"
    
    cur_new_window_index += 1
    boxes.append(new_box)
    return True, "success"

def resize_cmd(args):
    cx, cy, w, h = map(int, args.split())
    selected_box = get_selected_box(cx, cy)
    if selected_box is None:
        return False, "no window at given position"
    else:
        new_box = selected_box.get_resized_box(w, h)
        for box in boxes:
            if box == selected_box:
                continue
            if is_overlap(new_box, box):
                return False, "window does not fit"
            
        # Check if new window gets out of bounds
        if new_box.x + new_box.w > max_x or new_box.y + new_box.h > max_y:
            return False, "window does not fit"
        boxes.remove(selected_box)
        boxes.append(new_box)
        return True, "success"

def close_cmd(args):
    cx, cy = map(int, args.split())
    selected_box = get_selected_box(cx, cy)
    if selected_box is None:
        return False, "no window at given position"
    else:
        boxes.remove(selected_box)
        return True, "success"

def move_cmd(args):
    global boxes
    cx, cy, dx, dy = map(int, args.split())
    
    selected_box = get_selected_box(cx, cy)
    if selected_box is None:
        return False, "no window at given position"
    
    if (dx, dy) == (0, 0): 
        return True, "zero move"
    remaining_boxes = boxes
    remaining_boxes.remove(selected_box)
    moving_block = [selected_box]
    
    if dx > 0: # Move right
        dist_left = dx
        while dist_left > 0:
            # print("moving block", moving_block, "remaining boxes", remaining_boxes)
            distance_to_move = dist_left
            for box in moving_block:
                dist_to_wall = max_x - box.x - box.w
                distance_to_move = min(dist_to_wall, distance_to_move)
            
            colliding_box = None
            for box in moving_block:
                for box2 in remaining_boxes:
                    if box.x < box2.x and ((box.y + box.h - 1) >= box2.y and (box.y) <= (box2.y + box2.h - 1)):
                        dist_to_box = box2.x - (box.x + box.w)
                        if distance_to_move > dist_to_box:
                            colliding_box = box2
                            distance_to_move = dist_to_box
            
            # Move all the blocks
            # print("moving by", distance_to_move)
            new_block = []
            for box in moving_block:
                box = window(box.x + distance_to_move, box.y, box.w, box.h, box.index)
                new_block.append(box)
            moving_block = new_block
            dist_left -= distance_to_move
            
            if colliding_box is None: # thats about it for the move
                break
            else:
                moving_block.append(colliding_box)
                remaining_boxes.remove(colliding_box)
        
        boxes = moving_block + remaining_boxes
        # print("boxes", boxes)
        if dist_left != 0:
            return False, f"moved {dx - dist_left} instead of {dx}"
        else: return True, "success"
    
    elif dx < 0: # Move left
        dist_left = -dx
        while dist_left > 0:
            # print("moving block", moving_block, "remaining boxes", remaining_boxes)
            distance_to_move = dist_left
            for box in moving_block:
                dist_to_wall = box.x
                distance_to_move = min(dist_to_wall, distance_to_move)
            
            colliding_box = None
            for box in moving_block:
                for box2 in remaining_boxes:
                    if box.x > box2.x and ((box.y + box.h - 1) >= box2.y and (box.y) <= (box2.y + box2.h - 1)):
                        dist_to_box = box.x - (box2.x + box2.w)
                        if distance_to_move > dist_to_box:
                            colliding_box = box2
                            distance_to_move = dist_to_box

            # Move all the blocks
            # print("moving by", distance_to_move)
            new_block = []
            for box in moving_block:
                box = window(box.x - distance_to_move, box.y, box.w, box.h, box.index)
                new_block.append(box)
            moving_block = new_block
            dist_left -= distance_to_move
            
            if colliding_box is None: # thats about it for the move
                break
            else:
                moving_block.append(colliding_box)
                remaining_boxes.remove(colliding_box)
        
        boxes = moving_block + remaining_boxes
        # print("boxes", boxes)
        
        if dist_left != 0:
            return False, f"moved {-dx - dist_left} instead of {-dx}"
        else: return True, "success"
        
    elif dy > 0: # Move down
        dist_left = dy
        while dist_left > 0:
            # print("moving block", moving_block, "remaining boxes", remaining_boxes)
            distance_to_move = dist_left
            for box in moving_block:
                dist_to_wall = max_y - box.y - box.h
                distance_to_move = min(dist_to_wall, distance_to_move)
            
            colliding_box = None
            for box in moving_block:
                for box2 in remaining_boxes:
                    if box.y < box2.y and ((box.x + box.w - 1) >= box2.x and (box.x) <= (box2.x + box2.w - 1)):
                        dist_to_box = box2.y - (box.y + box.h)
                        if distance_to_move > dist_to_box:
                            colliding_box = box2
                            distance_to_move = dist_to_box
            
            # Move all the blocks
            # print("moving by", distance_to_move)
            new_block = []
            for box in moving_block:
                box = window(box.x, box.y + distance_to_move, box.w, box.h, box.index)
                new_block.append(box)
            moving_block = new_block
            dist_left -= distance_to_move
            
            if colliding_box is None: # thats about it for the move
                break
            else:
                moving_block.append(colliding_box)
                remaining_boxes.remove(colliding_box)
        
        boxes = moving_block + remaining_boxes
        # print("boxes", boxes)
        if dist_left != 0:
            return False, f"moved {dy - dist_left} instead of {dy}"
        else: return True, "success"

    elif dy < 0: # Move up
        dist_left = -dy
        while dist_left > 0:
            # print("moving block", moving_block, "remaining boxes", remaining_boxes)
            distance_to_move = dist_left
            for box in moving_block:
                dist_to_wall = box.y
                distance_to_move = min(dist_to_wall, distance_to_move)
            
            colliding_box = None
            for box in moving_block:
                for box2 in remaining_boxes:
                    if box.y > box2.y and ((box.x + box.w - 1) >= box2.x and (box.x) <= (box2.x + box2.w - 1)):
                        dist_to_box = box.y - (box2.y + box2.h)
                        if distance_to_move > dist_to_box:
                            colliding_box = box2
                            distance_to_move = dist_to_box

            # Move all the blocks
            # print("moving by", distance_to_move)
            new_block = []
            for box in moving_block:
                box = window(box.x, box.y - distance_to_move, box.w, box.h, box.index)
                new_block.append(box)
            moving_block = new_block
            dist_left -= distance_to_move
            
            if colliding_box is None: # thats about it for the move
                break
            else:
                moving_block.append(colliding_box)
                remaining_boxes.remove(colliding_box)
        
        boxes = moving_block + remaining_boxes
        # print("boxes", boxes)
        
        if dist_left != 0:
            return False, f"moved {-dy - dist_left} instead of {-dy}"
        else: return True, "success"
    
for cmd_num, line in enumerate(lines):
    # print(boxes)
    line = line.strip()
    cmd, _, args = line.partition(' ')
    if cmd == "OPEN":
        success, msg = open_cmd(args)
        if (not success):
            print(f"Command {cmd_num+1}: OPEN - {msg}")
    elif cmd == "RESIZE":
        success, msg = resize_cmd(args)
        if (not success):
            print(f"Command {cmd_num+1}: RESIZE - {msg}")
    elif cmd == "CLOSE":
        success, msg = close_cmd(args)
        if (not success):
            print(f"Command {cmd_num+1}: CLOSE - {msg}")
    else:
        success, msg = move_cmd(args)
        if (not success):
            print(f"Command {cmd_num+1}: MOVE - {msg}")

boxes.sort(key=lambda x: x.index)
# print("cur window", cur_new_window_index)
print(f"{len(boxes)} window(s):")
for box in boxes:
    print(box.x, box.y, box.w, box.h)