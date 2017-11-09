//
//  Factorization.c
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#include "Factorization.h"

#include <stdlib.h>
#include <stdio.h>
#include "Utilities.h"
#include "Error.h"

#define ALPHA 10
#define EPSILON 0.0001
#define USER thisUIRating.user
#define ITEM thisUIRating.item

void computeUserAndItemFactors(unsigned int f, DoubleMatrix* P, DoubleMatrix* Q, const RatingData* data) {
    for (int i = 0; i < f ; i += 1) { computeNextFactor(i, P, Q, data); }
}

void computeNextFactor(unsigned int f, DoubleMatrix* P, DoubleMatrix* Q, const RatingData* data) {
    UIRatings* knownRatings = RatingData_collectKnownRatingsAsUIRatings(data);
    double** res = malloc(data->userCount * sizeof(double*));
    for (int u = 0; u < data->userCount; u+= 1) {
        res[u] = malloc(data->itemCount * sizeof(double));
    }
    for (int r = 0; r < knownRatings->count; r += 1) {
        UIRating thisUIRating = knownRatings->elements[r];
        res[USER][ITEM] = thisUIRating.rating.value;
        for (int l = 0; l < f - 1; l += 1) {
            if (f == 0) break;
            res[USER][ITEM] -= P->elements[USER][l] * Q->elements[ITEM][l];
        }
        
        unsigned int nui = uimin(RatingData_numberOfRatingsByUser(data, USER), RatingData_numberOfRatingsForItem(data, ITEM));
        res[USER][ITEM] = (nui * res[USER][ITEM]) / (nui + ALPHA * (f + 1));
    }
    
    DoubleMatrix* R = RatingData_getRatingsAsDoubleMatrix(data);
    double errorNew = errorPQtoR(P, Q, R);
    double errorOld = errorNew * 2;
    
    while (errorNew / errorOld < 1 - EPSILON) {
        errorOld = errorNew;
        
        for (int u = 0; u < data->userCount; u += 1) {
            unsigned int* ratedItems = RatingData_itemsRatedByUser(data, u);
            unsigned int n = RatingData_numberOfRatingsByUser(data, u);
            
            double a = 0.0;
            double b = 0.0;
            for (int j = 0; j < n; j += 1) {
                int i = ratedItems[j];
                a += res[u][i] * Q->elements[i][f];
                b += Q->elements[i][f] * Q->elements[i][f];
            }
            
            P->elements[u][f] = a / b;
        }
        
        for (int i = 0; i < data->itemCount; i += 1) {
            unsigned int* usersWhoRated = RatingData_usersWhoRatedItem(data, i);
            unsigned int n = RatingData_numberOfRatingsForItem(data, i);
            
            double a = 0.0;
            double b = 0.0;
            for (int j = 0; j < n; j += 1) {
                int u = usersWhoRated[j];
                a += res[u][i] * P->elements[u][f];
                b += P->elements[u][f] * P->elements[u][f];
            }
            
            Q->elements[i][f] = a / b;
        }
        
        errorNew = errorPQtoR(P, Q, R);
        
        //DoubleMatrix_printNamed(P, "P nach while-Durchlauf");
        //printf("Error: %f\n", errorPQtoR(P, Q, R));
    }
    //DoubleMatrix_printNamed(P, "XXXX P AM ENDE");
    //printf("Error: %f\n", errorPQtoR(P, Q, R));
}
