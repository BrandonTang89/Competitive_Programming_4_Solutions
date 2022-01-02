'''
Kattis - eligibility
Kinda a time waster, easy.

Time: O(n), Space: O(1)
'''
n = int(input())
for _ in range(n):
    name, post, born, course = input().split()
    
    ans = "coach petitions"
    if int(post[:4]) >= 2010:
        ans = "eligible"
    elif int(born[:4]) >= 1991 :
        ans = "eligible"
    elif int(course) > 40:
        ans = "ineligible"
    
    print(name, ans)