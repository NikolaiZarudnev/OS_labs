#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    char *error = "err\n";
    void *handle = dlopen ("/home/nikolay/Рабочий стол/OS_labs/lab5_example/libworld.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(-1);
    }
    void (*world)() = dlsym(handle, argv[1]);
    if ((error = dlerror()) != NULL) {
        fprintf (stderr, "%s\n", error);
        printf("err dlsym\n");
        exit(-1);
    }
    (*world)();
    printf("Done\n");
    //printf("asd", (*world));
    dlclose(handle);
    
    return 0;
}