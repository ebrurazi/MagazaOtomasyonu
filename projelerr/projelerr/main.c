#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

#define N 1
#define M 2

//Sructları tanımladım

struct urun{
    char referans_kodu[20];
    float fiyat;
};
struct isci{
    char ad[20];
    char soyisim[20];
    int yas;
};
struct magaza{
    char isim[20];
    char sokak_ismi[20];
    char mahalle_ismi[20];
    char telefon_numara[15];
    float satis;
    struct isci e1;
    struct isci e2;
    struct isci e3;
    struct urun p[M];
};

//Fonksiyonun prototipleri tanımladım
void urun_olustur(struct urun *);
void isci_olustur(struct isci *);
void magaza_olustur(struct magaza *);
void urun_bas(struct urun);
void isci_bas(struct isci);
void magaza_bas(struct magaza);
void en_yasli(struct magaza);
void ortalama_fiyat(struct magaza []);
void bulundugu_mahalle(struct magaza [],char []);

int main(void){
    struct magaza m[N];
    int i;
    
    printf("********************MAGAZA OTOMASYONU********************\n\n");
    
    for (i=0;i<N; i++) {
        printf("MAGAZA %d : \n\n",i+1);
        // Kullanıcıdan mağaza verilerini almak için magaza_olustur fonksiyonu çağrıyoruz
        magaza_olustur(&m[i]);
    }
    for (i=0;i<N;i++) {
        printf("\nMagaza %d hakkında bilgi : \n\n",i+1);
        // Mağaza verilerini ekrana bastırmak için magaza_bas fonksiyonu çağrıyoruz
        magaza_bas(m[i]);
    }
   
    en_yasli(m[0]);
    ortalama_fiyat(m);
    bulundugu_mahalle(m,"sisli");
    printf("\n\n");
    return 0;
}
//Buralarda ürün,işçi ve mağaza fonksiyonu oluşturuyoruz. Kullanıcıdan verileri alıyoruz.
void urun_olustur(struct urun *ur){
    printf("Referans kodu giriniz : ");
    scanf("%s",ur->referans_kodu);
    printf("Lutfen fiyatı giriniz : ");
    scanf("%f",&ur->fiyat);
    printf("\n");
}
void isci_olustur(struct isci *is){
    printf("İşçinin adini giriniz : ");
    scanf("%s",is->ad);
    printf("İşçinin soyadini giriniz : ");
    scanf("%s",is->soyisim);
    printf("İşçinin yaşını giriniz : ");
    scanf("%d",&is->yas);
    printf("\n");
}
void magaza_olustur(struct magaza *ma){
    int k;
    
    printf("Lütfen mağazanın ismini giriniz : ");
    scanf("%s",ma->isim);
    printf("Lütfen mağazanın bulunduğu sokak ismini giriniz : ");
    scanf("%s",ma->sokak_ismi);
    printf("Mağazanın bulunduğu mahalle ismi giriniz : ");
    scanf("%s",ma->mahalle_ismi);
    printf("Mağazanin telefon numarasını girin : ");
    scanf("%s",ma->telefon_numara);
    printf("Satisin sayisini giriniz : ");
    scanf("%f",&ma->satis);
    printf("\n");
    printf("İsçi 1 : \n");
    isci_olustur(&ma->e1);
    printf("İşçi 2 : \n");
    isci_olustur(&ma->e2);
    printf("İşçi 3 : \n");
    isci_olustur(&ma->e3);
    
    for (k=0;k<M;k++) {
        printf("Ürünleri giriniz %d :\n",k);
        urun_olustur(&ma->p[k]);
    }
}

//Ürün,işçi ve mağaza bas fonksiyonlarında verileri yazdırıyoruz
void urun_bas(struct urun u){
    printf("\tReferans kodu : %s\n",u.referans_kodu);
    printf("\tFiyat : %f\n",u.fiyat);
    printf("\n");
}
void isci_bas(struct isci i){
    printf("\tİsim : %s\n",i.ad);
    printf("\tSoyisim : %s\n",i.soyisim);
    printf("\tYas : %d\n",i.yas);
    printf("\n");
}
void magaza_bas(struct magaza m){
    int a;
    
    printf("Mağazanın ismi : %s\n",m.isim);
    printf("Mağazanın bulunduğu sokak : %s\n",m.sokak_ismi);
    printf("Mağazanın bulunduğu mahalle : %s\n",m.mahalle_ismi);
    printf("Mağazanın telefon numarası : %s\n",m.telefon_numara);
    printf("Satış rakamı : %f\n",m.satis);
    printf("\n");
    printf("İşçi 1 : \n");
    isci_bas(m.e1);
    printf("işçi 2 : \n");
    isci_bas(m.e2);
    printf("İşçi 3 : \n");
    isci_bas(m.e3);
    
    for (a=0;a<M;a++) {
        printf("Urun %d:\n",a);
        urun_bas(m.p[a]);
    }
}

//Girilen yaşlardan en yaşlısını bulup yazdırıyoruz
void en_yasli(struct magaza ya){
    struct isci yasli;
    if(ya.e1.yas>yasli.yas)
        yasli=ya.e1;
    if(ya.e2.yas>yasli.yas)
        yasli=ya.e2;
    if(ya.e3.yas>yasli.yas)
        yasli=ya.e3;
    printf("\nEn yaşlı işçi:\n");
    isci_bas(yasli);
}

//Ürünlerin ortalama fiyatını yazdırıyoryuz
void ortalama_fiyat(struct magaza m[N]){
    float toplam=0;
    int i,j;
    
    for (i=0;i<N;i++) {
        for (j=0;j<M;j++) {
            toplam+=m[i].p[j].fiyat;
        }
        printf("\n'%s' mağazasında yer alan ürünlerin ortalama fiyati : %f\n",m[i].isim,(float)toplam/M);
    }
}

//Bulunduğu mahalle main de belirttiğimiz mahalle ise fonksiyon çalışıp göstermektedir.
void bulundugu_mahalle(struct magaza m[N],char kopMah[12]){
    int i;
    for (i=0;i<N; i++) {
        if(strcmp(m[i].mahalle_ismi,kopMah) == 0){
            printf("'%s' mahallesinde '%s' mağazası bulunur \n",m[i].mahalle_ismi,m[i].isim);
        }
    }
}
