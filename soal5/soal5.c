#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<termios.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>

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

char nama[100];
int statusLapar=200;
int statusBersih=100;
int statusSehat=300;
int detik=20;
int detikSehat=10;
int detikBersih=30;
int detikLapar=10;
int siapMandi=0;
int jeda=0;
pthread_t tid[7];
char pil;
int makanan=0;
void* menu(void*);

void* kelaparan (void *ptr)
{
    while(1)
    {
        // sleep(10);
        while(jeda!=0)
        {

        }
        sleep(1);
        if(detikLapar==1)
        {
            detikLapar=10;
            statusLapar-=5;            
        }
        else detikLapar-=1;
        if(jeda==0)
        {
            

            if(statusLapar<=0)
            {
                printf("Monster mati karena kelaparan\n");
                exit(EXIT_FAILURE);
            }

        }
        
        
    }
}

void* kebersihan (void *ptr)
{
    while(1)
    {
        // sleep(30);
        while(jeda!=0)
        {
            
        }
        sleep(1);
        if(detikBersih==1)
        {
            detikBersih=30;
            statusBersih-=10;
        }
        else detikBersih-=1;
        if(jeda==0)
        {
            
            if(statusBersih<=0)
            {
                printf("Monster mati karena terkena terlalu kotor\n");
                exit(EXIT_FAILURE);
            }
        }
        
    }
}

void* kesehatan (void *ptr)
{
    while(1)
    {
        while(jeda!=0)
        {
            
        }
        sleep(1);
        if(detikSehat==1)
        {
            detikSehat=10;
            statusSehat+=5;
        }
        else detikSehat-=1;
        if(jeda==0)
        {
            

            if(statusSehat<=0)
            {
                printf("Monster mati karena sakit-sakitan\n");
                exit(EXIT_FAILURE);
            }

        }
        
    }
}

void* countdown (void *ptr)
{
    while(1)
    {
        while(jeda!=0)
        {
            
        }
        if(siapMandi==0)
        {
            sleep(1);
            if(detik==0)
            {
                detik=20;
                siapMandi=1;
            }
            else detik-=1;
        }
        
    }
}
int *jumMakan;
void* toko (void* arg){
    key_t key = 1234;


    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumMakan = shmat(shmid, NULL, 0);

    *jumMakan = 0;
}
void* menu(void *arg)
{
    while(1){
    while(jeda!=0)
    {

    }
    system("clear");
    printf("Standby Mode\n");
    printf("nama : %s\n",nama);
    printf("Health : %d\n",statusSehat);
    printf("Hunger : %d\n",statusLapar);
    printf("Hygiene : %d\n",statusBersih);
    printf("Food Left : %d\n",makanan);
    if(siapMandi==0)
    printf("Bath will be ready in %d\n",detik);
    else printf("Bath is ready\n");
    printf("Choice :\n");
    printf("1. Eat\n");
    printf("2. Bath\n");
    printf("3. Battle\n");
    printf("4. Shop\n");
    printf("5. Exit\n");
    sleep(1);
    }
}

void* menu2(void *arg)
{
    while(1){
    while(jeda!=2)
    {

    }
    system("clear");
    printf("Shop Mode\n");
    printf("Shop food stock : %d\n",*jumMakan);
    printf("Your food stock : %d\n",makanan);
    printf("Choices\n");
    printf("1. Buy\n");
    printf("2. Back\n");
    sleep(1);
    }
}

int main()
{
    char c;
    int i;
    printf("Beri nama monstermu > ");
    c=getchar();
    while(c!='\n')
    {
        nama[i]=c;
        c=getchar();
        i++;
    }
    pthread_create(&(tid[0]),NULL,kelaparan,NULL);
    pthread_create(&(tid[1]),NULL,kebersihan,NULL);
    pthread_create(&(tid[2]),NULL,kesehatan,NULL);
    pthread_create(&(tid[3]),NULL,countdown,NULL);
    pthread_create(&(tid[4]),NULL,menu,NULL);
    pthread_create(&(tid[5]),NULL,toko,NULL);
    pthread_create(&(tid[6]),NULL,menu2,NULL);
    // scanf("%s",nama);
    // printf("%s",nama);
    // c=getch();
    while(1)
    {
        // menu();
        pil=getch();
        if(pil=='1')
        {
            if(makanan>0)
            {
                statusLapar+=15;
                makanan--;
                if(statusLapar>200)
            {
                statusLapar=200;
            }
            }
            
        }
        else if(pil=='2')
        {
            if(siapMandi==1)
            {
                statusBersih+=30;
                if(statusBersih>100)
                {
                    statusBersih=100;
                }
                siapMandi=0;
            }
            
        }
        else if(pil=='3')
        {
            int statusLawan=100;
            jeda=1;
            while(1)
            {
                system("clear");
                printf("Battle Mode\n");
                printf("Monster's Health : %d\n",statusSehat);
                printf("Enemy's Health : %d\n",statusLawan);
                printf("Choices\n");
                printf("1. Attack\n");
                printf("2. Run\n");
                char charac;
                charac = getch();
                if(charac=='1')
                {
                    if(statusSehat>0)
                    {
                        statusSehat-=20;
                        if(statusLawan>0)
                        {
                            statusLawan-=20;
                        }
                    }  
                    if(statusSehat<0)
                    {
                        statusSehat=0;
                        jeda=0;
                        break;
                    }
                    else if(statusLawan<0)
                    {
                        statusLawan=0;
                    }
                }
                else if(charac=='2')
                {
                    jeda=0;
                    break;
                }
                

            }
        }
        else if(pil=='4')
        {
            jeda=2;
            char charac;
            while(1)
            {
                charac = getch();
                if(charac=='1')
                {
                    if(*jumMakan > 0)
                    {
                        *jumMakan = *jumMakan - 1;
                        makanan++;
                    }
                    
                }
                else if(charac=='2')
                {
                    jeda=0;
                    break;
                }
                

            }
        }
        else if(pil=='5')
        {
            system("clear");
            printf("Sampai jumpa!!\n");
            exit(EXIT_FAILURE);
            break;
        }    
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_join(tid[4],NULL);
    pthread_join(tid[5],NULL);
    pthread_join(tid[6],NULL);
    return 0;
}
