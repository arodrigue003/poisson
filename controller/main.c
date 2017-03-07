//
// Created by cyrbos on 3/3/17.
//
#include "utils.h"
#include <unistd.h>
#include "controller.h"

int main(int argc, char* argv[]) {
    struct controller controller;

    int pipe_fd[2];

    CHKERR(pipe(pipe_fd));

    init_controller(&controller);

    //if (fork() == 0) {
    //    close(pipe_fd[1]);
        while (1) {
            handle_new_client(&controller);
        }
    /*}
    else {
        close(pipe_fd[0]);
        while (1) {
            handle_input(&controller);
        }
    }*/

    close_connections(&controller);
    return EXIT_SUCCESS;
}