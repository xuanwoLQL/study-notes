/* fork_nowait.c —— 任务3(3)：父进程不等待子进程，产生"孤儿进程"
 *                子进程的父进程会变成 init/systemd（PID=1）
 * 编译：gcc -Wall -g fork_nowait.c -o fork_nowait
 * 运行：./fork_nowait
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {                    /* 子进程 */
        printf("[子进程] 刚创建：PID=%d PPID=%d（此时父进程还在）\n",
               getpid(), getppid());
        fflush(stdout);

        sleep(5);                      /* 这 5 秒内父进程已经退出 */

        printf("[子进程] 睡眠 5 秒后：PID=%d PPID=%d（父进程已退出，被 PID=1 的 init/systemd 收养）\n",
               getpid(), getppid());
        fflush(stdout);
        exit(0);
    }

    /* 父进程：不调用 wait()，2 秒后结束；留出时间让子进程先打印真实的父进程 PID */
    printf("[父进程] PID=%d 创建了子进程 %d，本进程 2 秒后退出（不调用 wait）\n",
           getpid(), pid);
    fflush(stdout);
    sleep(2);
    exit(0);
}
