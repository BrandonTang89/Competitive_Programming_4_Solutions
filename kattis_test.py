from time import perf_counter_ns

MOD=int(1e9) + 7;
def fexp_mod(b, p):
    if (p == 0): return 1
    if (p == 1): return b

    if (p & 1):
        return (fexp_mod(b, p>>1)*fexp_mod(b, p>>1)*b)
    else:
        return fexp_mod(b, p>>1)*fexp_mod(b, p>>1)
def slow_exp(b, p):
    a = 1
    for i in range(p):
        a = (a*b)
    return a

def show_timeit(command, setup):
    print(setup + '; ' + command + ':')
    print(timeit.timeit(command, setup))
    print()


start = perf_counter_ns()
for _ in range(100):
    x = pow(3,100000)
end = perf_counter_ns()
print("pow:      ", end-start )


start = perf_counter_ns()
for _ in range(100):
    x = fexp_mod(3,100000)
end = perf_counter_ns()
print("fast_exp: ", end-start )

start = perf_counter_ns()
for _ in range(100):
    x = slow_exp(3,100000)
end = perf_counter_ns()
print("slow exp: ", end-start)





# show_timeit("slow_exp(2,1000000, MOD)", "MOD=int(1e9) + 7")
# show_timeit("pow(2,1000000, MOD)", "MOD=int(1e9) + 7")