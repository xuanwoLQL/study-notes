/* fork_wait.c —— 任务3(2)：父进程调用 wait() 回收子进程，避免僵尸进程
 * 编译：gcc -Wall -g fork_wait.c -o fork_wait
 * 运行：./fork_wait
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>            /* wait、WIFEXITED、WEXITSTATUS 声明 */

int main(void)
{
    pid_t pid = fork();                  /* 创建子进程 */

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {               /* 子进程 */
        printf("[子进程] 我是子进程，PID=%d，PPID=%d\n", getpid(), getppid());
        fflush(stdout);
        sleep(2);                        /* 阻塞 2 秒，模拟耗时操作 */
        printf("[子进程] 执行完毕，调用 exit(7) 终止\n");
        fflush(stdout);
        exit(7);                         /* 用非 0 退出码，便于观察回收结果 */
    }

    /* 父进程 */
    printf("[父进程] 我是父进程，PID=%d，子进程PID=%d，正在等待子进程结束…\n",
           getpid(), pid);
    fflush(stdout);

    int status;
    pid_t done = wait(&status);          /* 阻塞等待，直到有子进程终止并回收其内核资源 */
    if (done == -1) {
        perror("wait");
        return 1;
    }

    if (WIFEXITED(status))               /* 判断是否正常终止 */
        printf("[父进程] 子进程 %d 正常终止，退出码=%d\n",
               done, WEXITSTATUS(status));
    else if (WIFSIGNALED(status))        /* 判断是否被信号杀死 */
        printf("[父进程] 子进程 %d 被信号 %d 终止\n", done, WTERMSIG(status));

    printf("[父进程] 子进程资源已回收，无僵尸进程，父进程结束\n");
    return 0;
}
