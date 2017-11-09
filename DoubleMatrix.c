//
//  DoubleMatrix.c
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#include "DoubleMatrix.h"

#include <stdlib.h>
#include <stdio.h>

DoubleMatrix* DoubleMatrix_make(unsigned int width, unsigned height) {
    DoubleMatrix* m = malloc(sizeof(DoubleMatrix));
    DoubleMatrix_init(m, width, height);
    return m;
}

DoubleMatrix* DoubleMatrix_makeFilledWithValue(unsigned width, unsigned int height, double value) {
    DoubleMatrix* m = DoubleMatrix_make(width, height);
    DoubleMatrix_fillWithValue(m, value);
    return m;
}

void DoubleMatrix_init(DoubleMatrix* matrix, unsigned int width, unsigned int height) {
    matrix->width = width;
    matrix->height = height;
    matrix->elements = malloc(height * sizeof(double*));
    for (int l = 0; l < height; l += 1) {
        matrix->elements[l] = calloc(width, sizeof(double));
    }
}

DoubleMatrix* DoubleMatrix_copy(DoubleMatrix* m) {
    DoubleMatrix* copy = malloc(sizeof(DoubleMatrix));
    DoubleMatrix_init(copy, m->width, m->height);
    
    DoubleMatrix_copyValuesFromAtoB(m, copy);
    return copy;
}

void DoubleMatrix_copyValuesFromAtoB(DoubleMatrix* A, DoubleMatrix* B) {
    for (int i = 0; i < A->height; i += 1) {
        for (int j = 0; j < B->width; j += 1) {
            B->elements[i][j] = A->elements[i][j];
        }
    }
}

void DoubleMatrix_fillWithValue(DoubleMatrix* matrix, double value) {
    for (int i = 0; i < matrix->height; i += 1) {
        for (int j = 0; j < matrix->width; j += 1) {
            matrix->elements[i][j] = value;
        }
    }
}

DoubleMatrix* DoubleMatrix_multiply(const DoubleMatrix* a, const DoubleMatrix* b) {
    DoubleMatrix* result = malloc(sizeof(DoubleMatrix));
    DoubleMatrix_init(result, b->width, a->height);
    for (int i = 0; i < result->height; i += 1) {
        for (int j = 0; j < result->width; j += 1) {
            double sum = 0.0;
            for (int k = 0; k < a->width; k += 1) {
                sum += a->elements[i][k] * b->elements[k][j];
            }
            result->elements[i][j] = sum;
        }
    }
    return result;
}

DoubleMatrix* DoubleMatrix_transpose(const DoubleMatrix* m) {
    DoubleMatrix* result = malloc(sizeof(DoubleMatrix));
    DoubleMatrix_init(result, m->height, m->width);
    for (int i = 0; i < m->height; i += 1) {
        for (int j = 0; j < m->width; j += 1) {
            result->elements[j][i] = m->elements[i][j];
        }
    }
    return result;
}

void DoubleMatrix_print(const DoubleMatrix* m) {
    for (int i = 0; i < m->height; i += 1) {
        printf("| ");
        for (int j = 0; j < m->width - 1; j += 1) {
            printf("%6.2f, ", m->elements[i][j]);
        }
        printf("%6.2f |\n", m->elements[i][m->width - 1]);
    }
}

void DoubleMatrix_printNamed(const DoubleMatrix* m, char* name) {
    printf("\n%s:\n", name);
    DoubleMatrix_print(m);
}
