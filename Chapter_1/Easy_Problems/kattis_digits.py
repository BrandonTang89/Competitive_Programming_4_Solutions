'''
Kattis - digits
Keep n as a string and use the len function to get the number of digits


Time: O(log len(n)), Space: O(len(n))'''
while 1:
    n = input()
    if n == "END": exit()
    
    if n == "1":
        print(1)
        continue
    if n == "0":
        print(2)
        continue
    
    ans = 0
    while n != "1":
        # print(n)
        n = str(len(n))
        ans += 1
    print(ans+1)