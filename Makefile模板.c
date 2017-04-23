1、生成可执行文件的makefile
######################################
#
######################################
#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

#target you can change test to what you want
#目标文件名，输入任意你想要的执行文件名
TARGET  := test

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
.PHONY : everything objs clean veryclean rebuild

everything : $(TARGET)

all : $(TARGET)

objs : $(OBJS)

rebuild: veryclean everything

clean :
    rm -fr *.so
    rm -fr *.o

veryclean : clean
    rm -fr $(TARGET)

$(TARGET) : $(OBJS)
    $(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)




2、生成静态链接库的makefile

######################################
#
#
######################################

#target you can change test to what you want
#共享库文件名，lib*.a
TARGET  := libtest.a

#compile and lib parameter
#编译参数
CC      := gcc
AR      = ar
RANLIB  = ranlib
LIBS    :=
LDFLAGS :=
DEFINES :=
INCLUDE := -I.
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H

#i think you should do anything here
#下面的基本上不需要做任何改动了

#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

.PHONY : everything objs clean veryclean rebuild

everything : $(TARGET)

all : $(TARGET)

objs : $(OBJS)

rebuild: veryclean everything

clean :
    rm -fr *.o

veryclean : clean
    rm -fr $(TARGET)

$(TARGET) : $(OBJS)
    $(AR) cru $(TARGET) $(OBJS)
    $(RANLIB) $(TARGET)


3、生成动态链接库的makefile
######################################
#
#
######################################

#target you can change test to what you want
#共享库文件名，lib*.so
TARGET  := libtest.so

#compile and lib parameter
#编译参数
CC      := gcc
LIBS    :=
LDFLAGS :=
DEFINES :=
INCLUDE := -I.
CFLAGS  := -g -Wall -O3 $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
SHARE   := -fPIC -shared -o

#i think you should do anything here
#下面的基本上不需要做任何改动了

#source file
#源文件，自动找所有.c和.cpp文件，并将目标定义为同名.o文件
SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

.PHONY : everything objs clean veryclean rebuild

everything : $(TARGET)

all : $(TARGET)

objs : $(OBJS)

rebuild: veryclean everything

clean :
    rm -fr *.o

veryclean : clean
    rm -fr $(TARGET)

$(TARGET) : $(OBJS)
    $(CC) $(CXXFLAGS) $(SHARE) $@ $(OBJS) $(LDFLAGS) $(LIBS)
