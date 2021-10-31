from functools import lru_cache
from math import isclose
from collections import Counter
drinks = []
path = []

@lru_cache(maxsize=None)
def dp(drink_left, money_left, index):
    if index == n:
        if (isclose(drink_left, 0, abs_tol=1e-9) and isclose(money_left, 0, abs_tol=1e-9)): return 1
        else: return 0
            
    if drink_left < -1e-9 or money_left < -1e-9:
        return 0
    
    (drink_name, amt, price) = drinks[index]
    return max(dp(drink_left-amt, money_left-price, index), dp(drink_left, money_left, index+1))

def fill_path(drink_left, money_left, index):
    global path
    if index == n:
        return
    
    (drink_name, amt, price) = drinks[index]
    if (dp(drink_left, money_left, index+1) == 1):
        fill_path(drink_left, money_left, index+1)
    elif (dp(drink_left-amt, money_left-price, index) == 1):
        path.append(drinks[index][0])
        fill_path(drink_left-amt, money_left-price, index)
    else:
        return

money, target_drink, n = input().split()
money = float(money)
target_drink = float(target_drink)
n = int(n)

for i in range(n):
    drink_name, x, y, drink_price = input().split()
    x = int(x)
    y = eval(y)
    drink_price = float(drink_price)

    drinks.append((drink_name, float(x*y), drink_price))

#print(drinks)

fill_path(target_drink, money, 0)
path = Counter(path)
if (len(path) == 0):
    print("IMPOSSIBLE")
else:
    for (k, v) in path.items():
        print(f"{k} {v}")