#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef float E;
typedef struct matrix {
    E *mat;
    int nb_rows, nb_columns;
} Matrix;

Matrix newMatrix(int nb_rows, int nb_columns);

E getElt(Matrix m, int row, int column);

void setElt(Matrix m, int row, int column, E val);

void deleteMatrix(Matrix m);

int isSquare(Matrix m);

int isSymetric(Matrix m);

void printMatrix(Matrix m);

Matrix transpose(Matrix m);

Matrix addition(Matrix a, Matrix b);

Matrix multiplication (Matrix a, Matrix b);

Matrix mult_scalar(E sc, Matrix m);