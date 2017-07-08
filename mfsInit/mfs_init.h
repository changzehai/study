#ifndef __MFS_INIT_H_
#define __MFS_INIT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


extern int mfs_open_table_init();
extern int mfs_file_create();
extern int mfs_file_open(int *fd, int fno, int open_flag);
void *mfs_getrec(int *fd);
int mfs_file_save(int fd);
int mfs_file_read(int fd);

extern int mfs_shm_table_init();
extern int mfs_shmget(int fno, int shm_size);
extern void *mfs_shmat(int fno);

#endif

