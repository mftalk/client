from sympy import *
primes = []

def generatePrimes(bar_show_terminal=False):
    def bar(prg):
        barList = list()
        barList.append("[")

        for i in range(100):
            if round(prg) == i:
                barList.append('>')
            elif round(prg) < i:
                barList.append('-')
            else:
                barList.append('=')

        barList.append(f"] {round(prg * 10) / 10} %")
        return ''.join(barList)

    for i in range(999999):
        if isprime(i) and i > 100000:
            primes.append(i)

        progress = round((i / 999999 * 10000)) / 100

        if bar_show_terminal:
            if i % 100000 == 0 or progress == 100:
                print(f"\r{bar(progress)}", end='')
    print("\n")
    return primes
