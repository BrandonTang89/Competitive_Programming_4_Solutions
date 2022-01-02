'''
Kattis - provincesandgold
Behold! Nested ternary operators!

Time: O(1), Space: O(1)
'''
g, s, c = map(int, input().split())
buying_power = g*3 + s*2 + c

best_treasure = 'Gold' if buying_power >= 6 else 'Silver' if buying_power >= 3 else 'Copper'
best_estate = 'Province' if buying_power >= 8 else 'Duchy' if buying_power >= 5 else 'Estate' if buying_power >= 2 else None

if best_estate is None:
    print(best_treasure)
else:
    print(best_estate, "or", best_treasure)