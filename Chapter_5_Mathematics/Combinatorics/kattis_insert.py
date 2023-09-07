'''
Kattis - insert
A lot of boiler plate stuff to construct the binary tree explicitly. But the main idea is this:
let X_n be the number of permutations that construct the same binary tree as the sub-tree rooted 
at node n. Then X_n = X_left * X_right * C(size(left) + size(right), size(left)), where C is the
choose function, left and right are the left and right nodes of node n. X_null = 1. Size_n is the
number of nodes of the subtree rooted at n, including n.

Time: O(n^2), Space: O(n)
'''
from functools import lru_cache


@lru_cache(maxsize=None)
def comb(n, r):
    if (r == 0 or r == n):
        return 1
        if (n < r):
            return 0
    return (comb(n-1, r-1) + comb(n-1, r))


class Node:
    def __init__(self, val, index):
        self.val = val
        self.index = index
        self.left = None
        self.right = None


def insert(node, val, index):
    if node is None:
        return Node(val, index)
    if val < node.val:
        node.left = insert(node.left, val, index)
    else:
        node.right = insert(node.right, val, index)
    return node


def size(node):
    if node is None:
        return 0
    if sizememo[node.index] != -1:
        return sizememo[node.index]

    sizememo[node.index] = 1 + size(node.left) + size(node.right)
    return sizememo[node.index]


def x(node):
    if node is None:
        return 1
    if xmemo[node.index] != -1:
        return xmemo[node.index]

    xmemo[node.index] = x(node.left) * x(node.right) * \
        comb(size(node.left) + size(node.right), size(node.left))
    return xmemo[node.index]


while True:
    n = int(input())
    if n == 0:
        exit()
    arr = list(map(int, input().split()))
    sizememo = [-1 for _ in range(n)]
    xmemo = [-1 for _ in range(n)]

    root = Node(arr[0], 0)
    for i in range(1, n):
        insert(root, arr[i], i)

    print(x(root))
