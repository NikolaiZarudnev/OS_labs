#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
int my_remove(char *arg1, char *arg2)
{
    int fh1, fh2;
    char *namefile = malloc(sizeof(arg1));
    namefile = strrchr(arg1, '/');
    printf("%s\n", namefile);
    fh1 = open(arg1, O_RDONLY);
    
    char *arg3 = malloc(sizeof(arg2) + sizeof(namefile));
    strcat(arg3, arg2);
    strcat(arg3, namefile);
    fh2 = creat(arg3, __S_IWRITE | __S_IREAD);
    char *buf = malloc(3);
    while (read(fh1, buf, 3))
    {
        write(fh2, buf, 3);
    }
    printf("done\n");
    
    /*
    struct dirent *pDirent;
    DIR *from_dir = opendir(arg1);
    DIR *to_dir = opendir(arg2);
    while ((pDirent = readdir(from_dir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
    }


    closedir (from_dir);
    closedir (to_dir);
    */
   close(fh1);
   close(fh2);
   printf("done2\n");
   return 0;
}
int main(int argc, char const *argv[])
{
    int h = my_remove("asd/test1.txt", "qwe2");
    printf("asdasd11");
    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
    {
        printf("Авторы: Заруднев Николай, Каширин Владислав, Бесаева Далия\n");
        printf("Доступные аргументы:\n\t-r: переместить файл\n\t-c: копировать файл\n\t-d: удалить файл\n\t-s: общий размер указанной директории или файла\n\t-f: отображение всех файлов указанной директории\n\t-p: отображение всех процессов из файловой системы procf");
        printf("Управление файловой системой\n");
        printf("./main --help/-h\n");
    } else if (!strcmp(argv[1], "--remove") || !strcmp(argv[1], "-r"))
    {
        printf("hello\n");
        my_remove(argv[2], argv[3]);
    }
    printf("asdasd");
    /*replace file*/

    /*copy file*/

    /*delete file*/

    /*total size*/

    /*display all files in the dir*/
    /*struct dirent *pDirent;
    DIR *list_dir = opendir(arg2);
    while ((pDirent = readdir(list_dir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
    }*/
    /*list all proc from /procfs */
    return 0;
}

