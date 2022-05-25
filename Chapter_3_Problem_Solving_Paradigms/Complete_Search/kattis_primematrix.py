'''
Kattis - primematrix
Constructive problem, first we find a set of distinct positive integers that sum to a prime
number such that the maximum number is minimised. Then the matrix can be constructed by printing
all lexicographical rotations of the set of numbers. 

To find this set of numbers, given the bounds of the task, it is sufficient to do the following:
1. Assume our set is 1..n
2. Find the smallest prime >= sum(1..n)
3. replace zero or one of the n numbers with n+1 such that the sum is equal to the prime

Time: O(n), Space: O(n)
'''
_sieve_size = 0
bs = []
primes = []
def sieve(upperbound=1277): # Smallest prime larger than sum(1..50) is 1277
    global _sieve_size, bs, primes

    _sieve_size = upperbound+1
    bs = [True] * 10000010
    bs[0] = bs[1] = False
    for i in range(2, _sieve_size):
        if bs[i]:
            for j in range(i*i, _sieve_size, i):
                bs[j] = False
            primes.append(i)
            
sieve()

n, b = map(int, input().split())
init_sum = (n*(n+1))//2
for p in primes:
    if (p >= init_sum):
        target_prime = p
        break

nums = []  
if (target_prime != init_sum):
    diff = target_prime - init_sum
    x = n+1 - diff
    
    for i in range(1, n+2):
        if (i != x):
            nums.append(i)
    
else:
    nums = [i for i in range(1, n+1)]

if (nums[-1] > b):
    print("impossible")
else:
    for _ in range(n):
        print(" ".join(map(str, nums)))
        nums.append(nums[0])
        nums.pop(0)