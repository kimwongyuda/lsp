#define MY_ID                   10
#define SHM_KEY                 (0x9000 + MY_ID)
#define SHM_MODE                (SHM_R | SHM_W | IPC_CREAT)

#define SEM1_SEM_KEY    (0x5000 + MY_ID)
#define SEM2_SEM_KEY    (0x6000 + MY_ID)
#define MUTEX_SEM_KEY   (0x7000 + MY_ID)

#define NLOOPS                  20

#define MAX_BUF                 2

#define SHM_SIZE        1024
