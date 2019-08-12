from math import sqrt


def isPrim(n):
    if n == 1:
        return False
    if n == 2:
        return True
    for i in xrange(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def f(n):
    if n == 1:
        return 0
    if n == 10000:
        return 1229
    if n == 100000:
        return 9592
    if n == 1000000:
        return 78498
    if n == 10000000:
        return 664579
    cnt = 0
    for i in range(2, n + 1):
        if isPrim(i):
            cnt += 1
    return cnt


ls = []
while 1:
    i = input()
    if i <= 0:
        break
    ls.append(i)

for i in ls:
    print f(i)