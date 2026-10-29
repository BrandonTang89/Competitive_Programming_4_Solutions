for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    
    def f(arr: list[int], n: int, k: int) -> int:
      freq = [0] * (n+1)
      mex = 0
      mexs = []
      for x in arr:
        freq[x] += 1
        while freq[mex] > 0:
          mex += 1
        mexs.append(mex)
      mexs.sort()
      return mexs[-k]
  
    best = f(arr, n, k)
    best_i = -1
    best_j = -1
    for i in range(n):
      for j in range(i+1, n):
        arr[i], arr[j] = arr[j], arr[i]
        cur = f(arr, n, k)
        if cur > best:
          best = cur
          best_i = i
          best_j = j
        arr[i], arr[j] = arr[j], arr[i]
    
    if best_i == -1:
      print(-1)
    else:
      print(best_i + 1, best_j + 1)