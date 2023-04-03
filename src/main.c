#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(){




printf("  %s %s\n","PID", "CMD");

DIR * p1;
DIR * p2;
struct dirent *dp;
p1=opendir("/proc");
for (dp=readdir(p1);dp!=NULL;dp=readdir(p1)){
if((isdigit(dp->d_name[0])!=0) & (strcmp(dp->d_name, ".") != 0)){
char path[15];
snprintf(path, 15, "/proc/%s", dp->d_name);
p2=opendir(path);
if (p2<0){



}

else{closedir(p2);
char* new_str=(char*)malloc(sizeof(char)*(strlen(dp->d_name)+1));
strcpy(new_str,dp->d_name);
char path2[25];
snprintf(path2, 25, "/proc/%s/status", dp->d_name);
int fd=open(path2,O_RDONLY); if(fd<0){
}else{
char* buf=(char*)calloc(1024,sizeof(char));
ssize_t sz=read(fd, buf,15);
if (sz<0){
int error = errno;
perror("read");
return error;
}
int i=6;
int count=0;
char* s1=malloc(sizeof(char)*15);
while (buf[i]!='\n'){
    s1[i-6]=buf[i];
    i++;
    count++;
    }
s1=realloc(s1,sizeof(char)*(count+1));
s1[count]='\0';
if (strlen(new_str)==1){
    printf("    %s",new_str);
}else if(strlen(new_str)==2){
    printf("   %s", new_str);
}else if(strlen(new_str)==3){
    printf("  %s", new_str);
}else if(strlen(new_str)==4){
    printf(" %s", new_str);
}else if(strlen(new_str)==5){
    printf("%s", new_str);
}
printf(" %s\n", s1);
close(fd);
free(buf);
free(new_str);
free(s1);}}}
}closedir(p1);
    return 0;
}
