#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // структура для сокета
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2019);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    int sock = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет
    connect(sock, &server, sizeof(server)); // соединяемся с сервером
    // отправка сообщения
    char command[5][32];
    for (size_t i = 0; i < argc; i++)
    {
        strcpy(command[i+1], "\0");
        strcpy(command[i], argv[i]);
    }
    
    //printf("%s\n", argv[1]);
    send(sock, command, sizeof(command), 0);
    char buf[1024];
    int x = 0;
    recv(sock, buf, sizeof(buf), 0);
    printf("Client recieved:\n%s\n", buf);
    close(sock);
}
   