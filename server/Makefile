# 指令编译器和选项
CC=gcc
CFLAGS=-Wall -std=gnu99
 
# 目标文件
TARGET=server
# 源文件
SRCS= command_resp.c command.c command_parse.c server.c
 
OBJS = $(SRCS:.c=.o)
 
$(TARGET):$(OBJS) 
	
	$(CC) -pthread -o $@ $^
 
clean:
	rm -rf $(TARGET) $(OBJS)
 
%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<
