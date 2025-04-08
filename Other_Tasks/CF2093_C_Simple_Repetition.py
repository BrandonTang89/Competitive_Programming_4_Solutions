def is_prime(n):
    """Check if a number is a prime number."""
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True


for _ in range(int(input())):
    n, k = map(int, input().split())

    # edge cases
    if n == 1:
        if k == 2:
            print("YES")
            continue

    if k > 1:
        print("NO")
        continue
    elif is_prime(n):
        print("YES")
        continue
    else:
        print("NO")
