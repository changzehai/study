AUTOMAKE_OPTIONS= foreign
#程序名
bin_PROGRAMS= test
#程序包含源文件
test_SOURCES= test.c

#链接库文件名
# 动态库libXXX.so -> -lXXX
# 动态库XXX.a -> XXX.a 或者/aaa/bbb/XXX.a
test_LDADD= -lclntsh
#头文件指定
noinst_HEADERS=

#头文件路径指定
AM_CPPFLAGS = -I . \
              -I /usr/include/oracle/12.2/client64
#库文件路径指定
LIBS= -L /usr/lib \
      -L /usr/local/lib \
      -L /usr/lib/oracle/12.2/client64/lib
