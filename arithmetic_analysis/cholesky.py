import numpy
import math

def cholesky(A):
    lower = numpy.zeros((A.shape[0], A.shape[1]))#Start with zero matrix

    rows = 0
    while rows < A.shape[0]:
        cols = 0
        while cols <= rows: #cols iterate from 0 to rows because the matrix is lower
            if cols == rows:
                #Diagonal values have the following formula
                sum = 0

                for element in lower[rows]:
                    sum += element ** 2
                lower[rows][cols] = math.sqrt(A[rows][cols] - sum)

            else:
                sum = 0
                k = 0
                while k < cols:
                    sum +=  lower[rows][k] * lower[cols][k]
                    k += 1
                lower[rows][cols] = (A[rows][cols] - sum) / lower[cols][cols]
            cols += 1
        rows += 1
    return lower
