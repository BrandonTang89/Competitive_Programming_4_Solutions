'''
Kattis - classy
Relatively simple string tokenisation + custom comparision sort question. Fun facts: the python sort
function is stable by default. Remember to pad shorter classes with middles to make them equal length.

Time: O(n log n), Space: O(n)
'''
num_tc = int(input())

rankings = {
    "upper": "3",
    "middle": "2",
    "lower": "1",
}

for _ in range(num_tc):
    n = int(input())
    people = []
    people_ranks = {}
    
    max_len = 0
    for i in range(n):
        person, rank, dummy = input().split()
        person = person[:-1]
        rank = list(rank.split('-'))
        rank = [rankings[r] for r in rank]
        rank = rank[::-1]
        max_len = max(max_len, len(rank))
        
        people.append(person)
        people_ranks[person] = (rank)
        
    for rank in people_ranks.values():
        while (len(rank) < max_len):
            rank.append("2")
    
    people.sort() # sort by lexicographic order
    people.sort(key=lambda x: people_ranks[x], reverse=True) # sort by rank
    
    for person in people:
        print(person)
    
    print("==============================")