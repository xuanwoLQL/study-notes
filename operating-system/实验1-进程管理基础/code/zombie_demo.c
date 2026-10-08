/* zombie_demo.c —— 任务3(3)：父进程不回收已终止的子进程，产生"僵尸进程"（STAT=Z）
 * 编译：gcc -Wall -g zombie_demo.c -o zombie_demo
 * 运行：./zombie_demo
 *       在另一个终端执行： ps -o pid,ppid,stat,cmd -p <子进程PID>
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

    if (pid == 0) {                       /* 子进程：立即终止 */
        printf("[子进程] PID=%d 立即退出（退出码 0）\n", getpid());
        fflush(stdout);
        exit(0);
    }

    /* 父进程：故意不调用 wait()，子进程终止后成为僵尸进程 */
    printf("[父进程] PID=%d，子进程 %d 已终止但未被回收\n", getpid(), pid);
    printf("父进程将睡眠 60 秒，请在另一个终端执行：\n");
    printf("    ps -o pid,ppid,stat,cmd -p %d\n", pid);
    printf("    （STAT 显示为 Z 或 Z+ 即为僵尸进程）\n");
    fflush(stdout);

    sleep(60);                            /* 这 60 秒内子进程一直是僵尸进程 */

    printf("[父进程] 即将退出，僵尸子进程被 PID=1 的 init/systemd 接管并回收\n");
    return 0;
}
