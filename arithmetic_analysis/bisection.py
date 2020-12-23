import numpy

def find_no_of_iterations(e, lower_limit, upper_limit):
    return int(numpy.floor((numpy.log(upper_limit - lower_limit) - numpy.log(e))/numpy.log(2))) + 1

def bisection(f, n, lower_limit, upper_limit):
    #f: function as parameter, n: number of iterations, lower and upper limits: range
    m = 0.0
    for i in range(n + 1):
        m = (lower_limit + upper_limit) / 2.0
        print(i, ") m = ", m)
        if f(m) == 0:
            print("Found the solution exactly at ", i, "th iteration at m = ", m)
            return m #if we find the exact root
        elif f(m)*f(lower_limit) < 0: upper_limit = m #otherwise as usual
        else: lower_limit = m

    print("M after ", i, " iterations = ", m)
    return m
