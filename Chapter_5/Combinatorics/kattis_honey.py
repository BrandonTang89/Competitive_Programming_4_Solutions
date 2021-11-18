'''
Kattis - honey
Hm, the CP way to solve this is just to make a few terms and then throw it into OEIS and get the
first 14 terms. This is what I did. How it really works?... im not too sure

Maybe ill get back to it someday (or maybe not)
Time: O(1), Space: O(1)
'''
a = [1, 0, 6, 12, 90, 360, 2040, 10080, 54810, 290640, 1588356, 8676360, 47977776, 266378112, 1488801600, 8355739392, 47104393050,
     266482019232, 1512589408044, 8610448069080, 49144928795820, 281164160225520, 1612061452900080, 9261029179733760, 53299490722049520]

q = int(input())
for _ in range(q):
    n = int(input())
    print(a[n])