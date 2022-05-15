'''
Kattis - nizovi
Kinda simple output formatting question. We just maintain a running indentation counter and cur_word
that contains all the characteres to be printed in the same line.

Time: O(n), Space: O(n) where n is the length of the input string
'''
s = input()
cur_indentation = 0
cur_word = ""
for i in s:
    if (i == '{'):
        print(cur_indentation * ' ' + i)
        cur_indentation += 2
    elif (i == '}'):
        if (cur_word != ""): 
            print(cur_indentation * ' ' + cur_word)
            cur_word = ""
        cur_indentation -= 2
        cur_word += i
    elif (i == ','):
        cur_word += i
        print(cur_indentation * ' ' + cur_word)
        cur_word = ""
    else: 
        cur_word += i
if (cur_word != ""):
    print('}')