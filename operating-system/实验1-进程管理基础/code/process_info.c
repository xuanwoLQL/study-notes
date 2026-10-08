/* process_info.c —— 任务1：打印当前进程的身份信息
 * 编译：gcc -Wall -g process_info.c -o process_info
 * 运行：./process_info
 * 说明：程序打印完身份信息后立即结束，可用 echo $$ 对比程序输出的 PPID 进行验证。
 */
#include <stdio.h>
#include <unistd.h>      /* getpid、getppid、getuid、geteuid 等函数声明 */
#include <sys/types.h>

int main(void)
{
    printf("当前进程   PID  : %d\n", getpid());          /* 进程 ID */
    printf("父进程     PPID : %d\n", getppid());         /* 父进程 ID */
    printf("进程组     PGID : %d\n", getpgid(getpid())); /* 进程组 ID */
    printf("实际用户   UID  : %d\n", getuid());          /* 实际用户 ID */
    printf("有效用户   EUID : %d\n", geteuid());         /* 有效用户 ID */
    printf("实际组     GID  : %d\n", getgid());          /* 实际组 ID */
    printf("有效组     EGID : %d\n", getegid());         /* 有效组 ID */
    return 0;
}
