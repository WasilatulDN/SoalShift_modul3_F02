#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int AkmalStat = 0;
int SirajStat = 100;
int changeAkmal = 1;
int changeSiraj = 1;
int pauseAkmal = 0;
int pauseSiraj = 0;
int tambahAkmal = 0;
int kurangSiraj = 0;
// char perintah[100];
pthread_t tid[2];

void* akmal(void *ptr){
	while(1){
            if(pauseAkmal==3)
            {
                changeAkmal=0;
                printf("\nAgmal Ayo Bangun disabled 10 s\n");
                sleep(10);
                pauseAkmal=0;
            }
            else if(changeAkmal==1)
            {
                if(tambahAkmal==1)
                {
                    
                    AkmalStat+=15;
                    pauseSiraj++;
                    tambahAkmal=0;
                }
            }
            else if(changeAkmal == 0)
            {
                changeAkmal=1;
                tambahAkmal=0;
            }

        if(AkmalStat>=100)
        {
            printf("\nAgmal Terbangun,mereka bangun pagi dan berolahraga\n");
            exit(EXIT_FAILURE);
        }
        
		
	}
}

void* siraj (void *ptr){
	while(1){
            if(pauseSiraj==3)
            {
                changeSiraj=0;
                printf("\nFitur Iraj Ayo Tidur disabled 10 s\n");
                sleep(10);
                pauseSiraj=0;
            }
            else if(changeSiraj==1)
            {
                if(kurangSiraj==1)
                {
                    
                    SirajStat-=20;
                    pauseAkmal++;
                    kurangSiraj=0;
                }
            }
            else if(changeSiraj == 0)
            {
                changeSiraj=1;
                kurangSiraj=0;
            }

        if(SirajStat<=0)
        {
            printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(EXIT_FAILURE);
        }
        
		
	}
}

void menu()
{
    printf("Fitur :\n");
    printf("1. All Status\n");
    printf("2. Agmal Ayo Bangun\n");
    printf("3. Iraj Ayo Tidur\n");
    printf("Masukkan pilihan > ");
}

int main()
{
    pthread_create(&(tid[0]),NULL,akmal,NULL);
    pthread_create(&(tid[1]),NULL,siraj,NULL);
    int pil;
    while(1)
    {
        menu();
        scanf("%d",&pil);
        if(pil==1)
        {
            printf("Agmal WakeUp_Status = %d\n",AkmalStat);
            printf("Iraj Spirit_Status = %d\n",SirajStat);
            // system("stty -icanon -echo; dd if=/dev/tty of=/dev/null bs=1 count=1 2>/dev/null; stty icanon echo");
        }
        else if(pil==2)
        {
            tambahAkmal=1;
            // system("stty -icanon -echo; dd if=/dev/tty of=/dev/null bs=1 count=1 2>/dev/null; stty icanon echo");
        
        }
        else if(pil==3)
        {
            kurangSiraj=1;
        }
        // system("clear");
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    return 0;
}
