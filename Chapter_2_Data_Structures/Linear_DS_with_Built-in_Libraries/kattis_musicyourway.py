'''
Kattis - musicyourway
Relatively easy stable sorting problem since python's sort is stable by default. 

Time: O(nm log n), Space: O(n)
'''
attributes = list(input().split())
hashmap = {}
for index, attribute in enumerate(attributes):
    hashmap[attribute] = index

n = int(input())
songs = []
for i in range(n):
    songs.append(list(input().split()))
    
m = int(input())
for i in range(m):
    att = input()
    songs.sort(key=lambda x: x[hashmap[att]])
    
    print(" ".join(attributes))
    for song in songs:
        print(" ".join(song))
    print()