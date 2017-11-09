//
//  main.c
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Data.h"
#include "DoubleMatrix.h"
#include "Factorization.h"

#define F 4

int main(int argc, const char * argv[]) {
    //RatingData* sampleData = RatingData_readFromCSV(7, 7, "Datenset Test - jeder 3.csv");
    RatingData* sampleData = malloc(sizeof(RatingData));
    RatingData_initDummy(sampleData, 7, 7);
    
    DoubleMatrix* P = DoubleMatrix_makeFilledWithValue(F, sampleData->userCount, 2.0);
    DoubleMatrix* Q = DoubleMatrix_makeFilledWithValue(F, sampleData->itemCount, 2.0);
    
    computeUserAndItemFactors(F, P, Q, sampleData);
    
    DoubleMatrix_printNamed(RatingData_getRatingsAsDoubleMatrix(sampleData), "Datenset");
    DoubleMatrix_printNamed(P, "P");
    DoubleMatrix_printNamed(Q, "Q");
    printf("\n\n");
    
    return 0;
}
