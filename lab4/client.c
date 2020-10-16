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

int main()
{
    // структура для сокета
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2019);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    int sock = socket(AF_INET, SOCK_STREAM, 0); // создаем сокет
    connect(sock, &server, sizeof(server)); // соединяемся с сервером
    // отправка сообщения
    send(sock, "Hello", 6, 0);
    char buf[255] = "";
    recv(sock, buf, sizeof(buf), 0);
    printf("Сервер прислал: %s\n",buf);
    close(sock);
}
   