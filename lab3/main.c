#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc)
{
    pid_t pid;
    int rv;
	char *argv[16];
	printf("Input command: ");
	scanf("%s", argv);

	switch(pid=fork()) {
	case -1:
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	case 0:
		printf(" CHILD: Это процесс-потомок!\n");
		printf(" CHILD: Мой PID -- %d\n", getpid());
		printf(" CHILD: PID моего родителя -- %d\n", getppid());

		execl(argv[0], " ","-s", "qwe", NULL);
	default:
		printf("PARENT: Это процесс-родитель!\n");
		printf("PARENT: Мой PID -- %d\n", getpid());
		printf("PARENT: PID моего потомка %d\n",pid);
		printf("PARENT: Я жду, пока потомок не вызовет exit...\n");
		wait(pid);
		printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
		printf("PARENT: Выход!\n");
	}
	
	
}

