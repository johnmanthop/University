

def newton_mod(g, gprime1, gprime2, x0, e):
    x_next = 1000000000000000000000
    last = 0

    counter = 0
    while abs(x_next - last) >= 0.5*(10**-e):

        x_next = x0 - g(x0)/gprime1(x0) - 0.5*( ((g(x0)**2) * gprime2(x0)) / (gprime1(x0)**3) )
        print("Xn          = ", x0)
        print("Xn+1        = ", x_next)
        print("|Xn+1 - Xn| = ", abs(x_next - x0))

        last = x0
        x0 = x_next
        counter += 1
        
    print("Took ", counter, " repeats")
