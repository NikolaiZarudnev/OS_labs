#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int create_pr_lab2(char **flags)
{
  pid_t pid;
  int rv;
  switch(pid=fork()) {
  case -1:
        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
  case 0:
        printf("  CHILD: Это процесс-потомок!\n");
        printf("  CHILD: Выполняю l2; c флагом %s\n", flags[1]);
        printf("***********************************************\n");
        execv("l2", flags);
  default:
        printf("PARENT: Это процесс-родитель!\n");
        printf("PARENT: Я жду, пока потомок не вызовет exit...\n");
        wait(&pid);
        printf("***********************************************\n");
        printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
        printf("PARENT: Выход!\n");
  }
}

int create_pr_name(const char *name_programm, char *fl1, char *fl2, char *fl3)
{
  pid_t pid;
  int rv;
  switch(pid=fork()) {
  case -1:
        perror("fork"); /* произошла ошибка */
        exit(1); /*выход из родительского процесса*/
  case 0:
        printf("  CHILD: Это процесс-потомок!\n");
        printf("  CHILD: Выполняю %s; c флагом %s\n", name_programm, fl1);
        execl(name_programm, " ", fl1, fl2, fl3, NULL);
  default:
        printf("PARENT: Это процесс-родитель!\n");
        printf("PARENT: Я жду, пока потомок не вызовет exit...\n");
        wait(&pid);
        printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
        printf("PARENT: Выход!\n");
  }
}

int valid_l2_flag(char *fl1)
{
      if (!strcmp(fl1, "-h") || !strcmp(fl1, "--help")    || 
          !strcmp(fl1, "-d") || !strcmp(fl1, "--delete")  || 
          !strcmp(fl1, "-r") || !strcmp(fl1, "--replace") || 
          !strcmp(fl1, "-c") || !strcmp(fl1, "--copy")    || 
          !strcmp(fl1, "-s") || !strcmp(fl1, "--size")    || 
          !strcmp(fl1, "-l") || !strcmp(fl1, "--list")    || 
          !strcmp(fl1, "-p") || !strcmp(fl1, "--procfs"))
            return 1;
      return 0;      
}
int main(int argc, char *argv[])
{
      if (argv[1] == NULL) //Если флаги не введены
      {
            //Ловим сигналы Нибиру
      }
      else if (valid_l2_flag(argv[1])) //Если флаг совпадает с флагами из лаб. 2
      {
            create_pr_lab2(argv);
      }
      else if (!strcmp(argv[1], "--demon")) //Если процесс нужно запустить в фоновом режиме
      {
            //создаем демона внутри себя
      }
      else //Если процесс нужно запустить НЕ в фоне
      {
            create_pr_name_(argv[2], argv[3], argv[4], argv[5]);
      }
      return 0;
}

