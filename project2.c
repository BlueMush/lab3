#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <path name>\n", argv[0]);
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if(dir == NULL) {
        printf("failed open\n");
        return 1;
    }
    struct dirent *de=NULL;
    while((de = readdir(dir))!=NULL) {
        printf("%s %ld\n",de->d_name, de->d_ino);
    }
    closedir(dir);
    return 0;
}
