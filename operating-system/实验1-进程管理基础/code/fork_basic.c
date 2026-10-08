/* fork_basic.c —— 任务3(1)：fork() 的基本行为 + 父子进程地址空间独立性
 * 编译：gcc -Wall -g fork_basic.c -o fork_basic
 * 运行：./fork_basic
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    int value = 100;              /* 父子进程各自持有一份副本 */

    pid_t pid = fork();           /* 调用一次，返回两次 */

    if (pid < 0) {                /* 创建失败：父进程中得到 -1 */
        perror("fork failed");
        return 1;
    } else if (pid == 0) {        /* 子进程：fork() 返回 0 */
        value += 50;              /* 只修改子进程自己的副本 */
        printf("[子进程] PID=%d PPID=%d value=%d &value=%p\n",
               getpid(), getppid(), value, (void *)&value);
        fflush(stdout);
    } else {                      /* 父进程：fork() 返回子进程的 PID */
        sleep(1);                 /* 让子进程先打印，便于对比 */
        value -= 50;              /* 只修改父进程自己的副本 */
        printf("[父进程] PID=%d PPID=%d 子进程PID=%d value=%d &value=%p\n",
               getpid(), getppid(), pid, value, (void *)&value);
        fflush(stdout);
    }

    printf("[%s] 本进程执行到同一行代码后结束\n", (pid == 0) ? "子进程" : "父进程");
    return 0;                     /* 父子进程都从这里返回 */
}
