######################################
#
#######################################
#源文件类型
# The valid suffixes are among of .c, .C, .cc, .cpp, .CPP, .c++, .cp, or .cxx.
# SRCEXTS   := .c      # C program
# SRCEXTS   := .cpp    # C++ program
# SRCEXTS   := .c .cpp # C/C++ program
SRCEXTS   := .c


#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
#SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
#OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

#对象文件手动指定
OBJS	:= test.o


#源文件手动指定
SOURCE	:= test.c

  
#target you can change test to what you want
#目标文件名，输入任意你想要的执行文件名
TARGET  := test
  
#compile and lib parameter
#编译器指定
CC      := gcc
CXX		:= g++

#头文件手动指定
INCLUDE := -I.\
           -I /usr/include/oracle/12.2/client64


#库文件手动指定
LIBS    := /usr/lib/oracle/12.2/client64/lib/libclntsh.so


DEFINES :=

#C编译器编译选项
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)

#C++编译器编译选项
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H

#库链接选项
LDFLAGS :=
  
#下面的基本上不需要做任何改动了
.PHONY : all objs clean cleanall rebuild
  
all : $(TARGET)
  
objs : $(OBJS)
                
clean :
	rm -fr *.o $(TARGET)
    
cleanall: clean all

rebuild: clean all

#程序编译链接
$(TARGET) : $(OBJS)
ifeq ($(strip $(SRCEXTS)), .c)  # C file
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
else                            # C++ file
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
endif
