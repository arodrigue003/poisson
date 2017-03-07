//
// Created by cyrbos on 3/3/17.
//

#ifndef FREE_POISSON_CONTROLLER_H
#define FREE_POISSON_CONTROLLER_H

#include "aquarium.h"
#include "netinet/in.h"

/***** These values have to be loaded from cfg files *****/
#define CONTROLLER_PORT 12345

#define DISPLAY_TIMEOUT_VALUE 45

#define FISH_UPDATE_INTERVAL 1
/*********************************************************/

#define MAX_CLIENT 1024

#define BUFF_SIZE 1024

struct client {
    int sock;
    struct sockaddr_in sin;
    socklen_t sin_len;
};

struct controller {
    int listen_sock;
    struct client clients[MAX_CLIENT];
    int client_number;
    int max_sock;
    fd_set read_fd_set; //used by select

    char buff[BUFF_SIZE];

    struct aquarium aquarium;
};

void init_controller(struct controller* controller);

void handle_input(struct controller* controller);

void handle_new_client(struct controller* controller);

void close_connections(struct controller* controller);


#endif //FREE_POISSON_CONTROLLER_H
