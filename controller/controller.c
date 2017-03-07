//
// Created by cyrbos on 3/3/17.
//
#include "controller.h"
#include "utils.h"
#include <unistd.h>
#include <string.h>

void init_controller(struct controller* controller) {
    //for select
    FD_ZERO(&controller->read_fd_set);

    CHKERR(controller->listen_sock = socket(AF_INET, SOCK_STREAM, 0));
    FD_SET(controller->listen_sock, &controller->read_fd_set);

    struct sockaddr_in sin = { 0 };

    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    sin.sin_family = AF_INET;

    sin.sin_port = htons(CONTROLLER_PORT);

    CHKERR(bind(controller->listen_sock, (struct sockaddr*) &sin, sizeof(sin)));
    CHKERR(listen(controller->listen_sock, MAX_CLIENT));

    controller->max_sock = controller->listen_sock;
}

void handle_input(struct controller* controller) {
    //To-Do
}

void handle_new_client(struct controller* controller) {
    printf("watching client sockets...\n");
    CHKERR(select(controller->max_sock + 1, &controller->read_fd_set, NULL, NULL, NULL));
    if (FD_ISSET(controller->listen_sock, &controller->read_fd_set)) {
        struct client * new_client = &controller->clients[controller->client_number];

        memset(&new_client->sin, 0, sizeof(new_client->sin));
        new_client->sin_len =sizeof(new_client->sin);

        new_client->sock = accept(controller->listen_sock, (struct sockaddr*) &new_client->sin, &new_client->sin_len);
        printf("accepted new client number %d\n", controller->client_number);
        controller->client_number++;
        if (new_client->sock > controller->max_sock) {
            controller->max_sock = new_client->sock;
        }

        FD_SET(new_client->sock, &controller->read_fd_set);

    }
    for (int i = 0; i < controller->client_number; ++i) {
        if (FD_ISSET(controller->clients[i].sock, &controller->read_fd_set)) {
            CHKERR(recv(controller->clients[i].sock, controller->buff, BUFF_SIZE-1, 0));
            printf("Received message \"%s\" from client number %d", controller->buff, i);
            CHKERR(send(controller->clients[i].sock, controller->buff, BUFF_SIZE-1, 0));
            printf("Sending message \"%s\" to client number %d", controller->buff, i);
        }
    }
}

void close_connections(struct controller* controller) {
    for (int i = 0; i < controller->client_number; ++i) {
        close(controller->clients[i].sock);
    }

    close(controller->listen_sock);
}