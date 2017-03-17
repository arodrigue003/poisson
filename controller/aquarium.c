#include <string.h>
#include "aquarium.h"
#include "utils.h"

/****** Implémentation des fonctions de l'aquarium ******/


void init_aquarium(struct aquarium* aquarium) {
    aquarium->fish_number = 0;

    struct fish test_fish;

    test_fish.name = "test";
    test_fish.curr_x = 0;
    test_fish.curr_y = 0;
    test_fish.target_x = 10;
    test_fish.target_y = 10;
    test_fish.move_duration = 10;

    add_fish(&test_fish, aquarium);
}

char* get_fish_data_str(const struct fish *fish) {
    char* data_string = malloc(1024); //To-Do
    sprintf(data_string, "%s at %dx%d, %dx%d, %d", fish->name, fish->curr_x, fish->curr_y, fish->target_x, fish->target_y, fish->move_duration);
    return data_string;
}

char* get_fishes_data_str(const struct aquarium* aquarium) {
    char* fishes_data_str = malloc(sizeof(char) * 4 * 2 * aquarium->fish_number);
    char* fish_data_str;
    char* tmp;
    for (int i = 0; i < aquarium->fish_number; ++i) {
        fish_data_str = get_fish_data_str(&aquarium->fishes[i]);
        tmp = fishes_data_str;
        fishes_data_str = malloc(strlen(tmp) + strlen(fish_data_str));
        strcat(fishes_data_str, tmp);
        strcat(fishes_data_str, fish_data_str);
    }
    //Debug
    printf("%s\n", fishes_data_str);
    return fishes_data_str;
}

int add_fish(const struct fish* fish, struct aquarium* aquarium) {
    if (aquarium->fish_number >= MAX_FISH)
        return 0;
    aquarium->fishes[aquarium->fish_number] = *fish;
    aquarium->fish_number++;
    return 1;
}

int del_fish(char* fish_name, struct aquarium* aquarium) {
    for (int i = 0; i < aquarium->fish_number; ++i) {
        if (strcmp(aquarium->fishes[i].name, fish_name) == 0) {
            for (int j = i; j < aquarium->fish_number-1; j++) {
                aquarium->fishes[j] = aquarium->fishes[j+1];
            }
            return 1;
        }
    }
    return 0;//fish not found
}

/*  int load_aquarium(struct aquarium* aquarium); */
/* int save_aquarium(struct aquarium* aquarium); */


 /* int del_view(int view, struct aquarium* aquarium){ */
 /*   free((*aquarium).views[view]); */
 /*   (*aquarium).views[view] = NULL; */
 /* } */

 /* int add_view(int view_rank, struct view *view, struct aquarium* aquarium){ */
 /*   if (!(*aquarium).views[view_rank]){ */
 /*     fprintf (stderr, "%s:  Cannot add. This view is already used.\n", "add"); */
 /*     return 0; */
 /*   } */
 /*   (*aquarium).views[view_rank] = view; */
 /*   (*aquarium).aquarium_views++; */
 /*   return 1; */
 /* } */

 /* int show_aquarium(struct aquarium* aquarium){ */
 /*   printf("%dx%d\n", (*aquarium).aquarium_width,  (*aquarium).aquarium_height); */
 /*   for (int i = 0; i < MAX_VIEWS; i++){ */
 /*     if ( !(*aquarium).views[i]) */
 /*       printf("N%d %dx%d+%d+%d\n", i,  views[i].view_x, views[i].view_y, views[i].view_width,views[i].view_height);  */
 /*   } */
 /* } */
