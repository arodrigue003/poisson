//
// Created by cyrbos on 3/3/17.
//

#ifndef FREE_POISSON_CONTROLLER_H
#define FREE_POISSON_CONTROLLER_H

#include "netinet/in.h"

#include "aquarium.h"
#include "client.h"

/***** These values have to be loaded from cfg files *****/
#define CONTROLLER_PORT 12345

#define DISPLAY_TIMEOUT_VALUE 45

#define FISH_UPDATE_INTERVAL 1
/*********************************************************/

#define MAX_CLIENT 1024

#define BUFF_SIZE 1024

struct controller {
    int listen_sock;
    struct client clients[MAX_CLIENT];
    int client_number;
    int max_sock;
    fd_set read_fd_set; //used by select

    char buff[BUFF_SIZE];

    struct aquarium aquarium;
};

static void app(void);
static int init_connection(void);
static void end_connection(int sock);
static int read_client(int sock, char *buffer);
static void write_client(int sock, const char *buffer);
static void send_message_to_all_clients(struct client *clients, int client_number, const char *buffer);
static void remove_client(struct client *clients, int to_remove, int *actual);
static void clear_clients(struct client *clients, int actual);


#endif //FREE_POISSON_CONTROLLER_H
