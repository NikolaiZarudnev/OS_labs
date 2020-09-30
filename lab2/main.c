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

int main(int argc, char const *argv[])
{
    list_proc(argv[1]);

    // if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
    // {
    //     printf("Авторы: Заруднев Николай, Каширин Владислав, Бесаева Далия\n");
    //     printf("Доступные аргументы:\n\t-r: переместить файл\n\t-c: копировать файл\n\t-d: удалить файл\n\t-s: общий размер указанной директории или файла\n\t-f: отображение всех файлов указанной директории\n\t-p: отображение всех процессов из файловой системы procf");
    //     printf("Управление файловой системой\n");
    //     printf("./main --help/-h\n");
    // } else if (!strcmp(argv[1], "--remove") || !strcmp(argv[1], "-r"))
    // {
    //     printf("hello\n");
    //     my_remove(argv[2], argv[3]);
    // }
    
    /*replace file*/

    /*copy file*/
    //my_copy(argv[1], argv[2]);

    /*delete file*/

    /*total size*/

    /*display all files in the dir*/

    /*

    struct dirent *pDirent;

    DIR *list_dir = opendir(arg2);
    while ((pDirent = readdir(list_dir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
    }
    
    */

    /*list all proc from /procfs */
    list_proc();

    return 0;
}

