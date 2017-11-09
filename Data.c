//
//  Data.c
//  Recommender System
//
//  Created by Jan Kaiser on 02.11.17.
//  Copyright © 2017 Jan Kaiser. All rights reserved.
//

#include "Data.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define LUKE                0
#define STEVE               1
#define ALEXA               2
#define BILL                3
#define CORTANA             4
#define SIRI                5
#define EDSGER              6
#define STAR_WARS           0
#define JAMES_BOND          1
#define TWILIGHT            2
#define MINIONS             3
#define OCEANS_ELEVEN       4
#define FLUCH_DER_KARIBIK   5
#define ICE_AGE             6

void RatingData_init(RatingData* data, unsigned int userCount, unsigned int itemCount) {
    data->userCount = userCount;
    data->itemCount = itemCount;
    
    data->ratings = malloc(data->userCount * sizeof(Rating*));
    for (int u = 0; u < data->userCount; u += 1) {
        data->ratings[u] = malloc(data->itemCount * sizeof(Rating));
        for (int i = 0; i < data->itemCount; i += 1) {
            data->ratings[u][i].value = 0.0;
            data->ratings[u][i].known = false;
        }
    }
}

void RatingData_initDummy(RatingData* data, unsigned int userCount, unsigned int itemCount) {
    data->userCount = userCount;
    data->itemCount = itemCount;
    
    data->ratings = malloc(data->userCount * sizeof(Rating*));
    for (int u = 0; u < data->userCount; u += 1) {
        data->ratings[u] = malloc(data->itemCount * sizeof(Rating));
        for (int i = 0; i < data->itemCount; i += 1) {
            data->ratings[u][i].value = 0.0;
            data->ratings[u][i].known = false;
        }
    }
    
    data->ratings[LUKE][STAR_WARS] = (Rating){true, GOOD};
    data->ratings[LUKE][JAMES_BOND] = (Rating){true, OKAY};
    data->ratings[LUKE][TWILIGHT] = (Rating){true, BAD};
    data->ratings[LUKE][MINIONS] = (Rating){false, NAN};
    data->ratings[LUKE][OCEANS_ELEVEN] = (Rating){false, NAN};
    data->ratings[LUKE][FLUCH_DER_KARIBIK] = (Rating){false, NAN};
    data->ratings[LUKE][ICE_AGE] = (Rating){false, NAN};
     
    data->ratings[STEVE][STAR_WARS] = (Rating){false, NAN};
    data->ratings[STEVE][JAMES_BOND] = (Rating){true, GOOD};
    data->ratings[STEVE][TWILIGHT] = (Rating){false, NAN};
    data->ratings[STEVE][MINIONS] = (Rating){false, NAN};
    data->ratings[STEVE][OCEANS_ELEVEN] = (Rating){true, GOOD};
    data->ratings[STEVE][FLUCH_DER_KARIBIK] = (Rating){true, GOOD};
    data->ratings[STEVE][ICE_AGE] = (Rating){false, NAN};
     
    data->ratings[ALEXA][STAR_WARS] = (Rating){true, OKAY};
    data->ratings[ALEXA][JAMES_BOND] = (Rating){false, NAN};
    data->ratings[ALEXA][TWILIGHT] = (Rating){true, GOOD};
    data->ratings[ALEXA][MINIONS] = (Rating){true, GOOD};
    data->ratings[ALEXA][OCEANS_ELEVEN] = (Rating){false, NAN};
    data->ratings[ALEXA][FLUCH_DER_KARIBIK] = (Rating){false, NAN};
    data->ratings[ALEXA][ICE_AGE] = (Rating){false, NAN};
     
    data->ratings[BILL][STAR_WARS] = (Rating){false, NAN};
    data->ratings[BILL][JAMES_BOND] = (Rating){false, NAN};
    data->ratings[BILL][TWILIGHT] = (Rating){true, BAD};
    data->ratings[BILL][MINIONS] = (Rating){true, GOOD};
    data->ratings[BILL][OCEANS_ELEVEN] = (Rating){false, NAN};
    data->ratings[BILL][FLUCH_DER_KARIBIK] = (Rating){false, NAN};
    data->ratings[BILL][ICE_AGE] = (Rating){true, GOOD};
     
    data->ratings[CORTANA][STAR_WARS] = (Rating){false, NAN};
    data->ratings[CORTANA][JAMES_BOND] = (Rating){true, GOOD};
    data->ratings[CORTANA][TWILIGHT] = (Rating){false, NAN};
    data->ratings[CORTANA][MINIONS] = (Rating){false, NAN};
    data->ratings[CORTANA][OCEANS_ELEVEN] = (Rating){true, OKAY};
    data->ratings[CORTANA][FLUCH_DER_KARIBIK] = (Rating){false, NAN};
    data->ratings[CORTANA][ICE_AGE] = (Rating){true, BAD};
     
    data->ratings[SIRI][STAR_WARS] = (Rating){true, GOOD};
    data->ratings[SIRI][JAMES_BOND] = (Rating){false, NAN};
    data->ratings[SIRI][TWILIGHT] = (Rating){false, NAN};
    data->ratings[SIRI][MINIONS] = (Rating){true, BAD};
    data->ratings[SIRI][OCEANS_ELEVEN] = (Rating){false, NAN};
    data->ratings[SIRI][FLUCH_DER_KARIBIK] = (Rating){true, BAD};
    data->ratings[SIRI][ICE_AGE] = (Rating){false, NAN};
     
    data->ratings[EDSGER][STAR_WARS] = (Rating){false, NAN};
    data->ratings[EDSGER][JAMES_BOND] = (Rating){true, GOOD};
    data->ratings[EDSGER][TWILIGHT] = (Rating){false, NAN};
    data->ratings[EDSGER][MINIONS] = (Rating){true, OKAY};
    data->ratings[EDSGER][OCEANS_ELEVEN] = (Rating){false, NAN};
    data->ratings[EDSGER][FLUCH_DER_KARIBIK] = (Rating){true, BAD};
    data->ratings[EDSGER][ICE_AGE] = (Rating){false, NAN};
}

RatingData* RatingData_make(unsigned int userCount, unsigned int itemCount) {
    RatingData* data = malloc(sizeof(RatingData));
    RatingData_init(data, userCount, itemCount);
    return data;
}

RatingData* RatingData_readFromCSV(unsigned int userCount, unsigned int itemCount, char* path) {
    FILE* stream = fopen(path, "r");
    RatingData* data = RatingData_make(userCount, itemCount);
    
    int r = 0;
    rewind(stream);
    for (int u = 0; u < userCount; u += 1) {
        for (int i = 0; i < itemCount - 1; i += 1) {
            r = 99;
            fscanf(stream, "%u;", &r);
            data->ratings[u][i].value = (double)r;
            data->ratings[u][i].known = true;
            //DoubleMatrix_printNamed(RatingData_getRatingsAsDoubleMatrix(data), "inner Loop");
        }
        r = 99;
        fscanf(stream, "%u", &r);
        data->ratings[u][itemCount - 1].value = (double)r;
        data->ratings[u][itemCount - 1].known = true;
        //DoubleMatrix_printNamed(RatingData_getRatingsAsDoubleMatrix(data), "outer Loop");
    }
    
    fclose(stream);
    return data;
}

double RatingData_ratingByUserForItem(const RatingData* data, unsigned int user, unsigned int item) {
    return data->ratings[user][item].value;
}

bool RatingData_userRatedItem(const RatingData* data, unsigned int user, unsigned int item) {
    return data->ratings[user][item].known;
}

unsigned int RatingData_numberOfUsers(const RatingData* data) {
    return data->userCount;
}

unsigned int RatingData_numberOfItems(const RatingData* data) {
    return data->itemCount;
}

unsigned int RatingData_numberOfRatingsByUser(const RatingData* data, unsigned int user) {
    unsigned int n = 0;
    const Rating* userRatings = data->ratings[user];
    for (int i = 0; i < data->itemCount; i += 1) {
        if (userRatings[i].known) { n += 1; }
    }
    return n;
}

unsigned int* RatingData_itemsRatedByUser(const RatingData* data, unsigned int user) {
    unsigned int n = RatingData_numberOfRatingsByUser(data, user);
    unsigned int* items = malloc(n * sizeof(unsigned int));
    
    unsigned int i = 0;
    UIRatings* knownRatings = RatingData_collectKnownRatingsAsUIRatings(data);
    for (int r = 0; r < knownRatings->count; r += 1) {
        if (knownRatings->elements[r].user == user) {
            items[i] = knownRatings->elements[r].item;
            i += 1;
        }
    }
    return items;
}

unsigned int RatingData_numberOfRatingsForItem(const RatingData* data, unsigned int item) {
    unsigned int n = 0;
    for (int u = 0; u < data->userCount; u += 1) {
        if (data->ratings[u][item].known) { n += 1; }
    }
    return n;
}

unsigned int* RatingData_usersWhoRatedItem(const RatingData* data, unsigned int item) {
    unsigned int n = RatingData_numberOfRatingsForItem(data, item);
    unsigned int* users = malloc(n * sizeof(unsigned int));
    
    unsigned i = 0;
    UIRatings* knownRatings = RatingData_collectKnownRatingsAsUIRatings(data);
    for (int r = 0; r < knownRatings->count; r += 1) {
        if (knownRatings->elements[r].item == item) {
            users[i] = knownRatings->elements[r].user;
            i += 1;
        }
    }
    return users;
}

UIRatings* RatingData_collectKnownRatingsAsUIRatings(const RatingData* data) {
    unsigned int n = 0;
    for (int u = 0; u < data->userCount; u += 1) {
        for (int i = 0; i <data->itemCount; i += 1) {
            if (data->ratings[u][i].known) { n += 1; }
        }
    }
    
    UIRatings* rs = UIRatings_make(n);
    n = 0;
    for (int u = 0; u < data->userCount; u += 1) {
        for (int i = 0; i <data->itemCount; i += 1) {
            if (data->ratings[u][i].known) {
                UIRating r;
                r.user = u;
                r.item = i;
                r.rating = data->ratings[u][i];
                
                rs->elements[n] = r;
                n += 1;
            }
        }
    }
    return rs;
}

DoubleMatrix* RatingData_getRatingsAsDoubleMatrix(const RatingData* data) {
    DoubleMatrix* m = malloc(sizeof(DoubleMatrix));
    DoubleMatrix_init(m, data->itemCount, data->userCount);
    for (int u = 0; u < data->userCount; u += 1) {
        for (int i = 0; i < data->itemCount; i += 1) {
            m->elements[u][i] = data->ratings[u][i].value;
        }
    }
    return m;
}

UIRatings* UIRatings_make(unsigned int n) {
    UIRatings* r = malloc(sizeof(UIRatings));
    r->count = n;
    r->elements = malloc(n * sizeof(UIRating));
    return r;
}
