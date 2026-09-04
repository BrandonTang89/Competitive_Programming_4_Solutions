
def qGeq(u: int, v: int, d: int) -> bool:
    # returns true if dist(u, v) >= d
    print(f"? {u} {v} {d}", flush=True)
    res = int(input())
    assert res == 0 or res == 1
    return res == 1
    
for _ in range(int(input())):
    n = int(input())
    ub = 2 # 1 above the largest distance seen thus far
    
    # find x to be the furthest from 1
    x = 2
    for i in range(2 ,n+1):
        while True:
            if qGeq(1, i, ub):
                x = i
                ub += 1
            else:
                break
            
    # find y to be the furthest from x
    y = 1
    for i in range(2, n+1):
        while True:
            if x != i and qGeq(x, i, ub):
                y = i
                ub += 1
            else:
                break
    
    print(f"! {x} {y} {ub-1}")
        