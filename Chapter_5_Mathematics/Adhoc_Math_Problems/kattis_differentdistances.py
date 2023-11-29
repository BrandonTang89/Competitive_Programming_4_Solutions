'''
Kattis - differentdistances
Easy.
Time: O(1), Space: O(1)
'''
while True:
    l = input()
    if l == "0": break
    x1, y1, x2, y2, p = map(float, l.split())
    print("{:.10f}".format(((abs(x1 - x2))**p + (abs(y1 - y2))**p)**(1/p)))