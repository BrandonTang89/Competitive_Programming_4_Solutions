'''
Kattis - Busnumbers
DAT Based on bus numbers. Could also be solved by just normally sorting the numbers (especially for larger ranges)

Time: O(n) for the assigning, O(1) for the actual generation of the output string, Mem: O(1) 
'''
n = int(input())

dat = []
for i in range(10001):
    dat.append(False)

for bus_num in input().split(" "):
    dat[int(bus_num)]= True

ans = ""
index = 1
while (index <= 1000):
    if dat[index]:
        # Get the contiguous row
        end_ex = index
        while dat[end_ex]:
            end_ex +=1

        end_ex -= 1
        
        if end_ex == index:
            ans += str(index) + " "
        elif end_ex == index+1:
            ans += str(index) + " " + str(end_ex) + " "
        else:
            ans += str(index) + "-" + str(end_ex) + " "

        index = end_ex
    
    index +=1

print(ans[:-1])