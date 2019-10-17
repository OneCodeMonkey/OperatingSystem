#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>                                                           
#include<stdlib.h>

int main(void)
{
    pid_t fpid; //fpid表示fork函数返回的值
    int count=0;
    fpid=fork(); 
    if (fpid < 0) 
        printf("error in fork!\n"); 
    else if (fpid == 0) {
        printf("i am the child process, my process id is %d\n",getpid()); 
        printf(" my parent process id is %d\n",getppid()); 
        count++;
    }
    else {
        printf("i am the parent process, my process id is %d\n",getpid()); 
        count++;
    }
    printf("count 统计结果是: %d\n",count);
    while(1);//无限阻塞
    return 0;
}