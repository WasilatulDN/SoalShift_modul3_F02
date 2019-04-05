# SoalShift_modul3_F02
Pertanyaan, Jawaban dan Penjelasan Praktikum Modul 2 Sistem Operasi 2019.

Oleh :
* Wasilatul Dewi Ningrum (05111740000004)
* Ihdiannaja (05111740007005)

## Soal 1
#### Pertanyaan :
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120
#### Jawaban :
```
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int bil[1000];
int hasil[1000];
pthread_t t_faktor[1000];
int status1 = 0;
```
* Deklarasi array bil dan hasil bertipe integer
* Deklarasi variabel t_faktor bertipe pthread
* Deklarasi variabel status1 bertipe integer

```
void* faktor(void *pntr)
{
    while(status1 == 0)
    {

    }
```
* Membuat fungsi faktor dengan parameter void untuk menghitung hasil faktorial
* ketika statusnya = 0 dengan maka tidak melakukan apapun
```
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
```
* Deklarasi variabel cur, num, dan i
* Melakukan perulangan ketika bilangan num (bilangan yang difaktorkan) kurang dari samadengan 1
* Jika memenuhi persyaratan perulangan tersebut, maka bilangan num dikalikan dengan i dan ditampung dalam variabel res
* Melakukan perulangan ketika bilangan num (bilangan yang difaktorkan) kurang dari 0
* Jika memenuhi persyaratan perulangan tersebut, maka variabel hasil[cur] disamadengankan -1
* Jika tidak memenuhi persyaratan perulangan tersebut, maka variabel hasil[cur] disamadengankan res (hasil perkalian di atas)
* Setelah selesai, maka memori pointer dikosongkan
```
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
```
* Membuat fungsi insert untuk melakukan sorting dengan cara insertion sort
* Deklarasi variabel status1 = 0
* Deklarasi variabel i,key, dan j bertipe integer
* Melakukan perulangan 
* Memindahkan element bill[0..i-1], yang lebih besar dari key, ke satu posisi di depan posisi sekarang  
* Setelah fungsi selesai dijalankan, kosongkan memori 
* Mengubah status1 = 1
```
int main(int argc, char** argv)
{
    int i;
    for(i=1;i<argc;i++)
    {
        bil[i-1]=atoi((char*)argv[i]);
    }
```
* Membuat fungsi main dengan parameter argc (argumen untuk menghitung jumah perintah) dan argv(argumen untuk menampung perintah) 
* Deklarasi variabel i bertipe integer
* Karena argv bertipe char, maka bil[i-1] (angka yang akan difaktorialkan) diubah menjadi tipe integer dengan perintah `atoi((char*)argv[i])`
```
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
```
* Deklarasi * arg bertipe int yang mengalokasikan memori sebesar arg
* Deklarasi * arg = argc-1
* Membuat thread 
* Membuat join thread
```
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
```
* Membuat perulangan sebanyak jumlah bilangan yang akan difaktorkan
* Jika memenuhi maka printf "bilangan = "
* Jika hasil tiap bilangan yang difaktorkan tidak samadengan -1, maka printf hasilnya
* Jika hasil bilangan yang difaktorkan = -1, maka printf "error"

## Soal 2
#### Pertanyaan
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
Terdapat 2 server: server penjual dan server pembeli
1 server hanya bisa terkoneksi dengan 1 client
Server penjual dan server pembeli memiliki stok barang yang selalu sama
Client yang terkoneksi ke server penjual hanya bisa menambah stok
Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
Server penjual akan mencetak stok saat ini setiap 5 detik sekali
Menggunakan thread, socket, shared memory
#### Jawaban :
##### Server Jual
```
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
```
* Library untuk membuat socket
* Define port server jual = 8001
```
void* cek (void* arg)
{
        if(strcmp(buffer,"jual")==0)
        {
                *stok = *stok + 1;
        }
        
        memset(buffer, 0, 1024);
}
```
* Membuat fungsi cek dengan parameter arg
* Melakukan pengecekan apakah input buffer = "jual"
* Jika benar, maka stok bertambah 1
* Jika selesai, maka mengosongkan memory buffer
```
void* cetak (void* arg)
{
    while(1)
    {
        printf("%d\n",*stok);
        sleep(5);
    }
    
}
```
* Membuat fungsi cetak dengan parameter arg
* Melakukan perulangan while true
* Printf stoknya
* Mencetak stok setiap 5 detik sekali
```
int main(int argc, char const *argv[]) {
    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
```
* Fungsi untuk socket
```
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 0;
```
* Fungsi untuk shared memory
```
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
```
* Fungsi untuk socket
``` 
    while(1)
    {
        valread = read( new_socket , buffer, 1024);
        pthread_create(&(tid[index]),NULL,cek,NULL);
        pthread_join(tid[index],NULL);
        index++;
    }
    return 0;
}
```
* Melakukan while true
* Jika memenuhi, maka membaca input dari buffer dan menjalankan fungsi read()
* Setiap membaca input, maka membuat thread
* Join thread
* Increment index

##### Client Jual :
```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8001
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    char string[100];
```
* Fungsi untuk Socket Client
```
    while(1)
    {
        memset(string, 0, 100);
        scanf("%s",string);
        send(sock , string , strlen(string) , 0 );
    }
    
    return 0;
}
```
* Melakukan while true
* Mengosongkan memory
* Menscan atau memasukkan input yang disimpan dalam variabel string
* Input yang dimasukkan dikirim ke server jual

##### Server Beli :
```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8000

pthread_t tid[100];
int new_socket;
int *stok;
char buffer[1024] = {0};
```
* Deklarasi library untuk socket server
* Define port = 8000
```
void* cek (void* arg)
{
    char *pesangagal = "transaksi gagal";
    char *pesansukses = "transaksi berhasil";
    char *pesangagal1 = "perintah salah";
    if(strcmp(buffer,"beli")==0)
    {
        if(*stok > 0)
        {
            *stok = *stok - 1;
            printf("%s\n",pesansukses);
            send(new_socket , pesansukses , strlen(pesansukses) , 0 );
        }
        else
        {
            printf("%s\n",pesangagal);
            send(new_socket , pesangagal , strlen(pesangagal) , 0 );
        }
    }
    else
    {
        printf("%s\n",pesangagal1);
        send(new_socket , pesangagal1 , strlen(pesangagal1) , 0 );
    }
        
    memset(buffer, 0, 1024);
}
```
* Membuat fungsi cek dengan parameter arg
* Deklarasi * pesangagal = "transaksi gagal"
* Deklarasi * pesansukses = "transaksi berhasil"
* Deklarasi * pesangagal1 = "perintah salah"
* Memandingkan apakah input dari buffer = "beli"
* Jika benar dan stok tersedia, maka stok bertambah 1
* Printf pesansukses
* Mengirim pesansukses meuju client beli
* Jika benar namun stok tidak tersedia, maka tampilkan pesan gagal
* Jika salah, maka printf pesangagal1
* Mengirim pesangagal1 menuju client beli
* Mengosongkan memory
```
int main(int argc, char const *argv[]) {
    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
```
* Untuk socket
```
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 0;
```
* Fungsi untuk shared memory
```
    int index=1;

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
```
* Fungsi untuk socket
``` 
    while(1)
    {
        valread = read( new_socket , buffer, 1024);
        pthread_create(&(tid[index]),NULL,cek,NULL);
        pthread_join(tid[index],NULL);
        index++;
    }
    return 0;
}
```
* Melakukan while true
* Membaca input dari client beli
* Setiap cient beli menginput, maka membuat thread
* Melakukan thread join
* Increment index

##### Client Beli :
```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8000
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    char string[100];
```
* Fungsi untuk socket client
* Define port client beli = 800
```
    while(1)
    {
        memset(string, 0, 100);
        scanf("%s",string);
        send(sock , string , strlen(string) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer, 0, 1024);
    }
    
    return 0;
}
```
* Melakukan while true
* Kosongkan memory
* Scanf input client beli
* Mengirimkan input menuju server beli
* Membaca Input dari buffer
* Printf string dari buffer
* Kosongkan memory
