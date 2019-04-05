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
