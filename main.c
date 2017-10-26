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
        for(int i = 0; i < (m.nb_columns * m.nb_rows); i++){
            for(int j = 0; j < (m.nb_columns * m.nb_rows); j++){
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

int main(){
    Matrix m = newMatrix(2,2);
    setElt(m, 1, 1, 2.5);
    // setElt(m, 2, 2, 3.5);
    printMatrix(m);
    deleteMatrix(m);
    return 0;
}