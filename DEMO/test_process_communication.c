#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int f1(int x)
{
    printf("func1 当前进程的 PID 是：(%d)\n", getpid());
    if(x==1) {
        printf("func1 输出：(1)\n");
        return 1;
    } else {
        int temp = x * f1(x-1);
        printf("func1 输出：(%d)\n", temp);
        return temp;
    }
}

int f2(int y)
{
    printf("func2 当前进程的 PID 是：(%d)\n", getpid());
    if(y ==1||y==2) {
        printf("func2 输出：(1)\n");
        return 1;
    } else {
        int temp = f2(y - 1) + f2(y - 2);
        printf("func2 输出：(%d)\n", temp);
        return temp;
    }
}

int main(int argc,char* argv[])
{
    int x,y;
    printf("Input x,y\n");
    scanf("%d %d",&x,&y);
    int pid1,pid2;
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];
 
    if(pipe(pipe1)<0) {
        printf("pipe1 error");
    }
    if(pipe(pipe2)<0) {
        printf("pip2 error");
    }
    if(pipe(pipe3)<0) {
        printf("pipe3 error");
    }
    if(pipe(pipe4)<0) {
        printf("pipe4 error");  
    }
    if((pid1=fork())<0) {
        perror("pipe not create");
    } else if(pid1==0) {
        close(pipe1[1]);
        close (pipe2[0]);
        int x1;
        read(pipe1[0],&x1,sizeof(int));
        int z=f1(x1);

        write(pipe2[1],&z,sizeof(int));
        close(pipe1[0]);
        close(pipe2[1]);
        while(1);
    } else {
        //Father process

        if((pid2=fork())<0) {
            perror("Process not create ");
            exit(EXIT_FAILURE);
        } else if(pid2==0) {
            close(pipe3[1]);
            close(pipe4[0]);
            int y1;
            read(pipe3[0],&y1,sizeof(int));
            int z=f2(y1);
            write(pipe4[1],&z,sizeof(int));
            close(pipe3[0]);
            close(pipe4[1]);
            while(1);
        }
        printf("main 当前进程的 PID 是：(%d)\n", getpid());

        close(pipe1[0]);
        close(pipe2[1]);
        close(pipe3[0]);
        close(pipe4[1]);

        write(pipe1[1],&x,sizeof(int));
        write(pipe3[1],&y,sizeof(int));
        read(pipe2[0],&x,sizeof(int));
        read(pipe4[0],&y,sizeof(int));

        int z=x+y;

        printf("main PID:(%d) - 当前进程的输出是 (%d)\n",getpid(), z);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe3[1]);
        close(pipe4[0]);
    }

    while(1);
    return 0;
}