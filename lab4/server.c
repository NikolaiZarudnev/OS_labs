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
    struct sockaddr_in server, client;
    int sock = socket(AF_INET, SOCK_STREAM, 0); // создание сокета
    int size;
    char buf[1025];
    // структура для сервера
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server.sin_port = htons(2019); // порт сервера
    bind(sock, &server, sizeof(server)); // связка с сокетом
    listen(sock,5); // размер очереди
    while(1)
    {
        int newsock, clnlen;
        newsock = accept(sock, &client, &clnlen); // появление нового клиента
        printf("Новый клиент: %s\n",inet_ntoa(client.sin_addr));
        while((size = recv(newsock, buf, sizeof(buf), 0)) != 0) // пока получаем от клиента
            send(newsock, buf, sizeof(buf), 0); // отправляем эхо
        close(newsock);
    }
    close(sock);
}
