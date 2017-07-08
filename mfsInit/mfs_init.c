/**************************************************************
 *		FNAME		: mfs_init.c
 *		Version     :
 *      Function    : 内存文件实现
 *      Create      : 2017-07-08 changzehai
 *      Copyright (C) 2017 changzehai. All Rights Reserved.
 **************************************************************/
#include "mfs_init.h"


int main()
{
    int fd;
    char *rec = NULL; 

 
    /* 初始化 */
    mfs_open_table_init();
    mfs_shm_table_init();  
   
    /* 读取定义文件创建空白文件 */
    if (-1 == mfs_file_create()) {
        printf("mfs_file_create 失败\n");
        return -1;
    }
    printf("file cretae done!\n");

    /* 打开文件获取文件描述符 */
    if (-1 == mfs_file_open(&fd, 1, 0666)){
        printf("mfs_file_open error\n");
        return -1;
    }

    /* 根据文件描述符获得该文件的内存首地址 */
    if (NULL == (rec = mfs_getrec(&fd))) {
        printf("mfs_getrec error\n");
        return -1;
    }

    /* 向内存文件写内容，并把内容同步到硬盘文件中 */
    strcpy(rec, "雷佳群是常泽海一生最爱的小甜心小公举!\n");
    if (-1 == mfs_file_save(fd)) {
        printf("mfs_file_save error"); 
        return -1;
    }
    printf("file save done!\n");
    close(fd);

    /* 确认内容是否写入到硬盘文件中 */
    if (-1 == mfs_file_open(&fd, 1, 0666)){
        printf("mfs_file_open error\n");
        return -1;
    }
    
    if (-1 == mfs_file_read(fd)) {
        printf("mfs_file_read error\n");
        return -1;
    }
    close(fd);

    printf("mfsInit done\n");

    return 0;
}
