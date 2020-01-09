#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

#define MAXCLIENTS 4
#define PORT 2024

int connections = 0;
int idThread = 0;

typedef struct thData
{
    struct sockaddr_in address;
    int fd;
    int threadId;
} clientThread;

clientThread *clients[MAXCLIENTS];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;


//Inseram in vectorul de evidenta a threadurilor un nou jucator
void InsertClient(clientThread *cl)
{
    pthread_mutex_lock(&clients_mutex);


    for(int i=0; i < MAXCLIENTS; ++i)
    {
        if(!clients[i])
        {
            clients[i] = cl;
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

//Eliminam clienti din vectorul de evidenta
void RemoveClient(int id)
{
    pthread_mutex_lock(&clients_mutex);

    for(int i=0; i < MAXCLIENTS; ++i)
    {
        if(clients[i])
        {
            if(clients[i]->threadId == id)
            {
                clients[i] = NULL;
                connections=i;//a bug s solutin

                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

/* Transmitem informatii clientilor*/
void SendData(char *s, int id)
{
    pthread_mutex_lock(&clients_mutex);

    for(int i=0; i<MAXCLIENTS; ++i)
    {
        if(clients[i])
        {
            if(clients[i]->threadId == id)
            {
                if(write(clients[i]->fd, s, strlen(s)) < 0)
                {
                    perror("Eroare la transmiterea datelor.");
                    break;
                }
                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}


void *HandleConnections(void *th)
{

    char buff[1024];
    int stop = 0;
    printf("%d \n",connections);
    connections++;
    sprintf(buff,"%d",connections);

    for(int i=0;i<connections;i++)
    {
    SendData(buff,i);
    }

    clientThread *cl = (clientThread *)th;

    bzero(buff,1024);
    while(1)
    {
    printf("Ma preg sa citesc \n");
        if (stop)
        {
            break;
        }

        int received = recv(cl->fd, buff, 1024, 0);

        if (received > 0)
        {
            if(strlen(buff) > 0)
            {

                SendData(buff,cl->threadId); //testing purposes,trebuie modificat
                printf("%s\n", buff);
            }
        }
        else if (received == 0)
        {
            printf("%s", buff);
            SendData(buff, cl->threadId);
            stop = 1;
        }
        else
        {
            perror("Eroare la rcv.");
            stop = 1;
        }

        bzero(buff, 1024);
    }

    close(cl->fd);
    RemoveClient(cl->threadId);
    free(cl);
    connections--;
    pthread_detach(pthread_self());

    return NULL;
}

int main()
{

    char* IP = "127.0.0.1";
    int ok = 1;
    int serverfd ,clientfd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    pthread_t th;

    /* initializam socketul*/
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP);
    serv_addr.sin_port = htons(PORT);


    if(setsockopt(serverfd, SOL_SOCKET,(SO_REUSEPORT | SO_REUSEADDR),(char*)&ok,sizeof(ok)) < 0)
    {
        perror("Eroare la setarea flagurilor.");
        return -1;
    }

    if(bind(serverfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Eroare la bind");
        return -1;
    }

    if (listen(serverfd, MAXCLIENTS) < 0)
    {
        perror("Eroare la listen");
        return -1;
    }

    printf("Waiting for clients.\n");

    while(1)
    {
        socklen_t adresslen = sizeof(client_addr);
        clientfd = accept(serverfd, (struct sockaddr*)&client_addr, &adresslen);

        /* Vrificam daca nr maxim de clienti este atins */
        if((connections) == MAXCLIENTS)
        {
            char errorMSG[100]="Numarul maxim de clienti a fost deja atins.\n";
            write(clientfd, errorMSG, strlen(errorMSG));
            close(clientfd);
            connections--;
        }

        //initializam noul client
        clientThread *cl = (clientThread *)malloc(sizeof(clientThread));
        cl->address = client_addr;
        cl->fd = clientfd;
        cl->threadId = idThread++;
        //Adaugam noul client
        InsertClient(cl);
        pthread_create(&th, NULL, &HandleConnections, (void*)cl);

        sleep(1);
    }

    return 0;
}
