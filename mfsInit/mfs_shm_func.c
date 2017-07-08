#include "mfs_init.h"

typedef struct _SHM_ {
    int fno;
    int shmid;
} SHM;

typedef struct _SHM_TABLE_ {
    SHM shm[10240];
    int shm_cnt;
} SHM_TABLE;

static SHM_TABLE shm_table;

int mfs_shm_table_init()
{
    memset(shm_table.shm, -1, sizeof(shm_table.shm));
    shm_table.shm_cnt = 0;

    return 0;
}

int mfs_shm_table_in(int fno, int shmid)
{
    shm_table.shm[shm_table.shm_cnt].fno = fno;
    shm_table.shm[shm_table.shm_cnt].shmid = shmid;
    shm_table.shm_cnt++;
     
    return 0;
}

int mfs_fno_to_shmid(int fno)
{
    int i;

    for (i = 0; i < shm_table.shm_cnt; i++) {

        if (shm_table.shm[i].fno == fno) {
            return shm_table.shm[i].shmid;
        }

    } 

    return -1;
}

int mfs_shmget(int fno, int shm_size)
{

    int shmid;


    if ((shmid = shmget(IPC_PRIVATE, shm_size, 0666)) < 0) {
        printf("shmget fno[%d] shmid[%d]error!\n", fno, shmid);
        return -1;
    }

    if (-1 == mfs_shm_table_in(fno, shmid)) {
        printf("mfs_shm_table_in fno[%d] shmid[%d]\n", fno, shmid);
        return -1;
    }    


    return 0;
}


void *mfs_shmat(int fno)
{
    int shmid;

    if (-1 == (shmid = mfs_fno_to_shmid(fno))) {
        printf("mfs_fno_to_shmid error fno[%d]\n", fno);
        return NULL;
    }

    return shmat(shmid, NULL, 0666);
}

