######################################
#
######################################
#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SOURCE  := mfs_shm_func.c \
           mfs_file_func.c \
           mfs_init.c

OBJS    := mfs_shm_func.o \
           mfs_file_func.o \
           mfs_init.o

#target you can change test to what you want
#目标文件名，输入任意你想要的执行文件名
TARGET  := mfsInit

#compile and lib parameter
#编译参数
CC      := gcc
LIBS    :=
LDFLAGS :=
DEFINES :=
INCLUDE := -I.
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H


#i think you should do anything here
#下面的基本上不需要做任何改动了
.PHONY : objs clean 


all : $(TARGET)

objs : $(OBJS)

clean :
	@rm -fr *.o
	@rm -fr $(TARGET)

$(TARGET) : $(OBJS)
	@$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
	@echo "done"
