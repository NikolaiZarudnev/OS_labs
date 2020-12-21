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
#include <dlfcn.h>
#include <signal.h>
#define STDOUT 1
int signalhandler(int sig)
{
	switch (sig)
	{
	case SIGUSR1:
		printf("received SIGUSR1\n");
		break;
	case SIGUSR2:
		printf("received SIGUSR2\n");
		break;
	case SIGKILL:
		printf("received SIGKILL\n");
		break;
	case SIGSTOP:
		printf("received SIGSTOP\n");
		break;
	default:
		break;
	}
}

int create_proc_fileManage(char **flags)
{
    pid_t pid;
    int rv;
    switch(pid=fork()) {
    case -1:
            perror("fork"); /* произошла ошибка */
            exit(1); /*выход из родительского процесса*/
    case 0:
            printf("  CHILD: Выполняю fileManage; c флагом %s\n", flags[1]); 
            execv("fileManage", flags);
            kill(getppid(), SIGUSR1);//передаю родителю пользовательский сигнал SIGUSR1
    default:
            wait(&pid);
            //printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
            printf("PARENT: Выход!\n");
            raise(SIGUSR2);//родитель сам себе посылает пользовательский сигнал SIGUSR2
    }
}

int create_pr_name(const char *name_programm, char *flag1, char *flag2, char *flag3)
{
	pid_t pid;
	int rv;
	switch(pid=fork()) {
	case -1:
		perror("fork error"); /* произошла ошибка */
	    exit(1); /*выход из родительского процесса*/
	case 0:
	    printf("  CHILD: Выполняю %s; c флагом %s\n", name_programm, flag1);
	    execl(name_programm, name_programm, flag1, flag2, flag3, NULL);
	default:
	    wait(&pid);
	    printf("PARENT: Выход!\n");
	}
}

int background_process(char *name_programm, char *arg1, char *arg2, char *arg3) 
{
    pid_t pid;
	int rv;
    pid = fork();
    if (pid == 0) {
        daemon (1, 0);
        execl (name_programm, name_programm, arg1, arg2, arg3, NULL);
        while (1) {
            if (waitpid(pid, &rv, 0) == pid) {
                _exit (EXIT_FAILURE);
            }
        }
    } else if (pid < 0)
        rv = -1;
    else if (waitpid (pid, &rv, 0) != pid)
        rv = -1;

    return rv;
}

int valid_fileManage_flag(char *fl1)
{
    if (!strcmp(fl1, "-d") || !strcmp(fl1, "--delete")  || 
        !strcmp(fl1, "-r") || !strcmp(fl1, "--replace") || 
        !strcmp(fl1, "-c") || !strcmp(fl1, "--copy")    || 
        !strcmp(fl1, "-s") || !strcmp(fl1, "--size")    || 
        !strcmp(fl1, "-l") || !strcmp(fl1, "--list")    || 
        !strcmp(fl1, "-p") || !strcmp(fl1, "--procfs"))
        return 1;
    return 0;      
}

int new_client(int sock)
{
    FILE *ERRstat;
    char buf[5][32];
    char send_toclient[1024];
    int size;
    int newsock, clnlen;
    int x;
    struct sockaddr_in client;
    newsock = accept(sock, &client, &clnlen); // появление нового клиента
    char *error = "";
    void *handle = dlopen ("/home/nikolay/Рабочий стол/OS_labs/lab6/libcookies.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(-1);
    }

    printf("New client: %s\n",inet_ntoa(client.sin_addr));
    while((size = recv(newsock, buf, sizeof(buf), 0)) != 0)
    {
        printf("buffer: %s\n", buf[1]);
        if(!strcmp(buf[1], "-h") || !strcmp(buf[1], "--help")) {
            strcpy(send_toclient, "Авторы: Заруднев Николай, Каширин Владислав, Бесаева Далия\nДоступные аргументы:\n\t-r: переместить файл\n\t-c: копировать файл\n\t-d: удалить файл\n\t-s: общий размер указанной директории или файла\n\t-f: отображение всех файлов указанной директории\n\t-p: отображение всех процессов из файловой системы procf\nУправление файловой системой\n./client --help/-h\n./client --delete/-d 'filename'\n./client --replace/-r 'sourcefilename' 'todir'\n./client --copy/-c 'sourcefilename' 'todir'\n./client --size/-s 'dir'\n./client --list/-l 'dir'\n./client --procfs/-p");
            continue;
        }
        if (buf == NULL) //Если флаги не введены
        {
            printf("Error: Server recieved NULL\n");
            return 0;
            //Ловим сигналы Нибиру
        }
        else if (valid_fileManage_flag(buf[1])) //Если флаг совпадает с флагами из лаб. 2
        {
            create_proc_fileManage(buf);
        }
        else if (!strcmp(buf[1], "--demon")) //Если процесс нужно запустить в фоновом режиме
        {
            background_process(buf[2], buf[3], buf[4], buf[5]);
        }
        else //Если процесс нужно запустить НЕ в фоне
        {
            create_pr_name(buf[1], buf[2], buf[3], buf[4]);
        }
        send(newsock, send_toclient, sizeof(send_toclient), 0); // отправляем эхо

        void (*world)() = dlsym(handle, "cookie");
        if ((error = dlerror()) != NULL) {
            ERRstat = fopen("ERRORS.txt", "a+");
            fprintf (ERRstat, "%s\n %d", error);
            fclose(ERRstat);
            exit(-1);
        }
        (*world)();
        //x = 100;
        dlclose(handle);
        send(newsock, send_toclient, sizeof(send_toclient), 0); // отправляем эхо
    } // пока получаем от клиента
    close(newsock);
    return 0;
}

int main(int argc, char *argv[])
{
    signal(SIGUSR1, signalhandler);
    signal(SIGUSR2, signalhandler);
    signal(SIGINT, signalhandler);
    signal(SIGTERM, signalhandler);
    signal(SIGKILL, signalhandler);
    signal(SIGSTOP, signalhandler);

    struct sockaddr_in server, client;
    int sock = socket(AF_INET, SOCK_STREAM, 0); // создание сокета
    
    
    // структура для сервера
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server.sin_port = htons(2019); // порт сервера
    bind(sock, &server, sizeof(server)); // связка с сокетом
    listen(sock,5); // размер очереди
    pthread_t thread; //создаем идентификатор потока
    while(1)
    {
        pthread_create(&thread, NULL, new_client, sock);
        pthread_join(thread, NULL);
        
    }
    
    close(sock);
}
