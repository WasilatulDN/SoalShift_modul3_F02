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
* Server Jual
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
