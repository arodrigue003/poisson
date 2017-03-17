//
// Created by cyrbos on 3/3/17.
//

#ifndef FREE_POISSON_AQUARIUM_H
#define FREE_POISSON_AQUARIUM_H

#include "fish.h"

#define MAX_FISH 1024
#define MAX_VIEW 10

struct view {
    int view_x;
    int view_y;
    int view_width;
    int view_height;
};

struct aquarium {
    int aquarium_width;
    int aquarium_height;
    int aquarium_views;

    struct fish fishes[MAX_FISH];
    int fish_number;

    struct view views[MAX_VIEW];
};


/****** These functions return success or error ******/

void init_aquarium(struct aquarium* aquarium);

int add_fish(const struct fish* fish, struct aquarium *aquarium);

int del_fish(char *fish_name, struct aquarium *aquarium);

int start_fish(char *fish_name);

struct fish *get_fishes(struct aquarium *aquarium);

char *get_fish_data_str(const struct fish *fish);

char *get_fishes_data_str(const struct aquarium *aquarium);

int load_aquarium(struct aquarium *aquarium);

int del_view(int view, struct aquarium *aquarium);

int add_view(struct view *view, struct aquarium *aquarium);

int show_aquarium(struct aquarium *aquarium);

int save_aquarium(struct aquarium *aquarium);

/******************************************************/

#endif //FREE_POISSON_AQUARIUM_H
