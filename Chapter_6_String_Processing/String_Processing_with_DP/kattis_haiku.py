'''
Kattis - haiku
Straightforward DP problem. Heavy use of python magic makes it much easier to implement (rather than)
memo table with indices that need to be reset for each line.
Minimising this file results in the current shortest length solution of 368 (chars?) in 11 lines
Time: O(length src * target * n), Space: O(length src * target)
''' 
from functools import lru_cache
n = int(input())
syll = [input() for _ in range(n)]


@lru_cache(maxsize=None)
def decompose(src: str, target: int):
    if target == 0 and src == '':
        return True
    if target == 0 or src == '':
        return False
    if src[0] == ' ':  # remove leading spaces
        src = src[1:]
    for s in syll:
        if src.startswith(s) and decompose(src[len(s):], target-1): return True
    return False

if decompose(input(), 5) and decompose(input(), 7) and decompose(input(), 5):
    print('haiku')
else:
    print('come back next year')