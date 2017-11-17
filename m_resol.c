#include "m_resol.h"
#include "tp1.h"

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

E determinant(Matrix A){
    E det = 0.0;
    int i = 1;
    if(!isSquare(A)){
        fprintf(stderr, "Matrix isn't square, no determinant\n");
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

Matrix mult_row(Matrix A, int i, E k){
    int j = 1;
    for(j = 1; j <= A.nb_columns; j++){
        setElt(A, i, j, k * getElt(A, i, j));
    }
    return A;
}