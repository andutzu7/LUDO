//Example code: A simple server side code, which echos back the received message.
//Handle multiple socket connections with select and fd_set on Linux
#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros

#define PORT 2024

int main(int argc , char *argv[])
{
	int ok = 1;
	int listenSocket , len , newSocket , client_socket[SOMAXCONN] ,
        activity, valread , fd,connections=0;
	int max_fd;
	struct sockaddr_in server;

	char buf[1024];

	fd_set readfds;

	char *message = "Lets play some ludo \n";

	for (int i = 0; i < SOMAXCONN; i++)
	{
		client_socket[i] = 0;
	}

	if( (listenSocket = socket(AF_INET , SOCK_STREAM , 0)) <= 0)
	{
		perror("Eroare socket");
        return -1;
	}

	//setam flagul ca sa fie acceptate mai multi clienti
	if( setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&ok,sizeof(ok)) ==-1 )
	{
		perror("Eroare la setsockopt");
		return -2;
	}

    server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );

	if (bind(listenSocket, (struct sockaddr *)&server, sizeof(server))<0)
	{
		perror("Eroare la bind: ");
		return -3;
	}
	printf("Nr port: %d \n", PORT);

	//maxim 4 jucatori pot juca ludo
	if (listen(listenSocket, 4) < 0)
	{
		perror("Eroare la listen:");
		return -4;
	}


	len = sizeof(server);
	printf("Waiting for connections\n");

	while(1)
	{
        //golim fd-ul actual
		FD_ZERO(&readfds);

		FD_SET(listenSocket, &readfds);
		max_fd = listenSocket;

		for ( int i = 0 ; i < SOMAXCONN ; i++)
		{
			fd = client_socket[i];
            //adaugam fd catre toti clientii valizi
			if(fd > 0)
				FD_SET( fd , &readfds);

			if(fd> max_fd)
				max_fd = fd;
		}

		//asteptam pana cand un semnal este dat de catre client
		activity = select( max_fd + 1 , &readfds , NULL , NULL , NULL);

		if ((activity < 0))
		{
			printf("Eroare la select");
		}

		if (FD_ISSET(listenSocket, &readfds))
		{
			if ((newSocket = accept(listenSocket,(struct sockaddr *)&server, (socklen_t*)&len))<0)
			{
				perror("Eroare la accept");
				return -5;
			}

			printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , newSocket , inet_ntoa(server.sin_addr) , ntohs(server.sin_port));

			if( send(newSocket, message, strlen(message), 0) != strlen(message) )
			{
				perror("Eroare la send: ");
                return -6;
			}

			printf("Welcome message sent");

			for (int i = 0; i < SOMAXCONN; i++)
			{
				if( client_socket[i] == 0 )
				{
					client_socket[i] = newSocket;
					printf("Adding the new client to the list as clieent nr%d\n" , i);
                    connections++;
					break;
				}
			}
		}

		for (int i = 0; i < SOMAXCONN; i++)
		{
			fd = client_socket[i];

			if (FD_ISSET( fd , &readfds))
			{
                //daca un client s a deconectat
				if ((valread = read( fd , buf, 1024)) == 0)
				{
					getpeername(fd , (struct sockaddr*)&server ,(socklen_t*)&len);
                        printf("Client disconnected , ip %s , port %d \n" ,
						inet_ntoa(server.sin_addr) , ntohs(server.sin_port));
                 connections--;
                    //inchidem socketul
					close( fd );
					//marcam in vector cu 0 ca sa refolosim pozitia
					client_socket[i] = 0;
				}

				else
				{
                    //creem array ul cu rasp clientului
					buf[valread] = '\0';
					send(fd , buf , strlen(buf) , 0 );
				}
			}
		}
	for (int i = 0; i < SOMAXCONN; i++)
		{
		char str[100];
        sprintf(str,"%d",connections);
        send(newSocket,str,4,0);
		}
	}

	return 0;
}
