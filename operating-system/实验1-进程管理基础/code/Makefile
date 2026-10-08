# 实验1 进程管理基础 —— 一键编译
CC      = gcc
CFLAGS  = -Wall -g
TARGETS = process_info process_lifecycle crash_demo fork_basic fork_wait \
          fork_nowait zombie_demo fork_multi

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
