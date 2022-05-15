'''
Kattis - playfair
Another kinda timewasting problem. Just use whatever means necessary to solve since this isn't a very
time critical problem. Be careful not to miss out any of the cases.

Time: O(length of plain text), Space: O(length of plain text)
'''
key = input()
alphabet = list("abcdefghijklmnoprstuvwxyz")
square = []

counter = 0
for i in range(5):
    square.append([])
    for j in range(5):
        done = False
        if (counter < len(key)):
            while (True):
                if (key[counter] in alphabet):
                    square[i].append(key[counter])
                    alphabet.remove(key[counter])
                    counter += 1
                    done = True
                    break
                counter += 1
                if (counter >= len(key)):
                    break
        if (not done):
            square[i].append(alphabet[0])
            alphabet.pop(0)

plain_text = input()
plain_text = list("".join(plain_text.split()))

ans = ""
while (len(plain_text) > 0):
    # Check for same letter
    if (len(plain_text) == 1):
        plain_text.append("x")
    if (plain_text[0] == plain_text[1]):
        plain_text.insert(1, "x")
        continue

    (first_r, first_c) = (-1, -1)
    (second_r, second_c) = (-1, -1)

    for i in range(5):
        for j in range(5):
            if (square[i][j] == plain_text[0]):
                first_r = i
                first_c = j
            if (square[i][j] == plain_text[1]):
                second_r = i
                second_c = j

    # Check for same row
    if (first_r == second_r):
        ans += square[first_r][(first_c + 1) % 5]
        ans += square[second_r][(second_c + 1) % 5]

    # Check for same column
    elif (first_c == second_c):
        ans += square[(first_r + 1) % 5][first_c]
        ans += square[(second_r + 1) % 5][second_c]

    # Rest of the cases
    else:
        ans += square[first_r][second_c]
        ans += square[second_r][first_c]
        
    plain_text.pop(0)
    plain_text.pop(0)

print(ans.upper())
