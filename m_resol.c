#include "m_resol.h"
#include "tp1.h"

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