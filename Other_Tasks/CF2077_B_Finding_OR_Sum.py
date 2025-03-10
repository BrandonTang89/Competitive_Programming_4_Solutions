from sys import stdout
mask_even = 0
for i in range(0, 30, 2):
    mask_even += 1 << i

mask_odd = 0
for i in range(1, 30, 2):
    mask_odd += 1 << i

ZEROS = 0
MIX = 1
ONES = 2

for _ in range(int(input())):
    print(mask_even)
    stdout.flush()
    even_res = int(input())

    print(mask_odd)
    stdout.flush()
    odd_res = int(input())

    numbers = [None] * 30

    for i in range(2, 30, 2):
        # refer to mask odd to find the even bit patterns
        at_i = odd_res & (1 << i)
        at_ip1 = odd_res & (1 << (i + 1))

        if at_i and at_ip1:
            numbers[i] = ONES
        elif at_i and not at_ip1:
            numbers[i] = ZEROS
        elif not at_i and at_ip1:
            numbers[i] = MIX
        else:
            assert False

    at_0 = odd_res & 1
    at_1 = odd_res & 2
    if not at_0 and not at_1:
        numbers[0] = ZEROS
    elif at_0 and not at_1:
        numbers[0] = MIX
    elif not at_0 and at_1:
        numbers[0] = ONES
    else:
        assert False

    for i in range(1, 30, 2):
        # refer to mask even to find the odd bit patterns
        at_i = even_res & (1 << i)
        at_ip1 = even_res & (1 << (i + 1))

        if at_i and at_ip1:
            numbers[i] = ONES
        elif at_i and not at_ip1:
            numbers[i] = ZEROS
        elif not at_i and at_ip1:
            numbers[i] = MIX
        else:
            assert False

    x = 0
    y = 0
    for i in range(0, 30):
        if numbers[i] == MIX:
            y += 1 << i
        elif numbers[i] == ONES:
            x += 1 << i
            y += 1 << i

    print("!")
    stdout.flush()
    m = int(input())
    print((x | m) + (y | m))
