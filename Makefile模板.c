#########################################################
# FNAME		: Makefile万能模板                          #
# Version	:                                           #
# FUNCTION	:                                           #
# CRATE		: 2017-07-10 changzehai                     #
# Copyright (C) 2017 changzehai. All Rights Reserved.   #
#########################################################


#源文件类型
# The valid suffixes are among of .c, .C, .cc, .cpp, .CPP, .c++, .cp, or .cxx.
# SRCEXTS   := .c      # C program
# SRCEXTS   := .cpp    # C++ program
# SRCEXTS   := .c .cpp # C/C++ program
SRCEXTS   := .c

#source file
#源文件
HDRS	:= mfs_init.h

SRCS	:= mfs_shm_func.c \
           mfs_file_func.c \
           mfs_init.c

OBJS	:= mfs_shm_func.o \
           mfs_file_func.o \
           mfs_init.o

#目标文件名，输入任意你想要的执行文件名
PROGRAM  := mfsInit

#使用到的头文件和库文件路径指定
INCLUDE := -I. \

LIBS    := 
	      


#变量定义
CC      		= cc
LD 				= cc
MAKE			= make
MAKEFILE		= Makefile
TARGET			= all clean
TARGET_LINUX	= $(TARGET:=_linux)
HOST_LINUX		= ./linux


#compile and lib parameter
#编译参数
LDFLAGS := 
DEFINES :=
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H


#下面的基本上不需要做任何改动了
default		: all

$(OBJS)		:   $(HDRS) $(SRCS)
				@if [ ! -d $(HOST_LINUX) ]; then \
				echo "Make directory $(HOST_LINUX)"; mkdir -p $(HOST_LINUX); fi
ifeq ($(strip $(SRCEXTS)), .c)  # C file
				@echo "Compiling -c $(INCLUDE) $(@F:.o=.c) -o $@"
				@($(CC) $(CFLAGS) $(INCLUDE) -c $(@F:.o=.c) -o $@)
else                            # C++ file
				@echo "Compiling -c $(INCLUDE) $(@F:.o=.cpp) -o $@"
				@($(CC) $(CXXFLAGS) $(INCLUDE) -c $(@F:.o=.cpp) -o $@)
endif

$(PROGRAM)	: $(OBJS)
				@if [ ! -d $(HOST_LINUX) ]; then \
				echo "Make directory $(HOST_LINUX)"; mkdir -p $(HOST_LINUX); fi
				@echo "Linking $(PROGRAM)"
				@($(LD) $(LDFLAGS) $(LIBS) $(OBJS) -o $@)
				@echo "done"


all_	: $(PROGRAM)

clean_:;
		@rm -f $(OBJS) $(PROGRAM)

$(TARGET):
			@(echo "Making on `uname -s` ... $(@F)"; \
			$(MAKE) -f $(MAKEFILE) $(@F:=_linux))

$(TARGET_LINUX):
			echo $(OBJS)
			@($(MAKE) -f $(MAKEFILE) \
			"OBJS=`for obj in $(OBJS); do echo -n $(HOST_LINUX)/$${obj} " "; done` " \
			"PROGRAM=$(HOST_LINUX)/$(PROGRAM)" \
			$(@F:linux=))
