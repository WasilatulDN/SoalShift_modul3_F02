# SoalShift_modul3_F02
Pertanyaan, Jawaban dan Penjelasan Praktikum Modul 3 Sistem Operasi 2019.

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
* Deklarasi array bil dan hasil bertipe integer. Array bil digunakan untuk menampung input, sedangkan array hasil digunakan untuk menampung hasil faktorial dari tiap anggota array bil
* Deklarasi variabel t_faktor bertipe pthread. Thread akan digunakan untuk menghitung faktorial dari tiap anggota array bil.
* Deklarasi variabel status1 bertipe integer. Digunakan untuk menunggu program lain agar menyelesaikan tugasnya.

```
void* faktor(void *pntr)
{
    while(status1 == 0)
    {

    }
```
* Merupakan thread untuk menghitung faktorial.
* `while(status1 == 0)` digunakan untuk menunggu jalannya thread lain yaitu thread yang akan melakukan sorting.
```
    int cur = *((int *) pntr);
```
* thread tidak dapat melakukan passing data bertipe integer. Sehingga dari void dikonversi menjadi integer. Variabel cur menunjukkan index array bil yang akan dicari faktorialnya.
```
    int num;
    num = bil[cur];
```
* Variabel num digunakan untuk menampung isi array bil dengan index cur.
```
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
* Merupakan proses untuk mencari nilai faktorial dari nilai variabel num.
* Awalnya variabel res dideklarasikan bernilai 1.
* Lalu variabel res akan dikali dengan res+1, res+2, dst hingga variabel i bernilai sama dengan variabel num.
* Variabel res merupakan hasil faktorial. Lalu nilai dari variabel res disimpan pada array hasil dengan index cur. jika ternyata variabel num bernilai kurang dari 0, maka yang disimpan pada array hasil dengan index cur adalah -1.
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
* Thread insert digunakan untuk melakukan sorting dengan cara insertion sort
* Deklarasi variabel status1 = 0
* Thread tidak dapat melakukan passing data bertipe integer. Sehingga dari void dikonversi menjadi integer. Variabel n menunjukkan banyaknya angggota array bil.
* Deklarasi variabel i,key, dan j bertipe integer
* Melakukan perulangan 
* Memindahkan element bill[0..i-1], yang lebih besar dari key, ke satu posisi di depan posisi sekarang  
* Setelah fungsi selesai dijalankan, kosongkan memori 
* Mengubah status1 = 1. Hal ini akan memiliki efek pada thread faktorial.
```
int main(int argc, char** argv)
{
    int i;
    for(i=1;i<argc;i++)
    {
        bil[i-1]=atoi((char*)argv[i]);
    }
```
* Membuat fungsi main dengan parameter argc (argumen untuk menghitung jumah parameter) dan argv(argumen untuk menampung parameter) 
* Deklarasi variabel i bertipe integer
* malakukan perulangan
* Karena argv bertipe char, maka argv[i] (angka yang akan difaktorialkan) diubah menjadi tipe integer dengan perintah `atoi((char*)argv[i])` dan ditampung pada array bil dengan index [i-1]. Konversi dilakukan mulai dari i=1 karena argv[0] berisi nama program yang dijalankan.
```
pthread_t thread;
    int *arg = malloc(sizeof(arg));
    *arg = argc -1;
```
* Deklarasi * arg bertipe int yang mengalokasikan memori sebesar arg
* Deklarasi * arg = argc-1. Variabel arg menunjukkan banyaknya angka yang akan dihitung faktorialnya (ukuran array). Ukuran array adalah jumlah argumen dikurangi 1 karena argv[0] berisi nama program yang dijalankan.
```
    pthread_create(&thread, NULL, insert, arg);
    pthread_join(thread,NULL);
```
* Membuat thread yanng digunakan untuk melakukan sorting array bil.
* Melakukan join pada thread yang telah dibuat.
```
    for(i=0;i<argc-1;i++)
    {
        int *angka = malloc(sizeof(angka));
        *angka = i;
        pthread_create(&t_faktor[i], NULL, faktor, angka);
        pthread_join(t_faktor[i],NULL);
    }
```
* Melakukan perulangan sebanyak ukuran array bil
* Deklarasi * angka bertipe int yang mengalokasikan memori sebesar angka
* Variabel angka berisi nilai dari i.
* Membuat thread yanng digunakan untuk menghitung faktorial dari bilangan pada array dengan index i.
* Melakukan join thread yang telah dibuat.
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
* Membuat perulangan sebanyak ukuran array bil
* Mencetak nilai dari array bil dengan index i.
* Jika nilai dari array hasil dengan index i tidak sama dengan -1, maka cetak nilai array tersebut.
* Jika nilai dari array hasil dengan index i sama dengan -1, maka cetak "error" karena faktorial tidak dapat digunakan untuk bilangan negatif.
* Berikut hasil setelah program dijalankan :

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal1/soal1.png" width="600">

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
* Melakukan perulangan terus menerus
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
* Melakukan perulangan terus-menerus
* Mengecek apakah ada pesan dari client, jika ada, pesan dibaca dan ditampung pada variabel buffer dengan menjalankan fungsi read()
* Setiap membaca input, maka membuat thread yang digunakan untuk mengecek isi pesan dari client
* Melakukan join pada thread yang telah dibuat
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
```
* port pada client jual dibuat sama dengan port pada server jual
```
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
* Melakukan perulangan terus menerus
* Mengosongkan variabel string
* Menscan atau memasukkan input dan disimpan dalam variabel string
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
```
* Membuat fungsi cek dengan parameter arg
* Deklarasi variabel * pesangagal berisi string "transaksi gagal"
* Deklarasi variabel * pesansukses berisi string "transaksi berhasil"
* Deklarasi variabel * pesangagal1 berisi string "perintah salah"
``` 
    if(strcmp(buffer,"beli")==0)
    {
        if(*stok > 0)
        {
            *stok = *stok - 1;
            printf("%s\n",pesansukses);
            send(new_socket , pesansukses , strlen(pesansukses) , 0 );
        }
```
* Memandingkan apakah isi dari buffer = "beli"
* Jika benar dan stok tersedia, maka stok berkurang 1
* Printf isi dari variabel pesansukses
* Mengirim isi dari variabel pesansukses menuju client beli
```
        else
        {
            printf("%s\n",pesangagal);
            send(new_socket , pesangagal , strlen(pesangagal) , 0 );
        }
    }
```
* Jika benar namun stok tidak tersedia, maka tampilkan isi dari pesangagal
* Mengirim isi dari variabel pesangagal menuju client beli
```
    else
    {
        printf("%s\n",pesangagal1);
        send(new_socket , pesangagal1 , strlen(pesangagal1) , 0 );
    }
        
    memset(buffer, 0, 1024);
}
```
* Jika isi dari variabel bukan "beli", maka cetak isi variabel pesangagal1
* Mengirim isi variabel pesangagal1 menuju client beli
* Mengosongkan isi variabel buffer
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
* stok awalnya didefinisikan 0
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
* Melakukan perulangan terus menerus
* Mengecek apakah ada pesan dari client, jika ada, pesan dibaca dan ditampung pada variabel buffer dengan menjalankan fungsi read()
* Setiap membaca input, maka membuat thread yang digunakan untuk mengecek isi pesan dari client
* Melakukan join pada thread yang telah dibuat
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
```
* port pada client beli dibuat sama dengan port pada server beli
```
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
* Define port client beli = 8000
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
* Melakukan perulangan terus menerus
* Kosongkan isi variabel string
* Scanf input client beli dan menampungnya ke variabel string
* Mengirimkan isi variabel string menuju server beli
* Membaca Input dari buffer (pesan dari server)
* mencatak isi string dari buffer
* Kosongkan variabel buffer
* Berikut saat program dijalankan :
* Pada server jual

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal2/soal2serverjual.png" width="600">

* Pada client jual

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal2/soal2clientjual.png" width="600">

* Pada server beli

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal2/soal2serverbeli.png" width="600">

* Pada client beli

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal2/soal2clientbeli.png" width="600">

## Soal 3
#### Pertanyaan :
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:
Terdapat 2 karakter Agmal dan Iraj
Kedua karakter memiliki status yang unik
Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
Iraj memiliki Spirit_Status, di awal program memiliki status 100
Terdapat 3 Fitur utama
All Status, yaitu menampilkan status kedua sahabat
Ex: Agmal WakeUp_Status = 75 
      Iraj Spirit_Status = 30
“Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
“Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
Terdapat Kasus yang unik dimana:
Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
Program akan berhenti jika Salah Satu :
WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

Syarat Menggunakan Lebih dari 1 Thread
##### Jawaban :
```
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
```
* Deklarasi library thread
```
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
```
* Variabel AkmalStat diinisiasi bernilai 0 (sesuai permintaan soal).
* Variabel SirajStat diinisiasi bernilai 100 (sesuai permintaan soal).
* Variabel changeAkmal diinisiasi bernilai 1. Nilai 1 berarti AkmalStat boleh diubah (ditambah nilainya). Nilai 0 berarti AkmalStat tidak boleh diubah (ditambah nilainya).
* Variabel changeSiraj diinisiasi bernilai 1. Nilai 1 berarti SirajStat boleh diubah (dikurang nilainya). Nilai 0 berarti SirajStat tidak boleh diubah (dikurang nilainya).
* Variabel pauseAkmal diinisiasi bernilai 0. Nilai 0 berarti fitur "AGmal Ayo Bangun" tidak sedang di freeze selama 10 detik. Nilai 1 berarti fitur "Iraj Ayo Tidur" sudah dijalankan 1 kali. Nilai 2 berarti fitur "Iraj Ayo Tidur" sudah dijalankan 2 kali. Ketika bernilai 3 maka fitur sedang di freeze selama 10 detik.
* Variabel pauseSiraj diinisiasi bernilai 0. Nilai 0 berarti fitur "Iraj Ayo Tidur" tidak sedang di freeze selama 10 detik. Nilai 1 berarti fitur "Agmal Ayo Bangun" sudah dijalankan 1 kali. Nilai 2 berarti fitur "Agmal Ayo Bangun" sudah dijalankan 2 kali. Ketika bernilai 3 maka fitur sedang di freeze selama 10 detik.
* Variabel tambahAkmal diinisiasi bernilai 0. Nilai 0 berarti fitur "Agmal Ayo Bangun" belum dipanggil. Nilai 1 berarti fungsi "Agmal Ayo Bangun" sudah dipanggil namun belum dieksekusi.
* Variabel kurangSiraj diinisiasi bernilai 0. Nilai 0 berarti fitur "Iraj Ayo Tidur" belum dipanggil. Nilai 1 berarti fungsi "Iraj Ayo Tidur" sudah dipanggil namun belum dieksekusi.
* Deklarasi tid bertipe pthread_t yang akan digunakan saat membuat thread
```
void* akmal(void *ptr){
	while(1){
            if(pauseAkmal==3)
            {
                changeAkmal=0;
                printf("\nAgmal Ayo Bangun disabled 10 s\n");
                sleep(10);
                pauseAkmal=0;
            }
```
* Membuat fungsi akmal dengan parameter void * ptr
* Melakukan perulangan terus menerus
* Jika pauseAkmal=3, maka :
* Menset changeAkmal = 0. Artinya AkmalStat tidak boleh diubah.
* Mencetak "Agmal Ayo Bangun Disabled 10 s"
* Jeda selama 10 detik
* Set pauseAkmal = 0. Artinya counter fitur "Iraj Ayo Tidur" direset.
```
            else if(changeAkmal==1)
            {
                if(tambahAkmal==1)
                {
                    
                    AkmalStat+=15;
                    pauseSiraj++;
                    tambahAkmal=0;
                }
            }
```
* Jika changeAkmal = 1 (AkmalStat boleh diubah), maka
* Melakukan pengecekan apakah tambahAkmal = 1 (Apakah fitur sedang dipanggil namun belum dieksekusi).
* Jika memenuhi, maka AkmalStat bertambah 15
* Counter pauseSiraj mengalami increment
* Set tambahAkmal = 0. Artinya fitur sudah dieksekusi sehingga nilai tambahAkmal dikembalikan ke 0.
```
            else if(changeAkmal == 0)
            {
                changeAkmal=1;
                tambahAkmal=0;
            }
```
* Mengecek apakah changeAkmal = 0 (AkmalStat tidak boleh diubah)
* Jika memenuhi, maka set changeAkmal = 1. (mereset sehingga AkmalStat boleh diubah). Kondisi ini terpenuhi ketika fitur "Agmal Ayo Bangun" disabled. Saat disabled, changeAkmal di set menjadi 0. Saat program selesai menjalankan `sleep`, program akan masuk ke kondisi ini.
* Set tambahAkmal = 0. Saat disabled, mungkin saja user tetap mencoba menjalankan fitur "Agmal Ayo Bangun". Ketika user mencoba menjalankan fitur "Agmal Ayo Bangun", variabel changeAkmal akan di set menjadi 1. Oleh karena itu, Saat program selesai menjalankan `sleep`, tambahAkmal di reset menjadi 0.
```
        if(AkmalStat>=100)
        {
            printf("\nAgmal Terbangun,mereka bangun pagi dan berolahraga\n");
            exit(EXIT_FAILURE);
        }		
	}
}
```
* Melakukan pengecekan apakah AkmalStat melebihi batas atau >= 100
* Mencetak "Agmal Terbangun,mereka bangun pagi dan berolahraga"
* Exit program
```
void* siraj (void *ptr){
	while(1){
            if(pauseSiraj==3)
            {
                changeSiraj=0;
                printf("\nFitur Iraj Ayo Tidur disabled 10 s\n");
                sleep(10);
                pauseSiraj=0;
            }
```
* Membuat fungsi siraj dengan parameter void * ptr
* Melakukan perulangan terus menerus
* Jika pauseSiraj=3, maka :
* Menset changeSiraj = 0. Artinya SirajStat tidak boleh diubah.
* Mencetak "Iraj Ayo Tidur Disabled 10 s"
* Jeda selama 10 detik
* Set pauseSiraj = 0. Artinya counter fitur "Agmal Ayo Bangun" direset.
```
            else if(changeSiraj==1)
            {
                if(kurangSiraj==1)
                {
                    
                    SirajStat-=20;
                    pauseAkmal++;
                    kurangSiraj=0;
                }
            }
```
* Jika changeSiraj = 1 (SirajStat boleh diubah), maka
* Melakukan pengecekan apakah tambahSiraj = 1 (Apakah fitur sedang dipanggil namun belum dieksekusi).
* Jika memenuhi, maka SirajStat berkurang 20
* Counter pauseAkmal mengalami increment
* Set kurangSiraj = 0. Artinya fitur sudah dieksekusi sehingga nilai kurangSiraj dikembalikan ke 0.
```
            else if(changeSiraj == 0)
            {
                changeSiraj=1;
                kurangSiraj=0;
            }
```
* Mengecek apakah changeSiraj = 0 (SirajStat tidak boleh diubah)
* Jika memenuhi, maka set changeSiraj = 1. (mereset sehingga SirajStat boleh diubah). Kondisi ini terpenuhi ketika fitur "Iraj Ayo Tidur" disabled. Saat disabled, changeSiraj di set menjadi 0. Saat program selesai menjalankan `sleep`, program akan masuk ke kondisi ini.
* Set kurangSiraj = 0. Saat disabled, mungkin saja user tetap mencoba menjalankan fitur "Iraj Ayo Tidur". Ketika user mencoba menjalankan fitur "Iraj Ayo Tidur", variabel changeSiraj akan di set menjadi 1. Oleh karena itu, Saat program selesai menjalankan `sleep`, kurangSiraj di reset menjadi 0.
```
        if(SirajStat<=0)
        {
            printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(EXIT_FAILURE);
        }
   	}
}
```
* Melakukan pengecekan apakah SirajStat melebihi batas atau <=0
* Mencetak "Iraj ikut tidur, dan bangun kesiangan bersama Agmal"
* Exit program
```
void menu()
{
    printf("Fitur :\n");
    printf("1. All Status\n");
    printf("2. Agmal Ayo Bangun\n");
    printf("3. Iraj Ayo Tidur\n");
    printf("Masukkan pilihan > ");
}
```
* Membuat fungsi menu sesuai dengan soal
* Digunakan untuk mencetak menu
```
int main()
{
    pthread_create(&(tid[0]),NULL,akmal,NULL);
    pthread_create(&(tid[1]),NULL,siraj,NULL);
    int pil;
 ```
 * Membuat thread bernama akmal
 * Membuat thread bernama siraj
 ```
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
```
* Melakukan perulangan terus menerus
* Scanf pil yang dipilih
* Jika pil = 1, maka cetak "Agmal WakeUp_Status = " diikuti dengan AkmalStat
* Cetak "Iraj Spirit_Status = " diikuti dengan SirajStat
```
        else if(pil==2)
        {
            tambahAkmal=1;
            // system("stty -icanon -echo; dd if=/dev/tty of=/dev/null bs=1 count=1 2>/dev/null; stty icanon echo");
        
        }
```
* Jika pil = 2, maka
* set tambahAkmal = 1. Artinya fitur "Agmal Ayo Bangun" dipanggil namun belum dieksekusi.
```
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
```
* Jika pil =3, maka
* set kurangSiraj = 1. Artinya fitur "Iraj Ayo Tidur" dipanggil namun belum dieksekusi.
* join thread akmal dan thread siraj
* Berikut hasil setelah program dieksekusi :

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal3/soal3a.png" width="600">

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal3/soal3b.png" width="600">

## Soal 4
#### Pertanyaan :
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
Ketika Mengekstrak file .zip juga harus secara bersama-sama
Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
Wajib Menggunakan Multithreading
Boleh menggunakan system
#### Jawaban :
```
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[4];
int jeda=0;
```
* Deklarasi library thread
* Deklarasi tid bertipe thread
* Deklarasi jeda bertipe integer dan inisialisasi = 0
```
void *simpan(void *arg)
{
        printf("Membuat file SimpanProses1.txt\n");
        system("ps -aux | head -10 > /home/ihdiannaja2911/Documents/FolderProses1/SimpanProses1.txt");
        printf("Membuat file SimpanProses2.txt\n");
        system("ps -aux | head -10 > /home/ihdiannaja2911/Documents/FolderProses2/SimpanProses2.txt");
        jeda = 1;
        return NULL;
}
```
* Mmembuat fungsi simpan dengan parameter arg
* Printf "Membuat file SimpanProses1.txt"
* Melakukan system untuk membuat file SimpanProses1.txt dan berisi list proses maksimal 10 proses
* Printf "Membuat file SimpanProses2.txt"
* Melakukan system untuk membuat file SimpanProses2.txt dan berisi list proses maksimal 10 proses
* Set jeda = 1
```
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
```
* Mmembuat fungsi kompres dengan parameter arg
* Melaukan perulangan jika proses sebelumnya belum selesai
* Printf "Membuat KompresProses1.zip"
* Melakukan system untuk mengzip file SimpanProses1.txt dan menyimpannya dalam /home/ihdiannaja2911/Documents/FolderProses1/KompresProses1.zip 
* Printf "Membuat KompresProses2.zip"
* Melakukan system untuk mengzip file SimpanProses2.txt dan menyimpannya dalam /home/ihdiannaja2911/Documents/FolderProses1/KompresProses1.zip 
* Set jeda = 2
```
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
```
* Mmembuat fungsi hapus dengan parameter arg
* Melaukan perulangan jika proses sebelumnya belum selesai
* Printf "Delete file SimpanProses1.txt"
* Melakukan system untuk menghapus file SimpanProses1.txt  
* Printf "Delete file SimpanProses2.txt"
* Melakukan system untuk menghapus file SimpanProses2.txt 
* Set jeda = 3
```
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
```
* Membuat fungsi ekstrak dengan parameter arg
* Melaukan perulangan jika proses sebelumnya belum selesai
* Printf "Menunggu 15 detik untuk mengekstrak kembali"
* Melakukan system untuk mengunzip file KompresProses1.zip dan menyimpannya dalam /home/ihdiannaja2911/Documents/FolderProses1/
* Melakukan system untuk mengunzip file KompresProses2.zip dan menyimpannya dalam /home/ihdiannaja2911/Documents/FolderProses2/
```
int main(void)
{
        pthread_create(&(tid[0]),NULL,simpan,NULL);
        pthread_create(&(tid[1]),NULL,kompres,NULL);
        pthread_create(&(tid[2]),NULL,hapus,NULL);
        pthread_create(&(tid[3]),NULL,ekstrak,NULL);
```
* Membuat fungsi main 
* Membuat 4 thread, yaitu simpan, kompres, hapus, dan ekstrak
```
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_join(tid[2],NULL);
        pthread_join(tid[3],NULL);

        exit(0);
        return 0;
}
```
* Join tiap thread yang telah dibuat
* Proses selesai, exit proses
* Berikut hasil saat program dijalankan :

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal4/soal4tok.png" width="600">

* Membuat file .txt

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal4/soal4buat.png" width="600">

* Mengompres file .zip

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal4/soal4zip.png" width="600">

* Menghapus file .txt

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal4/soal4hapus.png" width="600">

* Mengekstrak file .zip

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal4/soal4unzip.png" width="600">

## Soal 5
#### Pertanyaan :
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
Pembeli (terintegrasi dengan game)
Dapat mengecek stok makanan yang ada di toko.
Jika stok ada, pembeli dapat membeli makanan.
Penjual (terpisah)
Bisa mengecek stok makanan yang ada di toko
Penjual dapat menambah stok makanan.
	Spesifikasi program:
Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
Program terdiri dari 3 scene yaitu standby, battle, dan shop.
Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode
Health : [health status]
Hunger : [hunger status]
Hygiene : [hygiene status]
Food left : [your food stock]
Bath will be ready in [cooldown]s
Choices
Eat
Bath
Battle
Shop
Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
Monster’s Health : [health status]
Enemy’s Health : [enemy health status]
Choices
Attack
Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
Buy
Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
Food stock : [shop food stock]
Choices
Restock
Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))
##### Jawaban :
```
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<termios.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
```
* Deklarasi library thread
```
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
```
* Fungsi berguna agar dapat mendekteksi key press (getch). Pada linux tidak terdapat library conio.h
```
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
```
* Deklarasi variabel sesuai dengan kebutuhan soal.
* Variabel nama digunakan untuk menampung nama monster sesuai dengan input user
* Varibel statusLapar diinisiasi bernilai 200.
* Variabel statusBersih diinisiasi bernilai 100
* Variabel statusSehat diinisiasi bernilai 300
* Variabel detik diinisiasi bernilai 20. Digunakan untuk melakukan countdown kamar mandi
* Variabel detikSehat diinisiasi bernilai 10. Digunakan untuk melakukan countdown bertambahnya StatusSehat
* Variabel detikBersih diinisiasi bernilai 30. Digunakan untuk melakukan countdown berkurangnya StatusBersih
* Variabel detikLapar diinisiasi bernilai 10. Digunakan untuk melakukan countdown berkurangnya StatusLapar
* Variabel siapMandi diinisiasi bernilai 0. Nilai 0 artinya kamar mandi belum siap digunakan. Nilai 1 artinya kamar mandi siap digunakan.
* Variabel jeda diinisiasi bernilai 0. Digunakan untuk mengatur jalannya fitur-fitur pada game.
* Variabel makanan diinisiasi bernilai 0. Digunakan untuk menunjukkan banyak makanan yang dimiliki oleh monster.
```
void* kelaparan (void *ptr)
{
    while(1)
    {
        // sleep(10);
        while(jeda!=0)
        {

        }
```
* Membuat fungsi kelaparan dengan parameter void * ptr
* Melakukan perulangan terus menerus
* Ketika jeda tidak sama 0 maka fitur tidak akan berjalan (baris program dibawahnya tidak dijalankan)
```
        sleep(1);
        if(detikLapar==1)
        {
            detikLapar=10;
            statusLapar-=5;            
        }
```
* Pause selama 1 detik
* Jika detikLapar = 1, maka
* Set detikLapar = 10 (mereset sehingga akan countdown lagi mulai dari 10)
* Set statusLapar dikurangi 5
```
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
```
* Jika detikLapar tidak samadengan 1
* Set detikLapar kurangi 1 (melakukan countdown)
* Jika jeda = 0, maka
* Jika statusLapar<=0, maka
* Printf "Monster mati karena kelaparan"
* Exit program utama
```
void* kebersihan (void *ptr)
{
    while(1)
    {
        // sleep(30);
        while(jeda!=0)
        {
            
        }
```
* Membuat fungsi kebersihan dengan parameter void * ptr
* Melakukan perulangan terus menerus
* Ketika jeda tidak sama 0 maka fitur tidak akan berjalan (baris program dibawahnya tidak dijalankan)
```
        sleep(1);
        if(detikBersih==1)
        {
            detikBersih=30;
            statusBersih-=10;
        }
```
* Pause selama 1 detik
* Jika detikBersih = 1, maka
* Set detikBersih = 30 (mereset sehingga akan countdown lagi mulai dari 30)
* Set statusBersih dikurangi 10
```
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
```
* Jika detikBersih tidak samadengan 1
* Set detikBersih kurangi 1 (melakukan countdown)
* Jika jeda = 0, maka
* Jika statusBersih<=0, maka
* Printf "Monster mati karena terlalu kotor"
* Exit program utama
```
void* kesehatan (void *ptr)
{
    while(1)
    {
        while(jeda!=0)
        {
            
        }
        sleep(1);
```
* Membuat fungsi kesehatan dengan parameter void * ptr
* Melakukan perulangan terus menerus
* Ketika jeda tidak sama 0 maka fitur tidak akan berjalan (baris program dibawahnya tidak dijalankan)
```
        if(detikSehat==1)
        {
            detikSehat=10;
            statusSehat+=5;
        }
```
* Pause selama 1 detik
* Jika detikSehat = 1, maka
* Set detikSehat = 10 (mereset sehingga akan countdown lagi mulai dari 10)
* Set statusSehat dikurangi 5
```
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
```
* Jika detikSehat tidak samadengan 1
* Set detikSehat kurangi 1 (melkukan countdown)
* Jika jeda = 0, maka
* Jika statusSehat<=0, maka
* Printf "Monster mati karena sakit-sakitan"
* Exit program utama
```
void* countdown (void *ptr)
{
    while(1)
    {
        while(jeda!=0)
        {
            
        }
```
* Membuat fungsi countdown dengan parameter * ptr
* Melakukan perulangan terus menerus
* Ketika jeda tidak sama 0 maka fitur tidak akan berjalan (baris program dibawahnya tidak dijalankan)
```
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
```
* Jika siapMandi = 0 (kamar mandi belum siap digunakan), maka
* Pause selama 1 detik
* Kemudian melakukan pengecekan apakah detik = 0,
* Jika benar, maka set detik = 20 (mereset detik sehingga countdown akan dimulai dari 20 lagi)
* Dan set siapMandi = 1 (kamar mandi siap digunakan)
* Jika tidak benar, maka set detik = -1 (melakukan countdown)
```
int *jumMakan;
```
* Deklarasi * jumMakan bertipe integer
```
void* toko (void* arg){
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumMakan = shmat(shmid, NULL, 0);

    *jumMakan = 0;
}
```
* Membuat fungsi toko
* Fungsi ini digunakan untuk menginisiasi shared memory
```
void* menu(void *arg)
{
    while(1){
    while(jeda!=0)
    {

    }
    system("clear");
```
* Membuat fungsi menu dengan parameter arg
* Melakukan perulangan terus menerus
* Ketika jeda tidak sama 0 maka fitur tidak akan berjalan (baris program dibawahnya tidak dijalankan)
* Melakukan system("clear") (mengosongkan tampilan pada console)
```
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
```
* Printf status peliharaan, peliharaan ketika battle, kemudian pause selama 1 detik (menu dicetak tiap 1 detik)
```
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
```
* Membuat fungsi menu2 dengan parameter arg
* Melakukan perulangan terus menerus
* Ketika jeda tidak sama 0 maka fitur tidak akan berjalan (baris program dibawahnya tidak dijalankan)
* Melakukan system("clear") (mengosongkan tampilan console)
* Printf menu sesuai dengan kebutuhan suntuk peliharaan berbelanja (menu saat shop mode)
* Pause selama 1 detik (menu dicetak tiap satu detik)
```
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
```
* Membuat fungsi main
* Deklarasi variabel c bertipe char
* Deklarasi variabel i bertike integer
* Printf "Beri nama monstermu > " 
* input char untuk memberi nama peliharaan
* Melakukan perulangan ketika input yang dimasukkan bukan enter (\n)
* Jika memenuhi, maka membaca tiap karakter dan dimasukkan ke dalam variabel nama dengan index i.
* Melakukan perintah untuk scan karakter
* Increment i
```
    pthread_create(&(tid[0]),NULL,kelaparan,NULL);
    pthread_create(&(tid[1]),NULL,kebersihan,NULL);
    pthread_create(&(tid[2]),NULL,kesehatan,NULL);
    pthread_create(&(tid[3]),NULL,countdown,NULL);
    pthread_create(&(tid[4]),NULL,menu,NULL);
    pthread_create(&(tid[5]),NULL,toko,NULL);
    pthread_create(&(tid[6]),NULL,menu2,NULL);
```
* Membuat thread kelaparan, kebersihan, kesehatan, countdown, menu, toko, menu2
```
    while(1)
    {
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
```
* Melakukan perulangan terus menerus
* Input angka untuk menentukan perintah (pil) yang diinginkan
* Jika pil = 1, maka
* Jika makanan>0 (monster mempunyai makanan), maka statusLapar ditambah 15
* Decrement makanan
* Jika statusLapar>200, maka statusLapar = 200 (monster maksimal hanya bisa memiliki statusLapar 200)
```
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
```
* Jika pil = 2, maka
* Mengecek apakah siapMandi = 1 (kamar mandi siap digunakan)
* Jika benar, maka statusBersih bertambah 30
* Jika statusBersih>100, maka set statusBersih = 100 (monster maksimal hanya bisa memiliki statusBersih 100)
* Set siapMandi = 0 (kamar mandi tidak siap digunakan)
```
        else if(pil=='3')
        {
            int statusLawan=100;
            jeda=1;
```
* Jika pil = 3, maka
* Set statusLawan = 100
* Deklarasi jeda = 1 untuk me-freeze thread yang mengubah nilai statusSehat, statusBersih, siapMandi, dll.
```
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
```
* Melakukan while true
* Melakukan system("clear")
* Printf untuk menampilkan status health monster dan enemy
* Printf pilihan perintah untuk battle
* Deklarasi charac bertipe char
* Melakukan fungsi getch() yang disimpan dalam charac
```
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
```
* Jika charac = 1, maka
* Set statusSehat dikurangi 20
* Jika statusLawan>0 (atau lawan belum kalah), maka set statusLawan dikurangi 20
* Jika statusSehat < 0, maka statusSehat = 0, jeda = 0, kemudian break
* Jika statusLawan < 0, maka set statusLawan = 0 (statusLawan tidak bisa negatif)
```
                else if(charac=='2')
                {
                    jeda=0;
                    break;
                }
            }
        }
```
* Jika charac = 2, maka set jeda =0 kemudian break. Jeda dikembalikan ke 0 agar thread yang mengubah nilai statusLapar, statusBersih, dll bisa berjalan.
```
        else if(pil=='4')
        {
            jeda=2;
            char charac;
```
* Jika pil = 4, maka:
* Set jeda = 2, kemudian deklarasi charac bertipe char. Jeda diatur sama dengan 2 agar thread menu2 dapat mencetak menu shop mode.
```
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
```
* Melakukan while true
* Melakukan fungsi getch() yang disimpan dalam variabel charac
* Jika charac = 1, maka :
* Melakukan pengecekan apakah shared memory jumMakan > 0, 
* Jika benar, maka jumMakan dikurangi 1
* Increment makanan
* Jika charac = 2, maka :
* Set jeda = 0
* Kemudian break
```
        else if(pil=='5')
        {
            system("clear");
            printf("Sampai jumpa!!\n");
            exit(EXIT_FAILURE);
            break;
        }    
    }
```
* Jika pil = 5, maka :
* Melakukan system("clear")
* Printf "Sampai jumpa!!"
* Melakukan perintah exit (keluar dari program utama)
* Break dari pengecekan
```
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    pthread_join(tid[3],NULL);
    pthread_join(tid[4],NULL);
    pthread_join(tid[5],NULL);
    pthread_join(tid[6],NULL);
    return 0;
}
```
* Melakukan thread join untuk ketujuh thread di atas
##### Soal 5 Jual :
```
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include<stdlib.h>
#include<termios.h>
#include<pthread.h>
```
* Deklarasi library thread
```
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
```
* Fungsi di atas agar dapat menggunakan fungsi getch(). Pada linux tidak terdapat library conio.h
```
int *jumMakan;
pthread_t tid[2];

void* awal (void* arg)
{
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumMakan = shmat(shmid, NULL, 0);
  
    *jumMakan = 0;

}
```
* Deklarasi jumMakan bertipe integer
* Deklarasi tid bertipe pthread_t
* Membuat fungsi awal dengan parameter arg
* Di dalam fungsi awal berisi perintah untuk shared memory
```
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
```
* Membuat fungsi menutoko dengan parameter arg
* Melakukan while true
* Printf hal yang dibutuhkan untuk shop
* Pause selama 1 detik (menu dicetak tiap satu detik)
```
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
```
* Membuat fungsi main
* Mmembuat thread awal dan menutoko
* Deklarasi variabel pil bertipe char
* Melakukan perulangan terus menerus
* Jika memenuhi maka masukka input ke dalam variabel pil
* Jika pil = 1, maka jumMakan + 1
* Jika pil = 2, maka break
* Berikut hasil setelah program dijalankan
* Stanby Mode

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal5/soal5standby.png" width="600">

* Shop Mode

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal5/soal5shop.png" width="600">

* Battle Mode

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal5/soal5battle.png" width="600">

* Toko

<img src="https://github.com/WasilatulDN/SoalShift_modul3_F02/blob/master/soal5/soal5toko.png" width="600">
