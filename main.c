#include "m_resol.h"
#include "tp1.h"

//Creates a Matrix with nb_rows rows and nb_columns columns

Matrix newMatrix(int nb_rows, int nb_columns){
    Matrix m;
    m.mat = malloc(nb_rows * nb_columns * sizeof(E));
    m.nb_rows = nb_rows;
    m.nb_columns = nb_columns;
    return m;
}

E getElt(Matrix m, int row, int column){
    //Le tableau étant d'une dimension, voici une manière (pas très intuitive) de récupérer
    //l'élément d'une cellule d'une matrice donné.
    if(column > m.nb_columns || row > m.nb_rows || column < 1 || row < 1){
        fprintf(stderr, "Error getElt: the Matrix's dimensions has been exceeded, row = %d, column = %d\n\n", row, column);
        exit(1);
    }
    return m.mat[(row-1)*m.nb_columns + column - 1];
}

void setElt(Matrix m, int row, int column, E val){
    if(column > m.nb_columns || row > m.nb_rows){
        fprintf(stderr, "Error setElt: the Matrix's dimensions has been exceeded, row = %d, column = %d, val = %f\n\n", row, column, val);
        exit(1);
    }
    // printf("YES setElt: row = %d, column = %d, val = %f\n\n", row, column, val);
    m.mat[(row-1)*m.nb_columns + column - 1] = val;
}

void deleteMatrix(Matrix m){
    m.nb_columns = 0;
    m.nb_columns = 0;
    free (m.mat);
}

int isSquare(Matrix m){
    return (m.nb_columns == m.nb_rows);
}

int isSymetric(Matrix m){ //0 si faux
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

Matrix transpose(Matrix m){
    Matrix t = newMatrix(m.nb_columns, m.nb_rows);
    for(int i = 1; i <= t.nb_rows; i++){
        for(int j = 1 ; j <= t.nb_columns; j++){
            setElt(t, i, j, getElt(m, j, i));
        }
    }
    return t;
}

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

Matrix mult_scalar(E sc, Matrix m){
    Matrix mult = newMatrix(m.nb_rows, m.nb_columns);
    for(int i = 1; i <= m.nb_rows; i++){
        for(int j = 1; j <= m.nb_columns; j++){
            setElt(mult, i, j, sc*getElt(m, i, j));
        }
    }
    return mult;
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
    Matrix C = newMatrix(4,4);
    setElt(C, 1, 1, 1); setElt(C, 1, 2, 2); setElt(C, 1, 3, 3); setElt(C, 1, 4, 4);
    setElt(C, 2, 1, 5); setElt(C, 2, 2, -6); setElt(C, 2, 3, 8); setElt(C, 2, 4, 9);
    setElt(C, 3, 1, 67); setElt(C, 3, 2, -42); setElt(C, 3, 3, 6); setElt(C, 3, 4, 5);
    setElt(C, 4, 1, 8); setElt(C, 4, 2, 9); setElt(C, 4, 3, 19); setElt(C, 4, 4, 3);
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
    
    double a = determinant(A);
    if(a != DBL_MAX)
        printf("Determinant of A: %lf\n", a);
    double b = determinant(B);
    if(b != DBL_MAX)
        printf("Determinant of B: %lf\n", b);
    double c = determinant(C);
    if(c != DBL_MAX)
        printf("Determinant of C: %lf\n", c);
    deleteMatrix(A);
    deleteMatrix(B);
    deleteMatrix(C);
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
    return 0;
}