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
#include <pthread.h>
int process(char *arg){
    int x = 0;
    if (!strcmp(arg, "-d"))
    {
        printf("x--\n");
        x--;
    }
    else if(!strcmp(arg, "-i"))
    {
        printf("x++\n");
        x++;
    }
    return x;
    pthread_exit(0);
}
void server_client(int q, int w, int e)
{
    printf("%d %d %d\n", q, w, e);
    struct sockaddr_in server, client;
    int sock = socket(AF_INET, SOCK_STREAM, 0); // создание сокета
    int size;
    char buf[255];
    // структура для сервера
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server.sin_port = htons(2019); // порт сервера
    bind(sock, &server, sizeof(server)); // связка с сокетом
    listen(sock,5); // размер очереди
    int x = 0;
    while(1)
    {
        int newsock, clnlen;
        newsock = accept(sock, &client, &clnlen); // появление нового клиента
        printf("New client: %s\n",inet_ntoa(client.sin_addr));
        while((size = recv(newsock, buf, sizeof(buf), 0)) != 0)
        {
            x = process(buf);
            send(newsock, &x, sizeof(x), 0); // отправляем эхо
        } // пока получаем от клиента
        close(newsock);
    }
    close(sock);
}
int main(int argc, char *argv[])
{
    
    //создаем идентификатор потока
    pthread_t thread;

    pthread_create(&thread, NULL, server_client, NULL);
    //ждем завершения потока
    pthread_join(thread, NULL);
    //создаем поток по идентификатору thread и функции потока threadFunc
    //и передаем потоку указатель на данные thread_data
    
    
}
