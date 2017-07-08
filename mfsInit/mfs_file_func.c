#include "mfs_init.h"

typedef struct _OPEN_ {
    int fno;
    int fd;

} OPEN;

typedef struct _OPEN_TABLE_ {
    OPEN open[10240];
    int  open_cnt;

} OPEN_TABLE;

static OPEN_TABLE open_table;

int mfs_open_table_init()
{
    memset(open_table.open, -1, sizeof(open_table.open));
    open_table.open_cnt = 0;

    return 0;
}

int mfs_open_table_in(int fno, int fd)
{
    open_table.open[open_table.open_cnt].fno = fno;
    open_table.open[open_table.open_cnt].fd = fd;
    open_table.open_cnt++;  

    return 0;
}


int mfs_fd_to_fno(int fd)
{
    int i;

    for (i = 0; i < open_table.open_cnt; i++) {
        if (open_table.open[i].fd == fd) {

            return open_table.open[i].fno;
        }


    }

    return -1;

}


int mfs_file_open(int *fd, int fno, int open_flag)
{
		FILE *fp = NULL;
		char buf[1024];
		char cmd[1024];
        char fname[50];
        int  fnum;

		if (NULL == (fp = fopen("mpf_mfs_directfile.txt", "r"))) {
				printf("fopen mpf_mfs_directfile.txt error!\n");
				return -1;
		}


		while (fgets(buf, 1024, fp)) {

				if (2 != sscanf(buf, "%s %d", fname, &fnum)) { 
                        if (NULL != strstr(fname, "#")) {
                            continue;
                        }
						printf("文件定义有误(%s)\n", buf);
						return -1;   
				}
               
                if (fno == fnum) {
                    sprintf(cmd, "/home/oracle/file/savefile/%s.sav", fname);
                    *fd = open(cmd, open_flag);
                    mfs_open_table_in(fno, *fd);

                    return *fd;
                }
    

		}
        
        fclose(fp);

        printf("指定文件不存在fno[%d]\n", fno);

        return -1;

}

int mfs_file_create()
{
   FILE *fp = NULL;
   char rec[8][50];
   char buf[1024];
   char cmd[1024];
   int  rec_size;
   int  rec_cnt;
   int  fno;

   if (NULL == (fp = fopen("mpf_mfs_directfile.txt", "r"))) {
       printf("fopen mpf_mfs_directfile.txt error!\n");
       return -1;
   }
   

   while (fgets(buf, 1024, fp)) {
   
       if (8 != sscanf(buf, "%s %s %s %s %s %s %s %s", 
                       &rec[0][0], &rec[1][0], &rec[2][0], &rec[3][0],
                       &rec[4][0], &rec[5][0], &rec[6][0], &rec[7][0])) {
           printf("文件定义有误(%s)\n", buf);
           return -1;   
       }


       if (!strcmp(&rec[2][0], "M")) {
           sprintf(cmd, "dd if=/dev/zero of=/home/oracle/file/savefile/%s.sav bs=%s count=%s",
                   &rec[0][0], &rec[5][0], &rec[6][0]);
           system(cmd);
           
           fno = atoi(&rec[1][0]);
           rec_size = atoi(&rec[5][0]);
           rec_cnt = atoi(&rec[6][0]); 
        
           if (-1 == mfs_shmget(fno, rec_size * rec_cnt)) {
               printf("mfs_shmget fno[%d] error", fno);
               return -1; 
           }
          

       }


   }

   fclose(fp);

    return 0;
}


void *mfs_getrec(int *fd)
{
 
    int fno;

    if (-1 == (fno = mfs_fd_to_fno(*fd))) {
        printf("mfs_fd_to_fno error\n");
        
        return NULL;
    }

    return mfs_shmat(fno); 

}

int mfs_file_save(int fd)
{
    void *rec = NULL;   
    ssize_t wsize;  
  
    rec = mfs_getrec(&fd); 
 
    if ((wsize = write(fd, rec, 1024)) < 0) {
        printf("write error\n");
        return -1;
    }

    return wsize;
}

int mfs_file_read(int fd)
{
    char buf[1024];
    ssize_t rsize; 

    memset(buf, 0x00, sizeof(buf));    

    if ((rsize = read(fd, buf, 1024)) < 0) {
        printf("read error!\n");
        return -1;
    }
    printf("文件内容: %s\n", buf);
    
    return rsize;
}
