//
//  Error.c
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#include "Error.h"

double errorPQtoR(DoubleMatrix* P, DoubleMatrix* Q, DoubleMatrix* R) {
    DoubleMatrix Qt = *DoubleMatrix_transpose(Q);
    DoubleMatrix Rf = *DoubleMatrix_multiply(P, &Qt);
    
    double err = 0.0;
    for (int u = 0; u < R->height; u += 1) {
        for (int i = 0; i < R->width; i += 1) {
            double a = R->elements[u][i] - Rf.elements[u][i];
            err += a * a;
        }
    }
    return err;
}
