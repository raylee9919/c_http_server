#ifndef ROUTE_H
#define ROUTE_H

#include <stdlib.h>
#include <string.h>

struct route
{
    char*               key_;
    char*               value_;
    struct route*       left_;
    struct route*       right_;
};

struct route* insert(struct route* root, char* key, char* value);

struct route* find(struct route* node, char* key);

#endif
