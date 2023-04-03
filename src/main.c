#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int isNumber(char num[]){
    for (int i=0; num[i]!='\0'; i++){
        if (isdigit(num[i])==0){
            return 0;
        }
    } return 1;
}

void check(int ret, const char* message) {
    if (ret != -1) {
        return;
    }
    int error = errno;
    perror(message);
    exit(error);
}

int main() {
    DIR *dir = opendir("/proc");
    if (dir == NULL){
        int error = errno;
        perror("opendir");
        exit(error);
    }

    printf("%*s", 5, "PID");
    printf(" CMD\n");
    struct dirent *dp;


    errno = 0;
    while ((dp = readdir(dir)) != NULL) {
        if (isNumber(dp->d_name) != 0) {


            char str[1024] = "/proc/";

            strcat(str, dp->d_name);
            strcat(str,"/status");

            int fd = open(str, O_RDONLY);
            check(fd, "open");

            char buffer[4096];
            int bytes_read = read(fd, buffer, sizeof(buffer));
            check(bytes_read, "read");

            int i = 0;
            while (buffer[i] != '\n') {
                i++;
            }



            char name[4096];
            strncpy(name, buffer+6, i-6);
            name[i-6] = '\0';
            strcat(name, "\n");
            printf("%*s", 5, dp->d_name);

            printf("%s", " ");

            printf("%s", name);

            int closefd = close(fd);
            check(closefd, "close");
        }
    }
    if (errno != 0){
        int error = errno;
        perror("readdir");
        exit(error);
    }
    int closedirerr = closedir(dir);
    check(closedirerr, "closedir");

    return 0;
}
