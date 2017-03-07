#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


#include "controller.h"
#include "utils.h"

static void app(void)
{
    struct controller controller;
    printf("Initiating connection socket\n");
    controller.listen_sock = init_connection();
    /* the index for the array */
    controller.client_number = 0;
    controller.max_sock = controller.listen_sock;
    /* an array for all clients */
    while(1)
    {
        int i = 0;
        FD_ZERO(&controller.read_fd_set);

        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &controller.read_fd_set);

        /* add the connection socket */
        FD_SET(controller.listen_sock, &controller.read_fd_set);

        /* add socket of each client */
        for(i = 0; i < controller.client_number; i++)
        {
            FD_SET(controller.clients[i].sock, &controller.read_fd_set);
        }

        printf("Watching stdin and sockets\n");
        CHKERR(select(controller.max_sock + 1, &controller.read_fd_set, NULL, NULL, NULL));

        /* something from standard input : i.e keyboard */
        if(FD_ISSET(STDIN_FILENO, &controller.read_fd_set))
        {
            /* stop process when type on keyboard */
            break;
        }
        else if(FD_ISSET(controller.listen_sock, &controller.read_fd_set))
        {
            /* new client */
            struct sockaddr_in csin = { 0 };
            socklen_t sinsize = sizeof csin;
            int csock = accept(controller.listen_sock, (struct sockaddr *)&csin, &sinsize);
            printf("Accepted new client %d\n", controller.client_number);
            if(csock == -1)
            {
                perror("accept()");
                continue;
            }
            
            /* what is the new maximum fd ? */
            controller.max_sock = csock > controller.max_sock ? csock : controller.max_sock;

            FD_SET(csock, &controller.read_fd_set);

            struct client c = { csock };
            controller.clients[controller.client_number] = c;
            controller.client_number++;
        }
        else
        {
            int i = 0;
            for(i = 0; i < controller.client_number; i++)
            {
                /* a client is talking */
                if(FD_ISSET(controller.clients[i].sock, &controller.read_fd_set))
                {
                    struct client client = controller.clients[i];
                    int c = read_client(controller.clients[i].sock, controller.buff);
                    /* client disconnected */
                    if(c == 0)
                    {
                        printf("Client %d disconnected\n", i);
                        close(controller.clients[i].sock);
                        remove_client(controller.clients, i, &controller.client_number);
                        //strncpy(controller.buff, itoa(i), BUFF_SIZE - 1);
                        //strncat(controller.buff, " disconnected !", BUFF_SIZE - strlen(controller.buff) - 1);
                        send_message_to_all_clients(controller.clients, client, controller.client_number, controller.buff, 1);
                    }
                    else
                    {
                        printf("received message from client %d : %s\n", i, controller.buff);
                        send_message_to_all_clients(controller.clients, client, controller.client_number, controller.buff, 0);
                    }
                    break;
                }
            }
        }
    }

    clear_clients(controller.clients, controller.client_number);
    end_connection(controller.listen_sock);
}

static void clear_clients(struct client *clients, int client_number)
{
    int i = 0;
    for(i = 0; i < client_number; i++)
    {
        close(clients[i].sock);
    }
}

static void remove_client(struct client *clients, int to_remove, int *client_number)
{
    /* we remove the client in the array */
    memmove(clients + to_remove, clients + to_remove + 1, (*client_number - to_remove - 1) * sizeof(struct client));
    /* number client - 1 */
    (*client_number)--;
}

static void send_message_to_all_clients(struct client *clients, struct client sender, int client_number, const char *buffer, char from_server)
{
    int i = 0;
    char message[BUFF_SIZE];
    message[0] = 0;
    for(i = 0; i < client_number; i++)
    {
        /* we don't send message to the sender */
        if(sender.sock != clients[i].sock)
        {
            if(from_server == 0)
            {
                //strncpy(message, sender.name, BUF_SIZE - 1);
                //strncat(message, " : ", sizeof message - strlen(message) - 1);
            }
            strncat(message, buffer, sizeof message - strlen(message) - 1);
            write_client(clients[i].sock, message);
        }
    }
}

static int init_connection(void)
{
    int sock;
    CHKERR(sock = socket(AF_INET, SOCK_STREAM, 0));
    struct sockaddr_in sin = { 0 };

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(CONTROLLER_PORT);
    sin.sin_family = AF_INET;

    CHKERR(bind(sock,(struct sockaddr *) &sin, sizeof sin));


    CHKERR(listen(sock, MAX_CLIENT));

    return sock;
}

static void end_connection(int sock)
{
    close(sock);
}

static int read_client(int sock, char *buffer)
{
    int n = 0;

    if((n = recv(sock, buffer, BUFF_SIZE - 1, 0)) < 0)
    {
        perror("recv()");
        /* if recv error we disonnect the client */
        n = 0;
    }

    buffer[n] = 0;

    return n;
}

static void write_client(int sock, const char *buffer)
{
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}

int main(int argc, char* argv[]) {
    app();
    return EXIT_SUCCESS;
}