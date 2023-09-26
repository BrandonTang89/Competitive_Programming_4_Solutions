'''
Kattis - mathworksheet
Relatively straightforward output formatting with built in python functions. The biggest annoyance is that
the question is quite ambiguous on whether to output a newline character at the end of the entire output.
The sample output doesn't have it, but it is necessary for AC.
Tiime: O(n), Space: O(n)
'''
inside = False
while True:
    n = int(input())
    if n == 0: break
    if inside: 
        print()
    inside = True
    
    
    arr = [str(eval(input())) for _ in range(n)]
    maxLen = max(map(len, arr))
    arr = [s.rjust(maxLen) for s in arr]
    
    print(arr[0], end="")
    numChars = len(arr[0])
    
    for (i, s) in enumerate(arr[1:]):
        if numChars + 1 + len(s) <= 50:
            print(" " + s, end="")
            numChars += 1 + len(s)
        else:
            print()
            print(s, end="")
            numChars = len(s)
    
    print()