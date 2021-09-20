'''
Kattis - pig latin
Easy adhoc question
Time: O(num_words) Mem: O(num_words)
'''
from sys import stdin

vowels = {"a","e","i","o","u", "y"}
for line in stdin:
    if line == '':
        break

    words = line.split()

    #print(words)
    pig_words = []
    for word in words:
        if word[0] in vowels:
            pig_words.append(word + "yay")
        
        else:
            pig_word = ""
            i=0
            for index,char in enumerate(word):
                if char not in vowels:
                    pig_word += char
                    i+=1
                else:
                    break
            
            #print("pw", pig_word)
            pig_word = (str(word[i:]) + pig_word) + "ay"
            pig_words.append(pig_word)

    #print(pig_words)
    l = " ".join(pig_words)
    print(l)
