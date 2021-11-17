'''
Kattis - batmanacci
Observation 0:
    len(bat(n)) = fibo(n)
Observation 1:
    let the initial problem be (k, n)
    bat(n) = bat(n-2) + bat(n-1) = bat(n-2) + bat(n-3) + bat(n-2)
    
    So if k <= fibo(n-2), we can reduce the problem to (k, n-2)
       if fibo(n-2) < k <= fibo(n-1), we can reduce the problem to (k - fibo[n-2], n-3)
       if fibo(n-1) < k, we can reduce the problem to (k - fibo(n-1), n-2)
    
    At least this was what I saw. But the easier version is that
        if k <= fibo(n-2), reduce to (k, n-2)
        else reduce to (k - fibo(n-2), n-1)
    
    Both have the same complexity but the first one is slightly faster, but more complex to write.

Note that we don't actually have to compute all those large fibo numbers, since k is limited.. But since
we are using python, let's not waste brain power and just let built-in big integer do its job

Time: O(n), Space: O(n) 
'''

fibo = [0, 1]
for i in range(2, int(1e5)):
    fibo.append(fibo[-1] + fibo[-2])

n, k = map(int, input().split())

while (n > 3):
    if (k <= fibo[n-2]):
        n -= 2
    elif (k > fibo[n-1]):
        k -= fibo[n-1]
        n -= 2
    else:
        k -= fibo[n-2]
        n -= 3
    
bat = ["", "N", "A", "NA"]
print(bat[n][k-1])