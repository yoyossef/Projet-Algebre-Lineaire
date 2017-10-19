#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <perror.h>

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
    if(column > m.nb_columns || row > m.nb_rows){
        fprintf(stderr, "Erreur, vous dépassez la dimension de la matrice\n");
        exit(1);
    }
    return m.mat[row*(m.nb_columns - 1) + column - 1 - row];
}

void setElt(Matrix m, int row, int column, E val){
    if(column > m.nb_columns || row > m.nb_rows){
        fprintf(stderr, "Erreur, vous dépassez la dimension de la matrice\n");
        exit(1);
    }
    m.mat[row*(m.nb_columns - 1) + column - 1 - row] = val;
}

void deleteMatrix(Matrix m){
    free (m.mat);
}

int isSymetric(Matrix){ //0 si faux
    int i, j;
    int retour = 1;
    for(int i = 0; i < (m.nb_columns * m.nb_rows); i++){
        for(j = 0; j < (m.nb_columns * m.nb_rows); j++){
            if(getElt(m,i,j) != getElt(m,j,i) && i!=j){
                retour = 0;
        }
    }
    return retour;
}

int main(){
    Matrix m = newMatrix(5,5);
    setElt(m, 1,1, 2.5);
    E elt = getElt(m, 1, 1);
    printf("%f\n", elt);
    deleteMatrix(m);
}