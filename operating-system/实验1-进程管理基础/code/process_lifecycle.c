/* process_lifecycle.c —— 任务2：单进程的生命周期与状态转换
 *   运行态(R) -> 阻塞态(S，sleep) -> 运行态(R，循环计数) -> 终止(exit 0)
 * 编译：gcc -Wall -g process_lifecycle.c -o process_lifecycle
 * 运行：./process_lifecycle
 */
#include <stdio.h>
#include <stdlib.h>      /* exit 函数声明 */
#include <unistd.h>

int main(void)
{
    printf("进程（PID：%d）开始运行...\n", getpid());
    printf("【第 1 阶段】进入阻塞态：sleep(15)，此时用 ps 观察 STAT 应为 S\n");
    printf("    观察命令：ps -p %d -o pid,ppid,stat,cmd\n", getpid());
    fflush(stdout);

    sleep(15);               /* 可中断睡眠：进程被挂起，让出 CPU，状态变为 S */

    printf("【第 2 阶段】睡眠结束，进程被唤醒，重新进入运行态 R\n");
    fflush(stdout);

    for (int i = 0; i < 10; i++) {
        printf("计数：%d\n", i);
        fflush(stdout);
        /* 忙等待（每次约 1 秒）：进程持续占用 CPU，处于运行态 R，便于 ps 抓到 */
        for (volatile long j = 0; j < 4000000000L; j++) {
            ;
        }
    }

    printf("进程（PID：%d）即将终止...\n", getpid());
    fflush(stdout);
    exit(0);                 /* 正常终止，退出码 0，父进程可通过 wait 获取 */
}
