'''
Kattis - genius
Decently easy DP probability problem. Let dp(k, cur) be the probability of genius given that we
need to do k more correct predictions and that we are considering tournament cur. Then with the
parition theorem for probability: dp(k, cur) = dp(k-1, cur+1) * p + dp(k, cur+1) * (1-p) where p
is the probaility of correctly predicting the winner of tournament cur. 

Time: O(kt), Space: O(kt)
'''
from functools import lru_cache
k, t, p, q, x1 = map(int, input().split())

xs = [x1]
for _ in range(1, t):
    xs.append((p * xs[-1]) % q)

xs = [x % 4 for x in xs]
tourneys = [list(map(int, input().split())) for _ in range(t)]


def getWinProb(arr, index):
    if index == 0:
        return arr[0]/(arr[0]+arr[1]) * \
            (arr[0]/(arr[0] + arr[2]) * (arr[2]/(arr[2] + arr[3])) +
             arr[0]/(arr[0] + arr[3]) * (arr[3]/(arr[2] + arr[3])))
    elif index == 1:
        return arr[1]/(arr[0]+arr[1]) * \
            (arr[1]/(arr[1] + arr[2]) * (arr[2]/(arr[2] + arr[3])) +
             arr[1]/(arr[1] + arr[3]) * (arr[3]/(arr[2] + arr[3])))
    elif index == 2:
        return arr[2]/(arr[2]+arr[3]) * \
            (arr[2]/(arr[2] + arr[0]) * (arr[0]/(arr[0] + arr[1])) +
             arr[2]/(arr[2] + arr[1]) * (arr[1]/(arr[0] + arr[1])))
    elif index == 3:
        return arr[3]/(arr[2]+arr[3]) * \
            (arr[3]/(arr[3] + arr[0]) * (arr[0]/(arr[0] + arr[1])) +
             arr[3]/(arr[3] + arr[1]) * (arr[1]/(arr[0] + arr[1])))


@lru_cache(None)
def dp(k: int, cur: int):  # probability of genius assuming that you need k more correct and that we are on tournament cur
    if k == 0:
        return 1
    if cur == t:
        return 0

    p = getWinProb(tourneys[cur], xs[cur])
    return dp(k-1, cur+1) * p + dp(k, cur+1) * (1-p)


print(dp(k, 0))
