/* crash_demo.c —— 任务2：进程异常终止（SIGSEGV，段错误）
 * 编译：gcc -Wall -g crash_demo.c -o crash_demo
 * 运行：./crash_demo ; echo $?      # 退出码为 139 = 128 + 11(SIGSEGV)
 */
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("进程（PID：%d）开始运行...\n", getpid());
    fflush(stdout);

    int *p = NULL;                            /* 空指针 */
    printf("准备解引用空指针 p = %p\n", (void *)p);
    fflush(stdout);

    *p = 10;                                  /* 非法访问：内核发送 SIGSEGV 信号 */

    printf("这一行永远不会被执行\n");          /* 进程已被信号杀死，不会执行 */
    return 0;
}
