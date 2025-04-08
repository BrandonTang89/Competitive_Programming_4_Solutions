def coord_to_num(x, y, n):
    # print(f"coord_to_num({x}, {y}, {n})")
    if n == 0:
        assert x == y == 1
        return 1

    is_top = x <= (1 << (n - 1))
    is_left = y <= (1 << (n - 1))

    if is_top and is_left:
        return coord_to_num(x, y, n - 1)
    elif not is_top and not is_left:
        return coord_to_num(x - (1 << (n - 1)), y - (1 << (n - 1)), n - 1) + (1 << (2*n - 2))
    elif not is_top and is_left:
        return coord_to_num(x - (1 << (n - 1)), y, n - 1) + 2 * (1 << (2*n - 2))
    else:
        return coord_to_num(x, y - (1 << (n - 1)), n - 1) + 3 * (1 << (2*n - 2))

def num_to_coord(num, n) -> tuple[int, int]:
    if n == 0:
        assert num == 1
        return (1, 1)
    
    if num <= (1<<(2*n - 2)):
        return num_to_coord(num, n - 1)
    elif num <= 2 * (1 << (2*n - 2)):
        x, y = num_to_coord(num - (1 << (2*n - 2)), n - 1)
        return (x + (1 << (n - 1)), y + (1 << (n - 1)))
    elif num <= 3 * (1 << (2*n - 2)):
        x, y = num_to_coord(num - 2 * (1 << (2*n - 2)), n - 1)
        return (x + (1 << (n - 1)), y)
    else:
        x, y = num_to_coord(num - 3 * (1 << (2*n - 2)), n - 1)
        return (x, y + (1 << (n - 1)))

for _ in range(int(input())):
    n = int(input())
    q = int(input())

    for _ in range(q):
        op, *x = input().split()

        if op == "->":
            x, y = map(int, x)
            print(coord_to_num(x, y, n))
        elif op == "<-":
            x = int(x[0])
            print(num_to_coord(x, n)[0], num_to_coord(x, n)[1])
