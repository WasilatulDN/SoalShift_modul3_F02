#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8001

pthread_t tid[100];

int *stok;
int new_socket;
char buffer[1024] = {0};
void* cek (void* arg)
{
        if(strcmp(buffer,"jual")==0)
        {
                *stok = *stok + 1;
        }
        
        memset(buffer, 0, 1024);
}

void* cetak (void* arg)
{
    while(1)
    {
        printf("%d\n",*stok);
        sleep(5);
    }
    
}

int main(int argc, char const *argv[]) {
    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 0;

    int index=1;
    pthread_create(&(tid[0]),NULL,cetak,NULL);
        
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    
    while(1)
    {
        valread = read( new_socket , buffer, 1024);
        pthread_create(&(tid[index]),NULL,cek,NULL);
        pthread_join(tid[index],NULL);
        index++;
    }
    return 0;
}
