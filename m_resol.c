/**
 * \file m_resol.c
 * \brief Contains functions that helps to resolve a system of equations
 * \author ROSTAQI Yossef
 * \date 16 Novembre 2017
 */

#include "m_resol.h"
#include "tp1.h"

/**
 * \fn Matrix Extraction(Matrix A, int i, int j)
 * \brief Creates an extracted Matrix from A, ignoring the row i and the column j
 *
 * \param int i
 * \param int j
 * \return the extracted matrix
 */

Matrix Extraction(Matrix A, int i, int j){
    // The extracted Matrix has a dimension of A's - 1
    Matrix extracted = newMatrix(A.nb_rows - 1, A.nb_columns - 1);
    int k = 1;
    int l = 1;
    int n = 1;
    int p = 1;
    for(k = 1; k <= A.nb_rows; k++){
        // i is the row to ignore
        if(k == i)
            continue;
        // We can't exceed the Matrix's row dimension so we use modulo
        n = n%A.nb_rows;
        for(l = 1; l <= A.nb_columns; l++){
            // j is the column to ignore
            if(l == j)
                continue;
            // We can't exceed the Matrix's column dimension so we use modulo
            p = p%A.nb_columns;
            // extracted(n, p) = A(k, l)
            setElt(extracted, n, p, getElt(A, k, l));
            // We increment p which is the indice for extracted's column
            p++;
        }
        p++;
        // We increment n which is the indice for extracted's row
        n++;
    }
    return extracted;
}

/**
 * \fn E determinant(Matrix A)
 * \brief Gives the determinant of Matrix A
 *
 * \param Matrix A
 * \return the determinant (if defined) of A
 * if it's not defined it returns DBL_MAX
 */

E determinant(Matrix A){
    E det = 0.0;
    int i = 1;
    if(!isSquare(A)){
        fprintf(stderr, "Matrix isn't square, no determinant\n");
        // I chose to return "infinity" if the Matrix isn't square
        return DBL_MAX;
    }
    else{
        if(A.nb_columns == 2){
            //det = ad - bc
            det = (getElt(A, 1, 1) * getElt(A, 2, 2)) - (getElt(A, 1, 2) * getElt(A, 2, 1));
            return det;
        }

        if(A.nb_columns == 1){
            // the determinant of a Matrix of dimension 1 is the value of the Matrix
            det = getElt(A, 1, 1);
            return det;
        }

        else{
            // if the Matrix's dimension is greater than 2
            for(int j = 1; j <= A.nb_columns; j++){
                Matrix extracted = Extraction(A, i, j);
                // det = sum of (-1)^(i+j) * A(i,j) * determinant(extractedMatrix)
                det = det + (pow(-1, i + j) * getElt(A, i, j) * determinant(extracted));
                deleteMatrix(extracted);
            }
            return det;
        }
    }
}


/**
 * \fn Matrix mult_row(Matrix A, int i, E k)
 * \brief multiplies the row i of Matrix A by k
 *
 * \param Matrix A
 * \param int i
 * \param E k
 * \return a modified Matrix
 */

Matrix mult_row(Matrix A, int i, E k){
    int j = 1;
    for(j = 1; j <= A.nb_columns; j++){
        setElt(A, i, j, k * getElt(A, i, j));
    }
    return A;
}

/**
 * \fn Matrix permut_row(Matrix A, int i, int j)
 * \brief permuts the i row with the j row of Matrix A
 *
 * \param Matrix A
 * \param int i
 * \param int j
 * \return a modified Matrix
 */

Matrix permut_row(Matrix A, int i, int j){
    E tmp;
    int k = 1;
    for(k = 1; k <= A.nb_columns; k++){
        tmp = getElt(A, i, k);
        setElt(A, i, k, getElt(A, j, k));
        setElt(A, j, k, tmp);
    }
    return A;
}

/**
 * \fn Matrix add_combination(Matrix A, int i, int j, E k)
 * \brief adds to Matrix A's row i a multiplication of the row j by k
 *
 * \param Matrix A
 * \param int i
 * \param int j
 * \param E k
 * \return a modified Matrix
 */

Matrix add_combination(Matrix A, int i, int j, E k){
    int l = 1;
    for(l = 1; l <= A.nb_columns; l++){
        setElt(A, i, l, getElt(A, i, l) + (k * getElt(A, j, l)) );
    }
    return A;
}

/** 
 * \fn void copyMatrix(Matrix src, Matrix dest)
 * \brief copy the matrix src into matrix dest
 * 
 * \param Matrix src
 * \param Matrix dest
 * \return void
 * */

void copyMatrix(Matrix src, Matrix dest){
    for(int i = 1; i <= src.nb_rows; i++){
        for(int j = 1; j <= src.nb_columns; j++){
            setElt(dest, i, j, getElt(src, i, j));
        }
    }
}

/**
 * \fn Matrix pivotDeGauss(Matrix A, bool upperTriangularMatrix)
 * \brief
 *
 * \param Matrix A
 * \param bool upperTriangularMatrix
 * \return a modified Matrix
 */

Matrix pivotDeGauss(Matrix A, bool upperTriangularMatrix){
    Matrix m = newMatrix(A.nb_rows, A.nb_columns);
    copyMatrix(A, m);
    int k, i, j;
    E pivot, q;
    // Algorithme de pivot de Gauss semblable au cours (cf cours 5ieme partie)
    for(k = 1; k <= m.nb_rows; k++){
        pivot = getElt(m, k, k);
        for(i = k + 1; i <= m.nb_rows; i++){
            q = getElt(m, i, k);
            setElt(m, i, k, 0.0);
            for(j = k+1; j <= m.nb_columns; j++){
                setElt(m, i, j, getElt(m, i, j) - getElt(m, k, j) * (q/pivot) );
            }
        }
    }
    if(upperTriangularMatrix){
        return m;
    }
    else{
            i = 1;
            // Pour avoir des "1" sur la diagonale
            for(i = 1; i <= A.nb_rows; i++)
                mult_row(m, i, 1/getElt(m, i, i));
            // Pour avoir une matrice triangulaire inférieur (inférieur + supérieur = diagonale) :
            for(k = m.nb_rows; k >= 1; k--){
                pivot = getElt(m, k, k);
                for(i = k-1; i>= 1; i--){
                    q = getElt(m, i, k);
                    setElt(m, i, k, 0.0);
                    for(j = m.nb_columns; j >= k+1; j--)
                        setElt(m, i, j, getElt(m, i, j) - getElt(m, k, j) * (q/pivot) );
                }
            }
        return m;
    }
}

/**
 * \fn E determinant2(Matrix m)
 * \brief founds the determinant from a upper triangular matrix (more optimised)
 *
 * \param Matrix m
 * \return the determinant of the matrix
 * \pre m must be a upper triangular matrix
 */

E determinant2(Matrix m){
    E det = 1;
    for(int i = 1; i <= m.nb_rows; i++){
        det *= getElt(m, i, i);
    }
    return det;
}

/**
 * \fn Matrix resolution(Matrix A, Matrix B)
 * \brief This function finds the Matrix x as Ax = b
 *
 * \param Matrix A
 * \param Matrix B
 * \return The Matrix x
 */

Matrix resolution(Matrix A, Matrix B){
	Matrix tmp = newMatrix(A.nb_rows,A.nb_columns+1);
	Matrix tmp1 = setMatrixBlock(tmp, 1, 1, A);
	deleteMatrix(tmp);
	Matrix tmp2 = setMatrixBlock(tmp1, 1, A.nb_columns + 1, B);
	deleteMatrix(tmp1);
	Matrix tmp3 = pivotDeGauss(tmp2,0);
    deleteMatrix(tmp2);
    // We extract the solutions (placed where Matrix B was) into Matrix x:
	Matrix x = getMatrixBlock(tmp3, 1, A.nb_columns+1, B.nb_rows, B.nb_columns);
    deleteMatrix(tmp3);
	return x;
}

/**
 * \fn Matrix inverse(Matrix A)
 * \brief It gives the inverse matrix of A
 *
 * \param Matrix A
 * \return The inverted matrix
 */

Matrix inverse(Matrix A){
    // We'll need a bigger Matrix to work on and have (A|Id)
    Matrix tmp = newMatrix(A.nb_rows, A.nb_columns * 2);
    // Creation of the identity Matrix
    Matrix Id = newMatrix(A.nb_rows, A.nb_columns);
    int i, j;
    for(i = 1; i <= Id.nb_rows; i++){
        for(j = 1; j <= Id.nb_rows; j++){
            if(i == j)
                setElt(Id, i, j, 1);
            else
                setElt(Id, i, j, 0);
        }
    }
    Matrix tmp1 = setMatrixBlock(tmp, 1, 1, A);
    deleteMatrix(tmp);
    Matrix tmp2 = setMatrixBlock(tmp1, 1, A.nb_columns + 1, Id);
    deleteMatrix(tmp1);
    deleteMatrix(Id);
    Matrix tmp3 = pivotDeGauss(tmp2, 0);
    deleteMatrix(tmp2);
    Matrix inverted = getMatrixBlock(tmp3, 1, A.nb_columns + 1, A.nb_rows, A.nb_columns);
    deleteMatrix(tmp3);
    return inverted;
}