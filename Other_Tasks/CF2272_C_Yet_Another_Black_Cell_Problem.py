for _ in range(int(input())):
  n, extra = map(int, input().split())
  arr = list(map(int, input().split()))
  
  def can_do(k: int, arr: list = arr, n: int = n, extra: int = extra) -> bool:
    prev = -int(1e9)
    
    i = 0 # next one to fill in
    ex_used = 0
    while i < n:
      if i + 1 < n and arr[i+1] - arr[i] <= k:
      # we try to get the next 2
        prev = arr[i+1]
        i += 2
        continue
        
      # we try to get the next 1 
      if arr[i] - prev <= k:
        prev = arr[i]
        i += 1
        continue
      
      # we just use an extra 
      ex_used += 1
      prev = arr[i] + k
      i += 1
      
    return ex_used <= extra
  
  l = 1
  r = max(arr)
  while l < r:
    m = (l + r) // 2
    if can_do(m):
      r = m
    else:
      l = m + 1
      
  print(l)
  