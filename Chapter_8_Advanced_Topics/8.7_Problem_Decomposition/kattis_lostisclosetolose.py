'''
Kattis - lostisclosetolose
String Processing. Relatively adhoc, use regex to speed up abit. Just do a O(n^2) string comparisons, to see
if any word is close to any other word. Do so in O(len(a) + len(b)) time with a simple linear sweep.

Time: O(n^2 * max_length_of_word)))
'''
from sys import stdin
import re
allcores = set()
for line in stdin:
    line = line.strip().lower()
    if line == "***": break
    line = re.sub('[^a-z ]','',line)
    line = re.sub('[."]', '', line)
    
    for word in line.split():
        allcores.add(word)
    
w = sorted(list(allcores))
n = len(w)

hasstuff = False
for i in range(n):
    similar_words = []
    for j in range(n):
        if i == j: continue
        a = w[i]
        b = w[j]
        swapped = False
        if len(a) > len(b):
            a,b = b,a
            swapped = True
        if len(a) + 1 == len(b):
            c = 0
            ai = 0
            bi = 0
            while ai < len(a) and bi < len(b) and c < 2:
                if a[ai] == b[bi]:
                    ai += 1
                    bi += 1
                else:
                    bi += 1
                    c += 1
            
            if c < 2:
                if swapped:
                    similar_words.append(a)
                else:
                    similar_words.append(b)
        
        if len(a) == len(b):
            c = 0
            issue1 = -1
            issue2 = -1
            for k in range(len(a)):
                if a[k] != b[k]:
                    if c == 0:
                        issue1 = k
                    else:
                        issue2 = k
                    c += 1
            if c == 1:
                similar_words.append(b)
                
            elif c == 2:
                if issue2-issue1 == 1 and a[issue1] == b[issue2] and a[issue2] == b[issue1]:
                    similar_words.append(b)
    
    if len(similar_words) > 0:
        print(w[i] + ": " + " ".join(similar_words))
        hasstuff = True

if not hasstuff:
    print("***")