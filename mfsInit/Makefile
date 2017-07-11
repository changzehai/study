######################################
#
######################################
#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
HDRS	:= mfs_init.h

SRCS	:= mfs_shm_func.c \
           mfs_file_func.c \
           mfs_init.c

OBJS	:= mfs_shm_func.o \
           mfs_file_func.o \
           mfs_init.o

INCLUDE := -I. \

LIBS    := 
		  
	    
	      

#target you can change test to what you want
#目标文件名，输入任意你想要的执行文件名
PROGRAM  := mfsInit

#compile and lib parameter
#编译参数
CC      := cc
LD 		:= cc
MAKE	:= make
MAKEFILE:= Makefile
LDFLAGS := 
DEFINES :=
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H


#i think you should do anything here
#下面的基本上不需要做任何改动了
TARGET			= all clean
TARGET_LINUX	= $(TARGET:=_linux)
HOST_LINUX		= ./linux

default		: all

$(OBJS)		:   $(HDRS) $(SRCS)
				@if [ ! -d $(HOST_LINUX) ]; then \
				echo "Make directory $(HOST_LINUX)"; mkdir -p $(HOST_LINUX); fi
				@echo "Compiling -c $(INCLUDE) $(@F:.o=.c) -o $@"
				@($(CC) $(CFLAGS) $(INCLUDE) -c $(@F:.o=.c) -o $@)

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
