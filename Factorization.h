//
//  Factorization.h
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#ifndef Factorization_h
#define Factorization_h

#include "Data.h"
#include "DoubleMatrix.h"

void computeUserAndItemFactors(unsigned int f, DoubleMatrix* P, DoubleMatrix* Q, const RatingData* data);
void computeNextFactor(unsigned int f, DoubleMatrix* P, DoubleMatrix* Q, const RatingData* data);

#endif /* Factorization_h */
