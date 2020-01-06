#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include <fstream>
#define PORT 2025
#define MAXCLIENTS 4

pthread_mutex_t lock;
int connectionsNumber;
pthread_t th[100];

typedef struct thData
{
    int idThread;
    int cl;
} thData;
//SERVERUL TREBUIE SA TRIMITA NR JUCATORI, JUCATORUL CURENT SI UN FISIER TEXT PT SCORURI

void* HandleConnection(void* thr) //aicisa tre sa inserez date B)
{
    int num;

    char buffer[1025];
    thData* t=(thData*)(thr);
    int clientSocket=t->cl;

    if ((num = recv(clientSocket,buffer,1024,0))== -1)
    {
        perror("recv");
        exit(1);
    }
    else if (num == 0)
    {
        printf("Connection closed\n");
        //So I can now wait for another client
        return NULL;
    }
    buffer[num] = '\0';
    sprintf(buffer,"%d",q);//aici o sa trim param jocului
    //trebuie de fiecare data cand se conecteaza sa trimita nr de conexiuni,jucatorul curent si sa primeasca daca gameover e true si daca da,scorul
    if ((send(clientSocket,buffer, strlen(buffer),0))== -1)
    {
        fprintf(stderr, "Failure Sending Message\n");
        close(clientSocket);
        return NULL;
    }

    printf("Server:Msg being sent: %s\nNumber of bytes sent: %d\n",buffer, strlen(buffer));
    close(clientSocket);
    return NULL;
}



int main()
{
    int serverSocket,clientSocket,addressSize;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int ok;
    serverSocket=socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket==-1)
    {
        perror("Socket error. ");
        return -1;
    }

    //initializam adresa serverului
    if( setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&ok,sizeof(ok)) ==-1 )
    {
        perror("Eroare la setsockopt");
        return -5;
    }


    serverAddr.sin_family=AF_INET;
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr.sin_port=htons(PORT);


    if(bind(serverSocket,(struct sockaddr*)&serverAddr,sizeof(struct sockaddr))<0)
    {

        perror("Binding error. ");
        return -2;
    }
    if(listen(serverSocket,MAXCLIENTS)<0)
    {

        perror("Listen error.");
        return -3;

    }
    printf("Wainting for clients to join \n");
    int num;
    int i=0;
    char buffer[1024];

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

    int test=0;
    while(1)
    {

        addressSize=sizeof(struct sockaddr_in);
        clientSocket=accept(serverSocket,(struct sockaddr*)&clientAddr,(socklen_t*)&addressSize);
        if(clientSocket<0)
        {
            perror("Accept error");
            return -4;
        }
        printf("New connection , socket fd is %d , ip is : %s , port : %d \n", clientSocket, inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
        test++;

        thData * td;
        td=(struct thData*)malloc(sizeof(struct thData));
        td->idThread=i++;
        td->cl=clientSocket;

        pthread_create(&th[i],NULL,HandleConnection,td);

    }

    close(serverSocket);
    return 0;
}

