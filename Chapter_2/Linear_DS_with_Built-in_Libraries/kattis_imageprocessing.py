'''
Kattis - imageprocessing
Relatively standard image processing problem.

Time: O(iw*ih*kh*kw), Space: O(iw*ih + kh*kw)
'''
ih, iw, kh, kw = map(int, input().split())
image = []
for r in range(ih):
    image.append(list(map(int, input().split())))

kernel = []
for r in range(kh):
    kernel.append(list(map(int, input().split()))[::-1])
kernel = kernel[::-1]

output_img = []
for r in range(ih - kh + 1):
    output_img.append([]);
    for c in range(iw - kw + 1):
        output_img[-1].append(0)
        for kr in range(kh):
            for kc in range(kw):
                output_img[-1][-1] += (image[r+kr][c+kc] * kernel[kr][kc])

for r in output_img:
    print(*r)