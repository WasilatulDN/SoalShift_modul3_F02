#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[4];
int jeda=0;
void *simpan(void *arg)
{
        printf("Membuat file SimpanProses1.txt\n");
        system("ps -aux | head -10 > /home/ihdiannaja2911/Documents/FolderProses1/SimpanProses1.txt");
        printf("Membuat file SimpanProses2.txt\n");
        system("ps -aux | head -10 > /home/ihdiannaja2911/Documents/FolderProses2/SimpanProses2.txt");
        jeda = 1;
        return NULL;
}

void *kompres(void *arg)
{
        while(jeda!=1)
        {

        }
        printf("Membuat KompresProses1.zip\n");
        system("zip -j /home/ihdiannaja2911/Documents/FolderProses1/KompresProses1.zip /home/ihdiannaja2911/Documents/FolderProses1/SimpanProses1.txt");
        printf("Membuat KompresProses2.zip\n");
        system("zip -j /home/ihdiannaja2911/Documents/FolderProses2/KompresProses2.zip /home/ihdiannaja2911/Documents/FolderProses2/SimpanProses2.txt");
        
        jeda=2;
        return NULL;
}

void *hapus(void *arg)
{
        while(jeda!=2)
        {

        }
        printf("Delete file SimpanProses1.txt\n");
        system("rm /home/ihdiannaja2911/Documents/FolderProses1/SimpanProses1.txt");
        printf("Delete file SimpanProses2.txt\n");
        system("rm /home/ihdiannaja2911/Documents/FolderProses2/SimpanProses2.txt");
        
        jeda=3;
        return NULL;
}

void *ekstrak(void *arg)
{
        while(jeda!=3)
        {

        }
        printf("Menunggu 15 detik untuk mengekstrak kembali\n");
        sleep(15);
        
        system("unzip /home/ihdiannaja2911/Documents/FolderProses1/KompresProses1.zip -d /home/ihdiannaja2911/Documents/FolderProses1/");
        system("unzip /home/ihdiannaja2911/Documents/FolderProses2/KompresProses2.zip -d /home/ihdiannaja2911/Documents/FolderProses2/");
        
        return NULL;
}

int main(void)
{
        pthread_create(&(tid[0]),NULL,simpan,NULL);
        pthread_create(&(tid[1]),NULL,kompres,NULL);
        pthread_create(&(tid[2]),NULL,hapus,NULL);
        pthread_create(&(tid[3]),NULL,ekstrak,NULL);

        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_join(tid[2],NULL);
        pthread_join(tid[3],NULL);

        exit(0);
        return 0;
}
