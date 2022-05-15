'''
Kattis - beavergnaw
A heavy on math question, work it out on pen and paper!

Time: O(1), Space: O(1)
'''
while True:
    D, V = map(int, input().split())
    if (D == 0 and V == 0): break
    
    print((D**3 - 6*V/3.14159265359)**(1/3))