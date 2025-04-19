def prune(arr):
    # remove any left bs
    # remove any right ps
    n = len(arr)
    num_left_bs = 0
    for i in range(n):
        if arr[i] == "B":
            num_left_bs += 1
        else:
            break
    num_right_ps = 0
    for i in range(n - 1, -1, -1):
        if arr[i] == "P":
            num_right_ps += 1
        else:
            break

    return arr[num_left_bs : n - num_right_ps]


def f(n: int) -> int:
    if n % 2 == 0:
        k = n // 2
        return k * (k + 1)
    else:
        k = n // 2
        return (k + 1) * (k + 1)


for _ in range(int(input())):
    n = int(input())
    arr = list(input())
    arr = prune(arr)
    n = len(arr)

    num_p_on_left = [0] * n
    num_b_on_right = [0] * n

    for i in range(n):
        num_p_on_left[i] = (num_p_on_left[i - 1] if i > 0 else 0) + (arr[i] == "P")

    for i in range(n - 1, -1, -1):
        num_b_on_right[i] = (num_b_on_right[i + 1] if i < n - 1 else 0) + (
            arr[i] == "B"
        )

    # print("arr", arr)
    ans = 0
    st: list = []
    p_edit = 0
    for i in range(n):
        if arr[i] == "P":
            if st and st[-1][0] == "P":
                ans += num_b_on_right[i]
                # print("added", num_b_on_right[i])
                st.pop()
                p_edit += 2
            else:
                st.append((arr[i], None))
        elif arr[i] == "B":
            if st and st[-1][0] == "B":
                ans += st[-1][1]
                # print("added", st[-1][1])
                st.pop()
            else:
                st.append((arr[i], num_p_on_left[i] - p_edit))
        # print(st)

    arr = prune([x[0] for x in st])
    # print("arr", arr)

    ans += f(len(arr) // 2)
    print(ans)
    