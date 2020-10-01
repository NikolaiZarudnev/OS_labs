#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int my_copy(const char *arg1, const char *arg2)
{
    int fh1, fh2;    
    fh1 = open(arg1, O_RDONLY);
    if (fh1 == -1)
    {
        printf("faile is not open\n");
        return -1;
    }

    char *namefile = malloc(sizeof(arg1));
    namefile = strrchr(arg1, '/');

    char *arg3 = malloc(sizeof(arg2) + sizeof(namefile));
    strcat(arg3, arg2);
    strcat(arg3, namefile);

    fh2 = creat(arg3, __S_IWRITE | __S_IREAD);
    if (fh2 == -1)
    {
        printf("fail is not open\n");
        return -1;
    }
    
    printf("Moving\n");
    char *buf = malloc(3);
    while (read(fh1, buf, 3))
    {
        write(fh2, buf, 3);
    }
    printf("done\n");

    close(fh1);
    close(fh2);
    return 0;
}

int list_proc(){

    struct dirent *pDirent;
    DIR *pDir = opendir ("/proc");
    while ((pDirent = readdir(pDir)) != NULL) 
    {   
        if (isdigit(pDirent->d_name[0]))
        {
            printf ("%s\n", pDirent->d_name);
        }
    }
    
    closedir (pDir);

    return 0;
}

int count_dir_size(char *dir)
{
    struct dirent *pD;
    struct stat file_stat;
    int size = 0;

    DIR *pDirec = opendir(dir);
    while ((pD = readdir(pDirec)) != NULL)
    {
        if (stat(pD->d_name, &file_stat) == 0)
        {
            size += file_stat.st_size;
        }

    }
    printf("Общий размер файлов каталога %s равен %d байт\n\n", dir, size);
    closedir(pDirec);

    return 0;
}

int my_delete(char *dir)
{
    printf ("Удаление файла: ");
   if (-1 == remove (dir))
      printf ("Ошибка\n");
   else 
      printf ("Выполнено\n");

   return 0;
}

int my_replace(const char *arg1, const char *arg2)
{
    my_copy(arg1, arg2);
    my_delete(arg1);
}

int list_files(char *dir)
{
    struct dirent *pDirent;
    DIR *pDir = opendir (dir);
    while ((pDirent = readdir(pDir)) != NULL)
    {
        printf ("[%s]\n", pDirent->d_name);
    }
    closedir (pDir);
}

int main(int argc, char const *argv[])
{
    list_proc(argv[1]);

    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
    {
        printf("Авторы: Заруднев Николай, Каширин Владислав, Бесаева Далия\n");
        printf("Доступные аргументы:\n\t-r: переместить файл\n\t-c: копировать файл\n\t-d: удалить файл\n\t-s: общий размер указанной директории или файла\n\t-f: отображение всех файлов указанной директории\n\t-p: отображение всех процессов из файловой системы procf");
        printf("Управление файловой системой\n");
        printf("./main --help/-h\n");
    }
    else if (!strcmp(argv[1], "--delete") || !strcmp(argv[1], "-d"))
    {
        my_delete(argv[2]);
    }
    else if (!strcmp(argv[1], "--replace") || !strcmp(argv[1], "-r"))
    {
        my_replace(argv[2], argv[3]);
    }
    else if (!strcmp(argv[1], "--copy") || !strcmp(argv[1], "-c"))
    {
        my_copy(argv[2], argv[3]);
    }
    else if (!strcmp(argv[1], "--size") || !strcmp(argv[1], "-s"))
    {
        count_dir_size(argv[2]);
    }
    else if (!strcmp(argv[1], "--list") || !strcmp(argv[1], "-l"))
    {
        list_files(argv[2]);
    }
    else if (!strcmp(argv[1], "--procfs") || !strcmp(argv[1], "-p"))
    {
        list_proc(argv[2]);
    }
    return 0;
}

