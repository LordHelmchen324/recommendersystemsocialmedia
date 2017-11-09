//
//  DoubleMatrix.h
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#ifndef DoubleMatrix_h
#define DoubleMatrix_h

typedef struct {
    double** elements;
    unsigned int width;
    unsigned int height;
} DoubleMatrix;

DoubleMatrix* DoubleMatrix_make(unsigned int width, unsigned height);
DoubleMatrix* DoubleMatrix_makeFilledWithValue(unsigned width, unsigned int height, double value);
void DoubleMatrix_init(DoubleMatrix* matrix, unsigned int width, unsigned int height);
DoubleMatrix* DoubleMatrix_copy(DoubleMatrix* m);
void DoubleMatrix_copyValuesFromAtoB(DoubleMatrix* A, DoubleMatrix* B);
void DoubleMatrix_fillWithValue(DoubleMatrix* matrix, double value);

DoubleMatrix* DoubleMatrix_multiply(const DoubleMatrix* a, const DoubleMatrix* b);
DoubleMatrix* DoubleMatrix_transpose(const DoubleMatrix* m);

void DoubleMatrix_print(const DoubleMatrix* m);
void DoubleMatrix_printNamed(const DoubleMatrix* m, char* name);

#endif /* DoubleMatrix_h */
