'''
Kattis - persistent
Kinda sketchy problem. The n < 10 edge case should be clear. For the general case, if the number
has a prime factor >= 10 then we cannot construct the answer. Else we prime factorise into {2, 3, 5, 7}
then we need to determine how to combine some of these factors into the smallest possible answer.
Clearly 5 and 7 cannot be combined. The issue and 2 and 3 can be used to form {4, 6, 8, 9}. But we
observe that greedily forming larger numbers is better since it results in less/smaller digits in
the front of the number (ik it is handwavy but hey its CP). Then we just print the digits in increasing
order.

Time: O(log n), Mem: O(1)
'''
while True:
    n = int(input())
    if (n == -1):
        exit()

    if n < 10:
        print(10 + n)
        continue

    primes = [2, 3, 5, 7]
    exps = [0, 0, 0, 0]
    ans = 0
    for (i, p) in enumerate(primes):
        while n % p == 0:
            exps[i] += 1
            n //= p

    if n > 1:
        print("There is no such number.")
    else:
        nines = exps[1] // 2
        exps[1] -= nines * 2
        eights = exps[0] // 3
        exps[0] -= eights * 3
        sixes = min(exps[0], exps[1])
        exps[0] -= sixes
        exps[1] -= sixes
        fours = exps[0] // 2
        exps[0] -= fours * 2

        ans = "2" * exps[0] + "3" * exps[1] + "4" * fours + "5" * exps[2] + "6" * sixes \
            + "7" * exps[3] + "8" * eights + "9" * nines
        print(ans)
