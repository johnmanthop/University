#all functions implemented iterativily
#so there is not recursion depth limit, and it is faster
def newton(g, gprime, x0, e):
    x_next = x0 + 1000000000000000000000
    last = 0
    counter = 0
    while abs(x_next - last) >= 0.5*(10**-e):

        x_next = x0 - g(x0) / gprime(x0)
        print("X", counter, "    = ", x0)
        print("X", counter + 1, "= ", x_next)
        print("|Xn+1 - Xn| = ", abs(x_next - x0))

        last = x0
        x0 = x_next
        counter += 1
    print("Took ", counter, " repeats")
