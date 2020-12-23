def secant_mod(f, x0, x1, x2, e):
    x3 = 0
    last = 100000000000000000000000000

    counter = 0
    while abs(x3 - last) >= 0.5*(10**-e):
        q = f(x0)/f(x1)
        r = f(x2)/f(x1)
        s = f(x2)/f(x0)

        x3 = x2 - (r*(r - q)*(x2 - x1) + (1 - r)*s*(x2 - x0)) / ((q - 1)*(r - 1)*(s - 1))

        last = x0
        x0 = x3

        print(x0)
        counter += 1
    print("Took ", counter, " repeats")
