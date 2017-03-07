//
// Created by cyrbos on 3/3/17.
//

#ifndef FREE_POISSON_UTILS_H
#define FREE_POISSON_UTILS_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CHKERR(X) \
    if ((X) < 0) \
    { \
        perror(#X); \
        exit(errno); \
    }

#endif //FREE_POISSON_UTILS_H
