'''
Kattis - wordcloud
Just mainly reading comprehension and following the instructions of the problem. 

Time: O(n log n), Space: O(n)
'''
from math import ceil

tc_counter = 0
while True:
    tc_counter += 1
    cloud_w, n = map(int, input().split())
    if (cloud_w == 0) & (n == 0):
        break

    def hw(word, occ, max_occ):
        p = 8 + ceil((40 * (occ-4)) / (max_occ - 4))
        return (p, ceil((9/16) * p * len(word))) # height, width

    max_occ = 0
    words = []
    for i in range(n):
        w, occ = input().split()
        occ = int(occ)

        if (occ < 5):
            continue
        max_occ = max(max_occ, occ)
        words.append((w, occ))
        
    words.sort()
    cur_h = 0 
    cur_w = -10
    total_height = 0
    
    for word in words:
        h, w = hw(word[0], word[1], max_occ)
        if (cur_w + 10 + w) > cloud_w:
            total_height += cur_h
            cur_w = -10
            cur_h = 0

        cur_h = max(cur_h, h)
        cur_w += w + 10
    total_height += cur_h
    print(f"CLOUD {tc_counter}: {total_height}")