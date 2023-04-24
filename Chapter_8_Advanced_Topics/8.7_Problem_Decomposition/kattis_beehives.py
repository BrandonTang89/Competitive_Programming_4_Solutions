'''
Kattis - beehives
Entry level geom question. Just test how many points are at least d distance from all other points.
Time: O(n^2), Space: O(n)
'''
def dist(a, b):
    (x1, y1) = a
    (x2, y2) = b
    return ((x1-x2)**2 + (y1-y2)**2)**0.5
while True:
    d, n = input().split()
    d = float(d)
    n = int(n)
    if n==0: break
    
    points = [map(float, input().split()) for _ in range(n)]
    points = [(x, y) for x, y in points]
    
    num_sweet = 0
    for i in range(n):
        issweet = True
        for j in range(n):
            if i == j:
                continue
            
            if dist(points[i], points[j]) <= d:
                issweet = False
                break
        
        num_sweet += issweet
    print(f"{n-num_sweet} sour, {num_sweet} sweet")