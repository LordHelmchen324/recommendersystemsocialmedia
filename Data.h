//
//  Data.h
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#ifndef Data_h
#define Data_h

#include <stdbool.h>
#include "DoubleMatrix.h"

#define NAN                 0.0
#define GOOD                3.0
#define OKAY                2.0
#define BAD                 1.0

typedef struct {
    bool known;
    double value;
} Rating;

typedef struct {
    Rating** ratings;
    unsigned int userCount;
    unsigned int itemCount;
} RatingData;

typedef struct {
    unsigned int user;
    unsigned int item;
    Rating rating;
} UIRating;

typedef struct {
    UIRating* elements;
    unsigned int count;
} UIRatings;

void RatingData_init(RatingData* data, unsigned int userCount, unsigned int itemCount);
void RatingData_initDummy(RatingData* data, unsigned int userCount, unsigned int itemCount);
RatingData* RatingData_make(unsigned int userCount, unsigned int itemCount);
RatingData* RatingData_readFromCSV(unsigned int userCount, unsigned int itemCount, char* path);
double RatingData_ratingByUserForItem(const RatingData* data, unsigned int user, unsigned int item);
bool RatingData_userRatedItem(const RatingData* data, unsigned int user, unsigned int item);
unsigned int RatingData_numberOfUsers(const RatingData* data);
unsigned int RatingData_numberOfItems(const RatingData* data);
unsigned int RatingData_numberOfRatingsByUser(const RatingData* data, unsigned int user);
unsigned int* RatingData_itemsRatedByUser(const RatingData* data, unsigned int user);
unsigned int RatingData_numberOfRatingsForItem(const RatingData* data, unsigned int item);
unsigned int* RatingData_usersWhoRatedItem(const RatingData* data, unsigned int item);
UIRatings* RatingData_collectKnownRatingsAsUIRatings(const RatingData* data);
DoubleMatrix* RatingData_getRatingsAsDoubleMatrix(const RatingData* data);

UIRatings* UIRatings_make(unsigned int n);

#endif /* Data_h */
