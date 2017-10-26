#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef float E;
typedef struct matrix {
    E *mat;
    int nb_rows, nb_columns;
} Matrix;

//Fonction qui crée une matrice, en fonction des paramètres nb_rows et nb_columns

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
        fprintf(stderr, "Erreur getElt, vous dépassez la dimension de la matrice\n");
        exit(1);
    }
    return m.mat[(row-1)*m.nb_columns + column - 1];
}

void setElt(Matrix m, int row, int column, E val){
    if(column > m.nb_columns || row > m.nb_rows){
        fprintf(stderr, "Erreur setElt, vous dépassez la dimension de la matrice\n");
        exit(1);
    }
    m.mat[(row-1)*m.nb_columns + column - 1] = val;
}

void deleteMatrix(Matrix m){
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
                if(getElt(m,i,j) != getElt(m,j,i) && i!=j){
                    retour = 0;
            }
        }
        return retour;
        }
    }
    return 0;
}

void printMatrix(Matrix m){
    for(int i = 1; i <= m.nb_rows; i++){
        for(int j = 1; j <= m.nb_columns; j++){
            E elt = getElt(m, i, j);
            printf("%f\t", elt);
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
    if(a.nb_columns != b.nb_columns || a.nb_rows != b.nb_rows)
        fprintf(stderr, "Erreur addition, les deux n'ont matrices n'ont pas la même dimension\n");
    Matrix add = newMatrix(a.nb_rows, a.nb_columns);
    for(int i = 1; i <= add.nb_rows; i++){
        for(int j = 1; j <= add.nb_columns; j++){
            setElt(add, i, j, (getElt(a, i, j) + getElt(b, i, j)));
        }
    }
    return add;
}

Matrix multiplication (Matrix a, Matrix b){
    Matrix mult = newMatrix(a.nb_rows, b.nb_columns);
    if(a.nb_columns != b.nb_rows){
        free(mult.mat);
        mult.mat = NULL;
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
    Matrix m = newMatrix(2,2);
    setElt(m, 1, 1, 1);
    setElt(m, 1, 2, 2);    
    setElt(m, 2, 1, 3);
    setElt(m, 2, 2, 4);
    printMatrix(m);
    printf("Transposée : \n");
    Matrix t = transpose(m);
    printMatrix(t);
    printf("Addition : \n");
    Matrix add = addition(m, t);
    printMatrix(add);
    Matrix mult = multiplication(m, t);
    printf("Multiplication : \n");
    printMatrix(mult);
    Matrix multsc = mult_scalar(2.0, mult);
    printf("Multiplication par deux : \n");    
    printMatrix(multsc);
    deleteMatrix(multsc);
    deleteMatrix(m);
    deleteMatrix(t);
    deleteMatrix(add);
    deleteMatrix(mult);
    return 0;
}