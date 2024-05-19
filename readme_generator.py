# Prints out a README.md file for the project
import re, os
start_of_readme = '''# Competitive Programming 4 Solutions
My solutions to some of the [Kattis](https://open.kattis.com/) problems listed in [Competitive Programming 4](https://cpbook.net/details?cp=4).
Some [UVA Online Judge](https://onlinejudge.org/) problems are also solved on [Virtual Judge](https://vjudge.net/). 

C++ code usually requires C++17 to work.
Python code usually requires Python 3.8 to work.

# List of Kattis Questions Solved
![Auto Update](https://github.com/BrandonTang89/Competitive_Programming_4_Solutions/actions/workflows/Update_README.yml/badge.svg)
| Index | Question Title | Solution |
| ----- | -------------- | -------- |'''

print(start_of_readme)
m_file_types = {'C++': 'cpp', 'Python': 'py', 'Haskell': 'hs', 'C': 'c', 'Ocaml': 'ml', 'Rust': 'rs'}

things_to_write = []
def print_table():
    things_to_write.sort()
    solution_types = []
    for index, (q_name, sol, task) in enumerate(things_to_write):
        for k, v in m_file_types.items():
            if (sol.endswith(v)):
                solution_types.append((k, sol))
                break
        
        if (index != len(things_to_write) - 1):
            if (things_to_write[index+1][0] == q_name):
                continue
        
        line = f"| {index+1} | [{q_name}]({task}) | "
        for solution_type, solution in solution_types:
            line += f"[{solution_type}]({solution}), " 
        
        line = line[:-2] + " |"
        print(line)
        
        solution_types.clear()

solution_root = "https://github.com/BrandonTang89/Competitive_Programming_4_Solutions/blob/main"
# Get Kattis Solutions
stream = os.popen('find | grep kattis')
lines = stream.readlines()
for line in lines:
    line = line.strip()

    # Matches kattis_xxxx.py or kattis_xxxx.cpp or kattis_xxxx.hs
    m = re.search(r'\/kattis_(\w*)\.(?:py|cpp|hs|c|ml|rs)', line)

    # First capturing group is the problem name
    things_to_write.append([str(m.group(1)), solution_root + line[1:], "https://open.kattis.com/problems/" + str(m.group(1))])
    
print_table()

# Get VJudge Solutions
things_to_write.clear()
stream = os.popen('find | grep vjudge')
lines = stream.readlines()
for line in lines:
    line = line.strip()

    # Matches vjudge_xxxx_someothername.someext where the someothername is optional
    m = re.search(r'\/vjudge_([^_]*)(?:.*).(?:py|cpp|hs|c|ml|rs)', line)

    # First capturing group is the problem name
    things_to_write.append([str(m.group(1)), solution_root + line[1:], "https://vjudge.net/problem/" + str(m.group(1))])

print('''# List of Virtual Judge Questions Solved
| Index | Question Title | Solution |
| ----- | -------------- | -------- |''')
print_table()

# Get Code Forces Solutions
things_to_write.clear()
stream = os.popen('find | grep CF')
lines = stream.readlines()
for line in lines:
    line = line.strip()

    # Matches CF(ContestNumber)_(Problem)_(TaskName).(?:ext)
    m = re.search(r'CF(\d+)_([^_]+)_([^.]+)?\.(?:py|cpp|hs|c|ml|rs)', line)

    contest_number = str(m.group(1))
    question_letter = str(m.group(2))
    question_name = str(m.group(3))
    things_to_write.append([f"CF{contest_number}_{question_letter}_{question_name}", solution_root + line[1:], 
                            f"https://codeforces.com/contest/{contest_number}/problem/{question_letter}"])

print('''# List of Code Forces Questions Solved
| Index | Question Title | Solution |
| ----- | -------------- | -------- |''')

print_table()
