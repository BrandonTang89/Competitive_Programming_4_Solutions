n = int (input())
ops = ['+', '-', '*', '//']
for q in range(n):
    l = int(input())
    
    done = False
    for i in range(4):
        for j in range(4):
            for k in range(4):
                expression = "4 " + ops[i] + " 4 " + ops[j] + " 4 " + ops[k] + " 4"
                if eval(expression) == l:
                    print(expression.replace("//", "/") + " = " + str(l))
                    done = True
                    break
                
                if done: break
            if done: break
        if done: break
    else:
        print ("no solution")