#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[2], tid2[2], tid3[2], tid4[2];
int status;
void *thread1(void *arg)
{
        status = 0;
        char buffer3[100], buffer4[100];
        pthread_t id = pthread_self();
        if(pthread_equal(id,tid[0]))
        {
                snprintf(buffer3, sizeof(buffer3), "ps -aux | head -10 > /home/test/Documents/FolderProses1/SimpanProses1.txt");
                system(buffer3);
        }
        else if(pthread_equal(id,tid[1]))
        {
                snprintf(buffer4, sizeof(buffer4), "ps -aux | head -10 > /home/test/Documents/FolderProses2/SimpanProses2.txt");
                system(buffer4);

        }
        status = 1;
        return NULL;
}


void *thread2(void *arg)
{
        while(status!=1)
        {

        }
        char buffer[100], buffer2[100];
        pthread_t id2 = pthread_self();
        if(pthread_equal(id2,tid2[0]))
        {
                snprintf(buffer, sizeof(buffer), "zip KompresProses1.zip /home/test/Documents/FolderProses1/SimpanProses1.txt");
                system(buffer);
        }
        else if(pthread_equal(id2,tid2[1]))
        {
                snprintf(buffer2, sizeof(buffer2), "zip KompresProses2.zip /home/test/Documents/FolderProses2/SimpanProses2.txt");
                system(buffer2);
        }
        status=2;
        return NULL;
}

void *thread3(void *arg)
{
        while(status!=2)
        {

        }
        char buffer[100], buffer2[100];
        char buf[100], buf2[100];
        pthread_t id3 = pthread_self();
        if(pthread_equal(id3,tid3[0]))
        {
                snprintf(buf, sizeof(buf), "rm /home/test/Documents/FolderProses1/SimpanProses1.txt");
                system(buf);
        }
        else if(pthread_equal(id3,tid3[1]))
        {
                snprintf(buf2, sizeof(buf2), "rm /home/test/Documents/FolderProses2/SimpanProses2.txt");
                system(buf2);
        }
        status=2;
        return NULL;
}

void *thread4(void *arg)
{
        while(status!=3)
        {

        }
        sleep(15);
        char buff[100], buff2[100];
        pthread_t id4 = pthread_self();
        if(pthread_equal(id4,tid4[0]))
        {
                snprintf(buff, sizeof(buff), "unzip KompresProses1.zip");
                system(buff);
        }
        else if(pthread_equal(id4,tid4[1]))
        {
                snprintf(buff2, sizeof(buff2), "unzip KompresProses2.zip");
                system(buff2);
        }
        return NULL;
}
int main(void)
{
        int i=0, j=0, k=0, l=0;
        while(i<2) // loop sejumlah thread
        {
                pthread_create(&(tid[i]),NULL,&thread1,NULL); //membuat thread
                i++;
        }
        while(j<2) // loop sejumlah thread
        {
                pthread_create(&(tid2[j]),NULL,&thread2,NULL); //membuat thread
                j++;
        }
        while(k<2) // loop sejumlah thread
        {
                pthread_create(&(tid3[k]),NULL,&thread3,NULL); //membuat thread
                k++;
        }
        while(l<2) // loop sejumlah thread
        {
                pthread_create(&(tid4[l]),NULL,&thread4,NULL); //membuat thread
                l++;
        }


        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_join(tid2[0],NULL);
        pthread_join(tid2[1],NULL);
        pthread_join(tid3[0],NULL);
        pthread_join(tid3[1],NULL);

        printf("Menunggu 15 detik untuk mengekstrak kembali\n");
        pthread_join(tid4[0],NULL);
        pthread_join(tid4[1],NULL);

        exit(0);
        return 0;
}
