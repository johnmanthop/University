import numpy
import copy

def inf_norm(x):
    max = abs(x[0])
    index = 1

    while index < x.shape[0]: # Save the first compare with a while loop rather than a for in loop
        if abs(x[index]) > max:
            max = abs(x[index])
        index += 1

    return max

def gauss_seidel(A, b, e):
    solution_vector = numpy.array([0 for i in range(b.shape[0])], numpy.float64)
    last = numpy.array([10 for i in range(b.shape[0])], numpy.float64)

    counter = 0
    while inf_norm(solution_vector - last) >= 0.5*(10**-e):
        rows = 0
        counter += 1
        last = copy.copy(solution_vector)
        while rows < A.shape[0]:
            cols = 0
            sum = 0

            while cols < A.shape[1]:
                if rows != cols:
                    sum += A[rows][cols] * solution_vector[cols]
                cols += 1


            solution_vector[rows] = (b[rows] - sum) / A[rows][rows]
            rows += 1
    print("Took ", counter, " repeats")
    return solution_vector
