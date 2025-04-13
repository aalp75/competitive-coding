import sys

sys.setrecursionlimit(100000)
input = sys.stdin.readline

INF = int(1e18)

def debug(*args):
    for e in args:
        print(e, file=sys.stderr)

def input_int():
    return(int(input()))

def input_list():
    return(list(map(int, input().split())))

def input_string():
    s = input()
    return(list(s[:len(s) - 1]))

def intputs_int(): # space seperated integer variable inputs
    return(map(int, input().split()))

def solve(test_case):
    debug(test_case)
    x = input_int()
    print(x)

def main():
    test_case = 1
    test_case = input_int()
    while test_case > 0:
        solve(test_case)
        test_case -= 1

main()

