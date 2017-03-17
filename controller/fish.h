//
// Created by cyrbos on 3/3/17.
//

#ifndef FREE_POISSON_FISH_H
#define FREE_POISSON_FISH_H

enum MOBILITY_MODEL {
    RANDOM_WAY_POINT
};

struct fish {
    char* name;
    int curr_x, curr_y;
    int target_x, target_y;
    int width, height;

    int move_duration;

    enum MOBILITY_MODEL mobility_model;
};

struct fish* new_fish();

#endif //FREE_POISSON_FISH_H
