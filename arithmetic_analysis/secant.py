
def secant(g, x0, x1, e):
    x_next = x0 + 1000000000000000000000
    counter = 0
    #It is x_next - x0 instead of x_next - x1 beacause at the start of every loop
    #x0 has the value of the previous x1
    while abs(x_next - x0) >= 0.5*(10**-e):
        x_next = x1 - g(x1)*(x1 - x0)/(g(x1) - g(x0))

        print("Xn-1        = ", x0)
        print("Xn          = ", x1)
        print("Xn+1        = ", x_next)
        print("|Xn+1 - Xn| = ", abs(x_next - x1))

        x0 = x1
        x1 = x_next
        counter += 1
    print("Took ", counter, " repeats")
