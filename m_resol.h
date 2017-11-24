#ifndef __M_RESOL_H
#define __M_RESOL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include "tp1.h"

typedef int bool;
#define true 1
#define false 0

Matrix Extraction(Matrix A, int i, int j);

E determinant(Matrix A);

Matrix mult_row(Matrix A, int i, E k);

Matrix permut_row(Matrix A, int i, int j);

Matrix add_combination(Matrix A, int i, int j, E k);

void copyMatrix(Matrix src, Matrix dest);

Matrix pivotDeGauss(Matrix A, bool upperTriangularMatrix);

E determinant2(Matrix m);

Matrix resolution(Matrix A, Matrix x);

Matrix inverse(Matrix A);

void decomposition_L_U(Matrix A, Matrix L, Matrix U);

#endif