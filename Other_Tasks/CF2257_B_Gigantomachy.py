import itertools


def num_lives(arr: list[int]) -> int:
    lives = sum(cur - next + 1 for cur, next in itertools.pairwise(arr))
    lives += arr[-1]
    return lives
        
for _ in range(int(input())):
    n, m = map(int, input().split())
    
    bea_lives = num_lives(list(map(int, input().split())))
    ver_lives = num_lives(list(map(int, input().split())))
    
    print(1 if bea_lives >= ver_lives else 2)