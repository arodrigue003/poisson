//
// Created by cyrbos on 3/3/17.
//

#ifndef FREE_POISSON_AQUARIUM_H
#define FREE_POISSON_AQUARIUM_H
#include "fish.h"

#define MAX_FISH 1024

struct aquarium {
    struct fish fishes[MAX_FISH];
};

/****** These functions return success or error ******/

int add_fish(struct fish fish, struct aquarium* aquarium);

int del_fish(char* fish_name, struct aquarium* aquarium);

int start_fish(char* fish_name);

struct fish* get_fishes(struct aquarium* aquarium);

/******************************************************/
#endif //FREE_POISSON_AQUARIUM_H
