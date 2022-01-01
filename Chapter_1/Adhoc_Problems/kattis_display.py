'''
Kattis - displaymap
Decompose the 7 by 5 display into a list in a map. Note that they require a newline character
at the end of the "end" in the output.

Time: O(n), Space: O(1)
'''
display_map = {
    "1": ["    +", "    |", "    |", "    +", "    |", "    |", "    +"],
    "2": ["+---+", "    |", "    |", "+---+", "|    ", "|    ", "+---+"],
    "3": ["+---+", "    |", "    |", "+---+", "    |", "    |", "+---+"],
    "4": ["+   +", "|   |", "|   |", "+---+", "    |", "    |", "    +"],
    "5": ["+---+", "|    ", "|    ", "+---+", "    |", "    |", "+---+"],
    "6": ["+---+", "|    ", "|    ", "+---+", "|   |", "|   |", "+---+"],
    "7": ["+---+", "    |", "    |", "    +", "    |", "    |", "    +"],
    "8": ["+---+", "|   |", "|   |", "+---+", "|   |", "|   |", "+---+"],
    "9": ["+---+", "|   |", "|   |", "+---+", "    |", "    |", "+---+"],
    "0": ["+---+", "|   |", "|   |", "+   +", "|   |", "|   |", "+---+"],
    ":": [" ", " ","o", " ", "o", " "," "],
}

while True:
    s = list(input())
    if s == list("end"): 
        print("end")
        break
    for i in range(7):
        line = "  ".join([display_map[c][i] for c in s])
        print(line)
    print()
    print()