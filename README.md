# 学习笔记：操作系统 / 数据库

信息安全专业的课程学习笔记，Markdown 格式，可直接在 GitHub 或 Obsidian 中阅读。

## 目录

| 目录 | 内容 |
| --- | --- |
| `operating-system/` | 操作系统：内核架构笔记 + 进程管理实验 |
| `database/` | 数据库考试复习笔记 |
| `attachments/` | 笔记中引用的图片（已从 Obsidian 语法转为标准 Markdown 链接） |

## 操作系统

### 笔记

- `宏内核和微内核.md` — 两种内核架构的对比

### 实验1 进程管理基础

`code/` 目录下有 8 个 C 程序和一份 Makefile，覆盖进程管理的核心概念：

| 文件 | 内容 |
| --- | --- |
| `process_info.c` | 获取并打印进程信息（PID/PPID 等） |
| `process_lifecycle.c` | 进程的创建、执行与退出 |
| `fork_basic.c` | `fork()` 基本用法 |
| `fork_wait.c` | 父进程用 `wait()` 回收子进程 |
| `fork_nowait.c` | 不回收子进程的后果 |
| `zombie_demo.c` | 僵尸进程的产生与处理 |
| `fork_multi.c` | 创建多个子进程 |
| `crash_demo.c` | 异常终止与信号 |

编译运行（代码使用 `fork`/`wait`，**仅限 Linux / WSL / macOS**）：

```bash
cd operating-system/实验1-进程管理基础/code
make
./fork_basic
./zombie_demo
make clean
```

`运行说明与截图清单.md` 记录了每个程序的复现步骤与预期输出。

> 说明：这几个程序是 Linux 专用的系统调用演示，本机（Windows）无可用 Linux 环境，**未做实际编译执行**，只做了逐文件逻辑核对。在 Linux 上直接 `make` 即可。

## 数据库

- `1.修正我电脑上的mysql.md` — 本机 MySQL 环境问题排查
- `2.数据库考试.md`
- `3.数据库考试第三章.md`
- `4.数据库考试第4章和第5章.md`

## 说明

- 笔记中的图片统一放在 `attachments/`，链接已从 Obsidian 的 `![[...]]` 语法转换为标准 Markdown，可直接在 GitHub 上阅读。
- `operating-system/宏内核和微内核.md` 中的两张内核架构示意图来自 CSDN 博客（原图带 `CSDN@三境界` 水印），版权归原作者所有，此处仅作学习记录引用。
