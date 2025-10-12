from sympy import *
primes = []

def generatePrimes(bar_show_terminal):
    def bar(prg):
        barList = list()
        barList.append("[")

        for i in range(100):
            if round(prg) == i:
                barList.append('>')
            elif round(prg) < i:
                barList.append('-')
            else:
                match i % 7:
                    case 0:
                        barList.append("M")
                    case 1:
                        barList.append("F")
                    case 2:
                        barList.append("T")
                    case 3:
                        barList.append("a")
                    case 4:
                        barList.append("l")
                    case 5:
                        barList.append("k")
                    case _:
                        barList.append("-")

        barList.append(f"] {round(prg * 10) / 10} %")
        return ''.join(barList)

    for i in range(999999):
        if isprime(i) and i > 100000:
            primes.append(i)

        progress = round((i / 999999 * 10000)) / 100

        if barBool:
            if i % 100000 == 0 or progress == 100:
                print(f"\r{bar(progress)}", end='')

    return primes
