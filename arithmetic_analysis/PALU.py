import numpy
import copy

def solve_lower_triangle_system(A, b):
    #A shold be a lower triangle matrix
    #b = contant's matrix
    solution_vector = numpy.zeros(A.shape[0])
    #solution vector = [x0, x1, ... xn]
    solution_vector[0] = b[0]#get the value of x0

    rows = 1
    cols_to_traverse = 1
    while rows < A.shape[0]:#for each row starting from the top
        cols = 0
        while cols < cols_to_traverse:#at each row we need to scan one more collumn
            solution_vector[rows] -= A[rows][cols] * solution_vector[cols]
            cols += 1
            #for each collumn at each row we multiply the value of the collumn
            #with the value of the corresponding xn (that has been found in a previous iteration)
        solution_vector[rows] += b[rows] #add the constant
        cols_to_traverse += 1
        rows += 1
        #ex:  #the lower triangle matrix always has 1 at the diagonal
        ############
        #1  0  0|  1 first  row: set x0 = 1
        #4  1  0|  1 second row: do x1 = - 4*x0 + 1
        #7  8  1|  1 third  row: do x2 = -7*x0 - 8*x1 + 1
        ############
    return solution_vector

def solve_upper_triangle_system(A, b):
    #A should be upper triangle matrix
    #b = constant's matrix
    solution_vector = numpy.zeros(A.shape[0])
    solution_vector[A.shape[0] - 1] = b[A.shape[0] - 1] / A[A.shape[0]-1][A.shape[1]-1]

    rows = A.shape[0] - 2
    cols_to_traverse = 1
    while rows >= 0:
        cols = A.shape[1] - 1
        while cols > cols_to_traverse:
            solution_vector[rows] -= A[rows][cols] * solution_vector[cols]
            cols -= 1
        solution_vector[rows] += b[rows]
        solution_vector[rows] /= A[rows][rows] #the upper triangle matrix
        #does not have 1s in the diagonal so we need to devide with the diagonal value
        cols_to_traverse -= 1
        rows -= 1

    return solution_vector

def find_permutation_matrix(A_org):
    A = A_org #make a copy of the original matrix
    P = numpy.identity(A.shape[0])
    #A is the premutated copy of A_org so both are preserved after the function call
    #I don't compute A as P*A_org because it is slower

    cols = 0
    while cols < A.shape[1]:#technically shape[0] should be equal to shape[1]
        max = A[cols][cols]
        max_index = cols
        rows = cols

        while rows < A.shape[0]:
            if abs(A[rows][cols]) > abs(max):
                max = A[rows][cols]
                max_index = rows
            rows += 1

        #doing the A swaps here is faster than multiplying with P later
        A[[cols, max_index]] = A[[max_index, cols]]
        P[[cols, max_index]] = P[[max_index, cols]]

        cols += 1

    return (P, A)

def factorize_LU(A):
    #Do gauss elimination on A and In at the same time
    In = numpy.identity(A.shape[0])

    rows = 0
    while rows < A.shape[0]:
        if A[rows][rows] != 0:
            rows_temp = rows + 1

            while rows_temp < A.shape[0]:
                factor = float(A[rows_temp][rows]) / A[rows][rows]
                A[rows_temp, :] = A[rows_temp, :] - factor * A[rows, :]
                In[rows_temp, rows] = factor
                rows_temp += 1
        #since this matrix is permutated, if there is at least a non-zero element in the collumn
        #then the diagonal value is non zero
        #if the diagonal is zero, then all values under it are also zero
        #so there is no need to compute anything
        rows += 1

    return (In, A)#return In as L and A as U

def solve_with_LU_factorization(A, b):
    res = find_permutation_matrix(copy.copy(A)) #Pass a copy of the array so it is not changed during the algorithm
    P = res[0]
    A_permutated = res[1]


    res = factorize_LU(copy.copy(A_permutated))
    L = res[0]
    U = res[1]
    y = solve_lower_triangle_system(copy.copy(L), numpy.dot(P, b))
    x = solve_upper_triangle_system(copy.copy(U), copy.copy(y))
    return x
