#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h"))
    {
        printf("Авторы: Заруднев Николай, Каширин Владислав, Бесаева Далия\n");
        printf("Доступные аргументы:\n\t-r: переместить файл\n\t-c: копировать файл\n\t-d: удалить файл\n\t-s: общий размер указанной директории или файла\n\t-f: отображение всех файлов указанной директории\n\t-p: отображение всех процессов из файловой системы procf");
        printf("Управление файловой системой\n");
        printf("./main --help/-h\n");
    }
    /*replace file*/

    /*copy file*/

    /*delete file*/

    /*total size*/

    /*display all files in the dir*/

    /*list all proc from /procfs */
    return 0;
}
