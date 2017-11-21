#include "m_resol.h"
#include "tp1.h"

/**
 * \fn Matrix newMatrix(int nb_rows, int nb_columns)
 * \brief Creates a Matrix with nb_rows rows and nb_columns columns
 *
 * \param int nb_rows
 * \param int nb_columns
 * \return a new matrix of nb_rows rows and nb_columns columns
 */

Matrix newMatrix(int nb_rows, int nb_columns){
    Matrix m;
    m.mat = malloc(nb_rows * nb_columns * sizeof(E));
    m.nb_rows = nb_rows;
    m.nb_columns = nb_columns;
    return m;
}

/**
 * \fn E getElt(Matrix m, int row, int column)
 * \brief Gives the element at the row i and column j of the matrix m
 *
 * \param Matrix m
 * \param int row
 * \param int column
 * \return the m(i,j) element
 */

E getElt(Matrix m, int row, int column){

    if(column > m.nb_columns || row > m.nb_rows || column < 1 || row < 1){
        fprintf(stderr, "Error getElt: the Matrix's dimensions has been exceeded, row = %d, column = %d\n\n", row, column);
        exit(1);
    }
    return m.mat[(row-1)*m.nb_columns + column - 1];
}

/**
 * \fn setElt(Matrix m, int row, int column, E val)
 * \brief Sets the value of the m(i,j) element of the matrix m at "val"
 *
 * \param Matrix m
 * \param int row
 * \param int column
 * \param E val
 * \return the modified matrix
 */

void setElt(Matrix m, int row, int column, E val){
    if(column > m.nb_columns || row > m.nb_rows){
        fprintf(stderr, "Error setElt: the Matrix's dimensions has been exceeded, row = %d, column = %d, val = %f\n\n", row, column, val);
        exit(1);
    }
    // printf("YES setElt: row = %d, column = %d, val = %f\n\n", row, column, val);
    m.mat[(row-1)*m.nb_columns + column - 1] = val;
}

/**
 * \fn void deleteMatrix(Matrix m)
 * \brief Deletes a Matrix by freeing the mat array and putting its number of
 *  rows/columns at 0
 *
 * \param Matrix m
 * \return void
 */

void deleteMatrix(Matrix m){
    m.nb_columns = 0;
    m.nb_rows = 0;
    free (m.mat);
}

/**
 * \fn int isSquare(Matrix m)
 * \brief tests if the matrix is square or not
 *
 * \param Matrix m
 * \return 1 if it's square, 0 otherwise
 */

int isSquare(Matrix m){
    return (m.nb_columns == m.nb_rows);
}

/**
 * \fn int isSymetric(Matrix m)
 * \brief tests if the matrix is symetric or not
 *
 * \param Matrix m
 * \return 1 if it's symetric, 0 otherwise
 */

int isSymetric(Matrix m){
    int retour = 1;
    if(isSquare(m)){
        for(int i = 1; i <= (m.nb_rows); i++){
            for(int j = 1; j <= (m.nb_columns); j++){
                if(getElt(m,i,j) != getElt(m,j,i) && i!=j)
                    retour = 0;
            }
            return retour;
        }
    }
    return 0;
}

/**
 * \fn void printMatrix(Matrix m)
 * \brief prints the Matrix m
 *
 * \param Matrix m
 * \return void
 */

void printMatrix(Matrix m){
    if(m.nb_columns != 0 || m.nb_rows != 0){
        for(int i = 1; i <= m.nb_rows; i++){
            for(int j = 1; j <= m.nb_columns; j++){
                E elt = getElt(m, i, j);
                printf("%f\t", elt);
            }
            printf("\n");
        }
        printf("\n");
    }
}

/**
 * \fn Matrix transpose(Matrix m)
 * \brief Calculates the transposed matrix m into a new matrix and returns it
 *
 * \param Matrix m
 * \return the new transposed matrix
 */

Matrix transpose(Matrix m){
    Matrix t = newMatrix(m.nb_columns, m.nb_rows);
    for(int i = 1; i <= t.nb_rows; i++){
        for(int j = 1 ; j <= t.nb_columns; j++){
            setElt(t, i, j, getElt(m, j, i));
        }
    }
    return t;
}

/**
 * \fn Matrix addition(Matrix a, Matrix b)
 * \brief Calculates the addition of a and b if they are compatible and returns
 *  a new matrix that contains the addition of a and b
 *
 * \param Matrix a
 * \param Matrix b
 * \return the additionned Matrix, or a null matrix if it's not compatible
 */

Matrix addition(Matrix a, Matrix b){
    Matrix add = newMatrix(a.nb_rows, a.nb_columns);
    if(a.nb_columns != b.nb_columns || a.nb_rows != b.nb_rows){
        free(add.mat);
        add.nb_rows = 0;
        add.nb_columns = 0;
        add.mat = NULL;
        fprintf(stderr, "Error addition: the two matrix don't have the same dimensions\n\n");
        return add;
    }
    for(int i = 1; i <= add.nb_rows; i++){
        for(int j = 1; j <= add.nb_columns; j++){
            setElt(add, i, j, (getElt(a, i, j) + getElt(b, i, j)));
        }
    }
    return add;
}

/**
 * \fn Matrix multiplication (Matrix a, Matrix b)
 * \brief Calculates the multiplication of a and b if they are compatible and returns
 *  a new matrix that contains the multiplication of a and b
 *
 * \param Matrix a
 * \param Matrix b
 * \return the multiplicated Matrix, or a null matrix if it's not compatible
 */

Matrix multiplication (Matrix a, Matrix b){
    Matrix mult = newMatrix(a.nb_rows, b.nb_columns);
    if(a.nb_columns != b.nb_rows){ //incompatible
        free(mult.mat);
        mult.nb_rows = 0;
        mult.nb_columns = 0;
        mult.mat = NULL;
        fprintf(stderr, "multiplication is incompatible\n\n");
        return mult;
    }
    E sum = 0.0;
    for(int i = 1; i <= mult.nb_rows; i++){
        for(int j = 1; j <= mult.nb_columns; j++){
            for (int k = 1; k <= a.nb_columns; k++){
                sum += getElt(a, i, k)*getElt(b, k, j);
            }
            setElt(mult, i, j, sum);
            sum = 0;            
        }
    }
    return mult;
}

/**
 * \fn Matrix mult_scalar(E sc, Matrix m)
 * \brief Multiplies the matrix m by the scalar sc and saves it into a new
 *  matrix
 *
 * \param E sc
 * \param Matrix m
 * \return the multiplicated Matrix
 */

Matrix mult_scalar(E sc, Matrix m){
    Matrix mult = newMatrix(m.nb_rows, m.nb_columns);
    for(int i = 1; i <= m.nb_rows; i++){
        for(int j = 1; j <= m.nb_columns; j++){
            setElt(mult, i, j, sc*getElt(m, i, j));
        }
    }
    return mult;
}

/**
 * \fn Matrix setMatrixBlock(Matrix A, int row, int column, Matrix B)
 * \brief Creates a new matrix C based on A which adds the block formed by Matrix B
 *
 * \param Matrix A
 * \param int row
 * \param int column
 * \param Matrix B
 * \return the Matrix C
 */

Matrix setMatrixBlock(Matrix A, int row, int column, Matrix B){
    Matrix C = newMatrix(A.nb_rows, A.nb_columns);
    int i, j;
    for(int i=1; i <= C.nb_rows; i++){
		for(int j=1; j <= C.nb_columns; j++){
			setElt(C, i, j, getElt(A,i,j));
		}
	}

	if(B.nb_rows + row - 1 > A.nb_rows || B.nb_columns + column - 1 > A.nb_columns){
		fprintf(stderr,"setMatrixBlock: Cannot set the Block \n");
        deleteMatrix(C);
		return C;
	}

	for(i = row; i < row + B.nb_rows; i++){
		for(j = column; j < column + B.nb_columns; j++){
			setElt(C, i, j, getElt(B, i-row+1, j-column+1));
		}
	}
	return C;
}

/**
 * \fn Matrix getMatrixBlock(Matrix A, int row, int column, int nb_rows, int nb_columns)
 * \brief Creates a new matrix D based on A which extracts the Matrix block
 *  of nb_rows * nb_columns from A(row, column)
 *
 * \param Matrix A
 * \param int row
 * \param int column
 * \param int nb_rows
 * \param int nb_columns
 * \return the Matrix D
 */

Matrix getMatrixBlock(Matrix A, int row, int column, int nb_rows, int nb_columns){
	Matrix D = newMatrix(nb_rows,nb_columns);
 	if(nb_rows + row-1 > A.nb_rows || nb_columns + column-1 > A.nb_columns){
		fprintf(stderr,"getMatrixBlock: Cannot get the Block \n");
        deleteMatrix(D);
		return D;
	}
	for(int i = 1; i <= nb_rows; i++){
		for(int j = 1; j <= nb_columns; j++){
			setElt(D, i, j, getElt(A, row + i - 1, column + j - 1) );
		}
	}
	return D;
}

int main(){
    Matrix A = newMatrix(3, 3);
    printf("Matrix A: \n");
    setElt(A, 1, 1, 1); setElt(A, 1, 2, 3); setElt(A, 1, 3, 5);
    setElt(A, 2, 1, 2); setElt(A, 2, 2, 5); setElt(A, 2, 3, 1);
    setElt(A, 3, 1, -1); setElt(A, 3, 2, -4); setElt(A, 3, 3, -3);
    printMatrix(A);
    Matrix B = newMatrix(2, 3);
    printf("Matrix B: \n");
    setElt(B, 1, 1, 1); setElt(B, 1, 2, 4); setElt(B, 1, 3, 2);
    setElt(B, 2, 1, 2); setElt(B, 2, 2, 5); setElt(B, 2, 3, 1);
    printMatrix(B);
    Matrix G = newMatrix(4,4);
    setElt(G, 1, 1, 1); setElt(G, 1, 2, 2); setElt(G, 1, 3, 3); setElt(G, 1, 4, 4);
    setElt(G, 2, 1, 5); setElt(G, 2, 2, -6); setElt(G, 2, 3, 8); setElt(G, 2, 4, 9);
    setElt(G, 3, 1, 67); setElt(G, 3, 2, -42); setElt(G, 3, 3, 6); setElt(G, 3, 4, 5);
    setElt(G, 4, 1, 8); setElt(G, 4, 2, 9); setElt(G, 4, 3, 19); setElt(G, 4, 4, 3);
    if(isSquare(A))
        printf("A is square\n");
    else
        printf("A isn't square\n");

    if(isSquare(B))
        printf("B is square\n");
    else
        printf("B isn't square\n");

    if(isSymetric(A))
        printf("A is symetric\n");
    else
        printf("A isn't symetric\n");

    if(isSymetric(B))
        printf("B is symetric\n");
    else
        printf("B isn't symetric\n");

    printf("Transposée de A : \n");
    Matrix tA = transpose(A);
    printMatrix(tA);

    printf("Transposée de B : \n");
    Matrix tB = transpose(B);
    printMatrix(tB);

    printf("Addition A + B : \n");
    Matrix add_a_b = addition(A, B);
    printMatrix(add_a_b);

    printf("Addition B + A : \n");
    Matrix add_b_a = addition(B, A);
    printMatrix(add_b_a);

    printf("Multiplication A * B : \n");
    Matrix mult_a_b = multiplication(A, B);
    printMatrix(mult_a_b);

    printf("Multiplication B * A : \n");
    Matrix mult_b_a = multiplication(B, A);
    printMatrix(mult_b_a);

    printf("Multiplication tA * B \n");
    Matrix mult_ta_b = multiplication(tA, B);
    printMatrix(mult_ta_b);

    printf("Multiplication tB * A \n");
    Matrix mult_tb_a = multiplication(tB, A);
    printMatrix(mult_tb_a);

    printf("Addition A + tA \n");
    Matrix add_ta_a = addition(tA, A);
    printMatrix(add_ta_a);

    printf("Multiplication of A by 5 : \n");    
    Matrix multsc_a = mult_scalar(5.0, A);
    printMatrix(multsc_a);

    printf("Multiplication of B by 3 : \n");    
    Matrix multsc_b = mult_scalar(3.0, B);
    printMatrix(multsc_b);

    if(isSymetric(add_ta_a))
        printf("tA + A is symetric\n");
    else
        printf("tA + A isn't symetric\n");

    printf("Matrix C = setMatrixBlock(A, 2, 1, B)\n");
    Matrix C = setMatrixBlock(A, 2, 1, B);
    printMatrix(C);

    printf("Matrix D = getMatrixBlock(A, 1, 1, 2, 2)\n");
    Matrix D = getMatrixBlock(A, 1, 1, 2, 2);
    printMatrix(D);

    double a = determinant(A);
    if(a != DBL_MAX)
        printf("Determinant of A: %lf\n", a);

    double b = determinant(B);
    if(b != DBL_MAX)
        printf("Determinant of B: %lf\n", b);

    double g = determinant(G);
    if(g != DBL_MAX)
        printf("Determinant of G: %lf\n", g);

    Matrix gauss = pivotDeGauss(A, true);
    double detgauss = determinant2(gauss);
    printMatrix(gauss);
    printf("Determinant of A : %lf\n", detgauss);
    deleteMatrix(gauss);
    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
    deleteMatrix(D);
    deleteMatrix(G);
    deleteMatrix(tA);
    deleteMatrix(tB);
    deleteMatrix(add_a_b);
    deleteMatrix(add_b_a);
    deleteMatrix(add_ta_a);
    deleteMatrix(mult_tb_a);
    deleteMatrix(mult_ta_b);
    deleteMatrix(mult_b_a);
    deleteMatrix(mult_a_b);
    deleteMatrix(multsc_a);
    deleteMatrix(multsc_b);
    // printf("%f\n %d\n", B.mat[0], B.nb_rows);
    return 0;
}