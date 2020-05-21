#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
    
int main(int argc, char* argv[]) 
{
    pid_t child = fork();
    char *arg[] = {"child", NULL};
    if (child != 0) wait(&child); //parent procces waits the child
    else execvp("./child", arg); //child procces execute a programm
    if (WIFEXITED(child)) printf("Child procces is OK\n");
    else printf("Child procces completed with %d error\n", WEXITSTATUS(child));
    return 0;
}
