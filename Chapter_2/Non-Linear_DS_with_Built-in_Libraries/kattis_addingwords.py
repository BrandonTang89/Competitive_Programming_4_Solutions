'''
Kattis - addingwords
Generally pretty simple, just remember to remove the old definition of word from the inverse
hashmap when it is redefined.

Time: O(n), Space: O(n)
'''
from sys import stdin
hashmap = {}
inverse_hashmap = {}

for line in stdin.readlines():
    line = line.strip()
    line = line.split()
    
    if (line[0] == "clear"):
        hashmap = {}
        inverse_hashmap = {}
    elif line[0] == "def":
        if (line[1] in hashmap):
            inverse_hashmap.pop(hashmap[line[1]])
        hashmap[line[1]] = (line[2])
        inverse_hashmap[(line[2])] = line[1]
    else:  # calc
        line = line[1:]
        print(" ".join(line), end=" ")
        line = line[:-1]
        for word in line[::2]:
            if not(word in hashmap):
                print("unknown")
                break
        else:
            line = ["(" + hashmap[word] + ")" if index%2 == 0 else word for index,word in enumerate(line)]
            line = " ".join(line)
            # print(line)
            line = eval(line)
            if (str(line) in inverse_hashmap):
                print(inverse_hashmap[str(line)])
            else:
                print("unknown")