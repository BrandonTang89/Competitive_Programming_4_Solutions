'''
Kattis - R2
Basic IO, Solved by Tzu En

Time: O(1), Mem: O(1)
'''

N_and_P = input()
N_and_P_splited = N_and_P.split(" ")

print(int(N_and_P_splited[1]) * 2 - int(N_and_P_splited[0]) )