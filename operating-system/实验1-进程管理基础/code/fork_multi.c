/* fork_multi.c —— 任务3(4)：循环创建 3 个子进程并发执行，父进程用 waitpid 循环回收
 * 编译：gcc -Wall -g fork_multi.c -o fork_multi
 * 运行：./fork_multi    （多运行几次，观察输出顺序是否固定）
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    const int N = 3;
    const int start[3] = {1, 6, 11};        /* 三个子进程各自的计数起点 */

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {                     /* 子进程：做完自己的任务立即退出 */
            printf("[子进程%d] PID=%d PPID=%d 开始计数 %d~%d\n",
                   i + 1, getpid(), getppid(), start[i], start[i] + 4);
            fflush(stdout);
            for (int k = start[i]; k < start[i] + 5; k++) {
                printf("[子进程%d] 计数：%d\n", i + 1, k);
                fflush(stdout);
                usleep(300000);             /* 睡眠 0.3 秒，便于观察并发交错 */
            }
            printf("[子进程%d] PID=%d 完成任务，退出码=%d\n", i + 1, getpid(), i + 1);
            fflush(stdout);
            exit(i + 1);                    /* 退出码 1/2/3，便于父进程区分 */
        }

        printf("[父进程] 已创建子进程：PID=%d\n", pid);
        fflush(stdout);
    }

    /* 父进程：循环回收全部子进程，避免产生僵尸进程 */
    int status, cnt = 0;
    pid_t done;
    while ((done = waitpid(-1, &status, 0)) > 0) {
        cnt++;
        if (WIFEXITED(status))
            printf("[父进程] 回收子进程 PID=%d，退出码=%d（第 %d 个被回收）\n",
                   done, WEXITSTATUS(status), cnt);
        else if (WIFSIGNALED(status))
            printf("[父进程] 子进程 PID=%d 被信号 %d 终止\n",
                   done, WTERMSIG(status));
    }

    printf("[父进程] 全部 %d 个子进程均已回收，无僵尸进程\n", cnt);
    return 0;
}
