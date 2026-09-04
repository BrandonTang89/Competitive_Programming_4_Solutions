
from math import gcd

for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    print(gcd(arr[0], arr[-1]))