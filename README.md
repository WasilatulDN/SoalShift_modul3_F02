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
* Deklarasi state yang sesuai dengan soal
* Deklarasi tid bertipe pthreas_t
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
* Membuat fungsi akmal dengan parameter * ptr
* Melakukan while true
* Jika pauseAkmal=3, maka :
* Menset ChangeAkmal = 0
* Mencetak "Agmal Ayo Bangun Disabled 10 s"
* Jeda selama 10 detik
* Set pauseAkmal = 0
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
* Jika changeAkmal = 1, maka
* Melakukan pengecekan apakah tambahAkmal = 1
* Jika memenuhi, maka AkmalStat bertambah 15
* Set pauseSiraj increment
* Set tambahAkmal = 0
```
            else if(changeAkmal == 0)
            {
                changeAkmal=1;
                tambahAkmal=0;
            }
```
* Mengecek apakah changeAkmal = 0
* Jika memenuhi, maka set changeAkmal = 1
* Set tambahAkmal = 0
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
* Membuat fungsi siraj dengan parameter * ptr
* Melakukan while true
* Jika pauseSiraj=3, maka :
* Menset ChangeSiraj = 0
* Mencetak "Fitur Iraj Ayo Tidur Disabled 10 s"
* Jeda selama 10 detik
* Set pauseSiraj = 0
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
* Jika changeAkmal = 1, maka
* Melakukan pengecekan apakah tambahAkmal = 1
* Jika memenuhi, maka AkmalStat bertambah 15
* Set pauseSiraj increment
* Set tambahAkmal = 0
```
            else if(changeSiraj == 0)
            {
                changeSiraj=1;
                kurangSiraj=0;
            }
```
* Mengecek apakah changeAkmal = 0
* Jika memenuhi, maka set changeAkmal = 1
* Set tambahAkmal = 0
```
        if(SirajStat<=0)
        {
            printf("\nIraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(EXIT_FAILURE);
        }
   	}
}
```
* Melakukan pengecekan apakah AkmalStat melebihi batas atau >= 100
* Mencetak "Agmal Terbangun,mereka bangun pagi dan berolahraga"
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
* Melakukan while true
* Scanf pil yang dipilih
* Jika pil = 1, maka printf "Agmal WakeUp_Status = " diikuti dengan status akmal
* Printf "Iraj Spirit_Status = " diikuti dengan status siraj
```
        else if(pil==2)
        {
            tambahAkmal=1;
            // system("stty -icanon -echo; dd if=/dev/tty of=/dev/null bs=1 count=1 2>/dev/null; stty icanon echo");
        
        }
```
* Jika pil = 2, maka
* tambahAkmal = 1
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
* kurangSiraj = 1
* join thread akmal dan threan siraj

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
* Fungsi berguna agar dapat mendekteksi key press (getch)
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
* Deklarasi variabel sesuai dengan kebutuhan soal
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
* Membuat fungsi kelaparan dengan parameter * ptr
* Melakukan perulangan while true 
* Jika memenuhi, maka melakukan erulangan kembali ketika jeda tidak samadengan 0
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
* Set detikLapar = 10
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
* Set detikLapar kurangi 1
* Jika jeda = 0, maka
* Jika statusLapar<=0, maka
* Printf "Monster mati karena kelaparan"
* Exit fungsi
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
* Membuat fungsi kebersihan dengan parameter * ptr
* Melakukan perulangan while true 
* Jika memenuhi, maka melakukan perulangan kembali ketika jeda tidak samadengan 0
```
        sleep(1);
        if(detikBersih==1)
        {
            detikBersih=30;
            statusBersih-=10;
        }
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
```
