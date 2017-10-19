#include <stdio.h>
#include <stdlib.h>

typedef float E;
typedef struct matrix {
    E *mat;
    int nb_rows, nb_columns;
} Matrix;

Matrix newMatrix(int nb_rows, int nb_columns){
    Matrix m;
    m.mat = malloc(nb_rows * nb_columns * sizeof(E));
    m.nb_rows = nb_rows;
    m.nb_columns = nb_columns;
    return m;
}

E getElt(Matrix m, int row, int column){
    return m.mat[row*(m.nb_columns - 1) + column - 1 - row];
}

void setElt(Matrix m, int row, int column, E val){
    m.mat[row*(m.nb_columns - 1) + column - 1 - row] = val;
}

void deleteMatrix(Matrix m){
    free (m.mat);
}

int main(){
    Matrix m = newMatrix(5,5);
    setElt(m, 1,1, 2.5);
    E elt = getElt(m, 1, 1);
    printf("%f\n", elt);
    deleteMatrix(m);
}