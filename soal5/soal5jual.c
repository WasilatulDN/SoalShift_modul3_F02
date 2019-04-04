#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include<stdlib.h>
#include<termios.h>
#include<pthread.h>

static struct termios old, new;
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      new.c_lflag |= ECHO; /* set echo mode */
  } else {
      new.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

int *jumMakan;
pthread_t tid[2];

void* awal (void* arg)
{
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumMakan = shmat(shmid, NULL, 0);
  
    *jumMakan = 0;

}

void* menutoko (void* arg)
{
    while(1)
    {
        system("clear");
        printf("Shop\n");
        printf("Food Stock : %d\n",*jumMakan);
        printf("Choice : \n");
        printf("1. Restock\n");
        printf("2. Exit\n");
        sleep(1);
    }

}
void main()
{
    pthread_create(&(tid[0]),NULL,awal,NULL);
    pthread_create(&(tid[1]),NULL,menutoko,NULL);
    char pil;
    while(1)
    {
        pil=getch();
        if(pil=='1')
        {
            *jumMakan = *jumMakan + 1;
        }
        else if(pil=='2')
        {
            break;
        }
    }
}
