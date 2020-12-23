import random

def bisection_mod(f, upper_limit, lower_limit, e):
    m = 0.0
    last = 1000000
    counter = 0
    while (abs(m - last)) >= 0.5*(10**-e):
        last = m
        m = random.uniform(upper_limit, lower_limit)

        print(counter, ") m = ", m)

        if f(m) == 0:
            print("Found the solution exactly at ", counter, "th iteration at m = ", m)
            return m #if we find the exact root
        elif f(m)*f(lower_limit) < 0: upper_limit = m #otherwise as usual
        else: lower_limit = m


        counter += 1

    print("M after ", counter, " iterations = ", m)
    return m
