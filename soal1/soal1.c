#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int bil[1000];
int hasil[1000];
pthread_t t_faktor[1000];
int status1 = 0;
void* faktor(void *pntr)
{
    while(status1 == 0)
    {

    }
    int cur = *((int *) pntr);
    int num;
    num = bil[cur];
    int i, res = 1;
    for(i=1;i<=num;i++)
    {
        res = res*i;
    }
    if(num<0)
    {
        hasil[cur]=-1;
    }
    else
    {
        hasil[cur]=res;
    }
    free(pntr);
}

void* insert(void *ptr) 
{ 
    status1=0;
    int n = *((int *) ptr);
    
    int i, key, j; 
    for (i = 1; i < n; i++) { 
        key = bil[i]; 
        j = i - 1; 

        while (j >= 0 && bil[j] > key) { 
            bil[j + 1] = bil[j]; 
            j = j - 1; 
        } 
        bil[j + 1] = key; 
    }
    free(ptr);
    status1=1; 
} 

int main(int argc, char** argv)
{
    int i;
    for(i=1;i<argc;i++)
    {
        bil[i-1]=atoi((char*)argv[i]);
    }
    pthread_t thread;
    int *arg = malloc(sizeof(arg));
    *arg = argc -1;
    pthread_create(&thread, NULL, insert, arg);
    pthread_join(thread,NULL);
    for(i=0;i<argc-1;i++)
    {
        int *angka = malloc(sizeof(angka));
        *angka = i;
        pthread_create(&t_faktor[i], NULL, faktor, angka);
        pthread_join(t_faktor[i],NULL);
    }
    for(i=0;i<argc-1;i++)
    {
        printf("%d! = ",bil[i]);
        if(hasil[i]!=-1)
        {
            printf("%d\n",hasil[i]);
        }
        else
        {
            printf("error\n");
        }
        
    }
    return 0;
}
