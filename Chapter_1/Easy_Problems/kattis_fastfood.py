'''
Kattis - fastfood
Just read and follow. Would be harder the same sticker could be used for different prizes,
then we would need some kind of dynamic programming.

Time: linear, Space: linear
'''
num_tc = int(input())
for tc in range(num_tc):
    n, m = map(int, input().split())
    prizes = [list(map(int, input().split())) for _ in range(n)]
    stickers = list(input().split())
    stickers = [int(x) for x in stickers]
    
    ans = 0
    for prize in prizes:
        cash = prize.pop()
        prize.pop(0)
        num = min(stickers[prize[i] - 1] for i in range(len(prize)))
        ans += cash * num
        
    print(ans)