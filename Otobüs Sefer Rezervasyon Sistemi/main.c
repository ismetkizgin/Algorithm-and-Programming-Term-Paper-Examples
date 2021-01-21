#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int otobusKapasitesi[100];
int otobusPersonelSayisi[100];
char otobusModeli[100][20]; 
int otobusSayisi = 0;

char seferNumaralari[100][6];
char seferBaslangicSehri[100][20];
char seferVarisSehri[100][20];
int seferOtobosNumarasi[100];
int seferOtobusBaslangicSaati[100];
int seferOtobusVarisSaati[100];
float seferHasilati[100];
int seferKoltukDurumu[100][100] = { 0 };
int seferSayisi = 0;

char rezervasyonKodu[1000][8];
char rezervasyonAd[1000][20];
char rezervasyonSoyad[1000][20];
int rezervasyonKoltukNo[1000];
int rezervasyonSeferIndis[1000];
int rezervasyonSayisi = 0;

char hex_arr[4];

void firmaIslemleri();
void otobusEkle();
void hexadecimal();
void seferNumarasiOlustur();
void seferEkle();
int koltukBilgisi(int);
void seferListesi();
void seferBilgisi(int);
void seferKoltukBilgisi();
void musteriIslemleri();
void rezervayonYap();
void rezervasyonNumarasiOlustur();
void rezervayonBilgisi();

int main(void) {
    do {
        int islemNumarasi;
        printf("Ana Menu\n\n1. Firma Girisi\n2. Musteri Girisi\n3. Cikis\n\nLutfen Bir Islem Numarasi Giriniz:-> ");
        scanf("%d", &islemNumarasi);

        switch(islemNumarasi) {
            case 1:
                firmaIslemleri();
                break;
            case 2:
                musteriIslemleri();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Lutfen dogru islem numarasi giriniz...\n\n");
                break;
        }
    } while(1);
}

void firmaIslemleri() {
    do {
        int islemNumarasi;
        printf("1. Otobus Ekleme\n2. Sefer Bilgisi Ekleme\n3. Sefer/Koltuk Bilgisi\n4. Bir Ust Menuye Don\n\nLutfen Bir Islem Numarasi Giriniz:->");
        scanf("%d", &islemNumarasi);
        
        if(islemNumarasi == 4)
            break;

        switch(islemNumarasi) {
            case 1:
                otobusEkle();
                break;
            case 2:
                seferEkle();
                break;
            case 3:
                seferKoltukBilgisi();
                break;
            default:
                printf("Lutfen dogru islem numarasi giriniz...\n\n");
                break;
        }
    } while(1);
}

void musteriIslemleri() {
    do {
        int islemNumarasi;
        printf("1. Seferleri Listele\n2. Sefer Rezervasyon Yap\n3. Rezervasyon GÃ¶ster\n4. Bir Ust Menute Don\n\nLutfen Bir Islem Numarasi Giriniz:->");
        scanf("%d", &islemNumarasi);
        
        if(islemNumarasi == 4)
            break;

        switch(islemNumarasi) {
            case 1:
                seferListesi();
                break;
            case 2:
                rezervayonYap();
                break;
            case 3:
                rezervayonBilgisi();
                break;
            default:
                printf("Lutfen dogru islem numarasi giriniz...\n\n");
                break;
        }
    } while(1);
}

void otobusEkle() {
    if(otobusSayisi > 99) {
        printf("Otobus sayisi max. ulasti...\n\n");
        return;
    }

    printf("Otobus Kapasitesini Giriniz: ");
    scanf("%d", &otobusKapasitesi[otobusSayisi]);
    printf("Otobus Modelini Giriniz: ");
    scanf("%s", otobusModeli[otobusSayisi]);
    
    if(otobusKapasitesi[otobusSayisi] <= 30) {
        printf("Otobus Kýsa Yol Otobusu Oldugu Icin 2 Personel Atandi.\n");
        ++otobusSayisi;
        return;    
    }

    while (1) {
        printf("Otobus Personel Sayisini Giriniz: ");
        scanf("%d", &otobusPersonelSayisi[otobusSayisi]);

        if(otobusPersonelSayisi[otobusSayisi] == 2 || otobusPersonelSayisi[otobusSayisi] == 3) {
            ++otobusSayisi;
            break;
        }        
        printf("Lutfen 2 veya 3 Olarak Giriniz Personel Sayisini.\n\n");
    }
}

void seferEkle() {
    seferNumarasiOlustur();

    while (1) {
        printf("Otobus Numarasini Giriniz: ");
        scanf("%d", &seferOtobosNumarasi[seferSayisi]);

        if(0 < seferOtobosNumarasi[seferSayisi] && otobusSayisi >= seferOtobosNumarasi[seferSayisi])
            break;

        printf("Dogru Otobus Numarasini Giriniz...\n\n");
    }

    while (1) {
        printf("Sefer saatini giriniz: ");
        scanf("%d",&seferOtobusBaslangicSaati[seferSayisi]);

        if(seferOtobusBaslangicSaati[seferSayisi] < 24 && seferOtobusBaslangicSaati[seferSayisi] >= 0) 
            break;

        printf("Lutfen Dogru Bir Saat Giriniz(0-23)...\n\n");
    }

    while (1) {
        printf("Varis Saatini Giriniz: ");
        scanf("%d", &seferOtobusVarisSaati[seferSayisi]);

        if(!(seferOtobusVarisSaati[seferSayisi] > 4 && otobusKapasitesi[seferOtobosNumarasi[seferSayisi] - 1] <= 30))
            break;
        printf("Secilen Otobus Uzun Yola Uygun Degildir. Lutfen Saati Duzenleyin...\n\n");
    }
    
    printf("Sefer Baslangic Sehrini Giriniz: ");
    scanf("%s", seferBaslangicSehri[seferSayisi]);
    printf("Sefer Varis Sehrini Giriniz: ");
    scanf("%s", seferVarisSehri[seferSayisi]);

    printf("Sefer Hasilatini Giriniz: ");
    scanf("%f", &seferHasilati[seferSayisi]);
    printf("Koltuk Fiyati: %.2f \n\n", seferHasilati[seferSayisi]/otobusKapasitesi[seferOtobosNumarasi[seferSayisi] - 1]);
    
    ++seferSayisi;
}

void seferNumarasiOlustur() {
    int i, state = 1;
    while (1) {
      hexadecimal();
      for (i = 0; i < seferSayisi; i++) {
          if(!strcmp(hex_arr, seferNumaralari[i]))
            state = 0;
      }
      
      if(state)
        break;
    }

    strcpy(seferNumaralari[seferSayisi], "22");
    strcat(seferNumaralari[seferSayisi], hex_arr);
}


void hexadecimal() {
    srand(time(NULL));
    int num=(rand() % (50000 - 10000 + 1)) + 10000, bin = 0;    
    int i = 0, rem;

    while(num != 0) {
        rem = num % 16;
        if (rem < 10) {
            hex_arr[i++] = 48 + rem;
        }
        else {
            hex_arr[i++] = 55 + rem;
        }
        num /= 16;
    }
}

void seferListesi() {
    int i;
    printf("Sefer Numaralari\n");
    for (i = 0; i < seferSayisi; i++)
        printf("%s\n", seferNumaralari[i]);

    printf("\n\n");
}

void seferBilgisi(int seferIndis) {
    printf("\n\n**********");
    printf("Sefer No: %s\n", seferNumaralari[seferIndis]);
    printf("Otobus No: %d\n", seferOtobosNumarasi[seferIndis]);
    printf("KalkÄ±s Saati: %d:22\n", seferOtobusBaslangicSaati[seferIndis]);
    printf("Varis Saati: %d:22\n", (seferOtobusBaslangicSaati[seferIndis] + seferOtobusVarisSaati[seferIndis]) % 24 );
    printf("KalkÄ±s Sehri: %s\n", seferBaslangicSehri[seferIndis]);
    printf("Varis Sehri: %s\n", seferVarisSehri[seferIndis]);
}

void seferKoltukBilgisi() {
    seferListesi();
    char seferNumarasi[6];
    int seferIndis, i, state = 0;
    while (1) {
        printf("\nSefer Numarasini Giriniz: ");
        scanf("%s", seferNumarasi);

        for (i = 0; i < seferSayisi; i++) {
            if(!(strcmp(seferNumarasi, seferNumaralari[i]))) {
                state = 1;
                seferIndis = i;
            }
        }
        
        if(state)
            break;

        printf("Lutfen Dogru Sefer Numrasi Giriniz...\n\n");
    }

    int doluKoltukSayisi = koltukBilgisi(seferIndis);
    seferBilgisi(seferIndis);
    printf("Bos Koltuk Sayisi: %d\n", otobusKapasitesi[seferOtobosNumarasi[seferIndis] - 1] - doluKoltukSayisi);
    printf("Toplam Hasilat: %.2f\n\n", seferHasilati[seferIndis]/otobusKapasitesi[seferOtobosNumarasi[seferIndis] - 1] * doluKoltukSayisi);
}

int koltukBilgisi(int seferIndis) {
    int i, doluKoltukSayisi = 0;
    for (i = 0; i < otobusKapasitesi[seferOtobosNumarasi[seferIndis]-1]; i++) {
        if(seferKoltukDurumu[seferIndis][i]){
            printf("%d. Koltuk: X\n", i + 1);
            doluKoltukSayisi++;
        }
        else
            printf("%d. Koltuk: Bos\n", i + 1);
    }

    return doluKoltukSayisi;
}

void rezervayonYap() {
    seferListesi();
    char seferNumarasi[6];
    int seferIndis, i, state = 0;
    while (1) {
        printf("\nSefer Numarasini Giriniz: ");
        scanf("%s", seferNumarasi);

        for (i = 0; i < seferSayisi; i++) {
            if(!(strcmp(seferNumarasi, seferNumaralari[i]))) {
                state = 1;
                seferIndis = i;
            }
        }
        
        if(state)
            break;

        printf("Lutfen Dogru Sefer Numrasi Giriniz...\n\n");
    }

    char ad[20], soyad[20];
    int koltukNo;
    printf("Adinizi Giriniz: ");
    scanf("%s", ad);
    printf("Soyadinizi Giriniz: ");
    scanf("%s", soyad);

    koltukBilgisi(seferIndis);

    while (1) {
    	int kontrol=0;
        printf("Koltuk Numaranizi Seciniz: ");
        scanf("%d", &koltukNo);
		printf("\n\n");
        if(koltukNo > 0 && koltukNo <= otobusKapasitesi[seferOtobosNumarasi[seferIndis] - 1] && !seferKoltukDurumu[seferIndis][koltukNo - 1]){
        	seferKoltukDurumu[seferIndis][koltukNo - 1]=1;
        	koltukBilgisi(seferIndis);
        	while(1){
        		char onay;
        		printf("Koltuk numarasini onayliyormusunuz?(E-e/H-h) : ");
        		scanf(" %c",&onay);
        		if(onay=='E' || onay=='e' || onay=='H' || onay=='h'){
        			if(onay=='H' || onay=='h')
        				{
        					seferKoltukDurumu[seferIndis][koltukNo - 1]=0;
        					printf("\n\n");
        					koltukBilgisi(seferIndis);
        					kontrol=1;
        					break;
						}
        			else
        				{
							rezervasyonKoltukNo[rezervasyonSayisi]=koltukNo-1;
        					strcpy(rezervasyonAd[rezervasyonSayisi], ad);
        					strcpy(rezervasyonSoyad[rezervasyonSayisi], soyad);
        					rezervasyonNumarasiOlustur();
        					rezervasyonNumarasiOlustur();
        					printf("Rezervasyon Kaydedildi!\nRezervasyon Kodunuz : %s\n\n",rezervasyonKodu[rezervasyonSayisi]);
        					break;
						}
        				
				}
				else
				printf("\nLutfen dogru karakter giriniz!\n\n");
			}
			if(!kontrol)
        	break;
		}
		else
        printf("Lutfen bos bir koltuk numarasi giriniz...\n\n");
    }

    rezervasyonSayisi++;
}

void rezervasyonNumarasiOlustur() {
    int i, state = 1;
    while (1) {
      hexadecimal();
      for (i = 0; i < rezervasyonSayisi; i++) {
          if(!strcmp(hex_arr, rezervasyonKodu[i]))
            state = 0;
      }
      
      if(state)
        break;
    }
    strcat(rezervasyonKodu[rezervasyonSayisi], hex_arr);
}

void rezervayonBilgisi() {
	char rezervasyonKod[8];
	int rezervasyonIndis, i, state=0;
    while (1) {
        printf("\nRezervasyon Kodunu Giriniz: ");
        scanf("%s", rezervasyonKod);

        for (i = 0; i < rezervasyonSayisi; i++) {
        	printf("%s\n",rezervasyonKodu[i]);
            if(!(strcmp(rezervasyonKod, rezervasyonKodu[i]))) {
                state = 1;
                rezervasyonIndis = i;
            }
        }
        
        if(state)
            break;

        printf("Lutfen Dogru Rezervasyon Numranizi Giriniz...\n\n");
    }
    
    printf("\n\nRezervasyon Bilgileri\n");
    printf("Rezervasyon Kodu : %s\n",rezervasyonKodu[rezervasyonIndis]);
    printf("Ad : %s\n",rezervasyonAd[rezervasyonIndis]);
    printf("Soyad : %s\n",rezervasyonSoyad[rezervasyonIndis]);
    printf("Rezervasyon Koltuk No : %d\n",rezervasyonKoltukNo[rezervasyonIndis]+1);
    printf("Otobus Kalkis Saati : %d\n",seferOtobusBaslangicSaati[rezervasyonSeferIndis[rezervasyonIndis]]);
    printf("Sefer Süresi : %d\n",seferOtobusVarisSaati[rezervasyonSeferIndis[rezervasyonIndis]]);
}