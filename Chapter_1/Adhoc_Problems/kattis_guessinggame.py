'''
Kattis - guessinggame
Relatively basic problem. Could be improved with RUPQ fenwick tree.

Time: O(n), Space: O(1)
'''
arr = [True for i in range(10)]
while True:
    x = int(input())
    if x == 0: break
    
    x-= 1
    outcome = input()
    if outcome == "too high":
        for i in range(x, 10):
            arr[i] = False
    elif outcome == "too low":
        for i in range(0, x+1):
            arr[i] = False
    else:
        print("Stan is dishonest" if not arr[x] else "Stan may be honest")
        arr = [True for i in range(10)]