#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int aracsayisi = 0;

typedef struct
{
    char plaka[25];
    char model[50];
    char renk[50];
} AracBilgisi;

typedef struct
{
    int id;
    struct tm *giris_saati;
    AracBilgisi aracBilgisi;
} Otopark;

Otopark otopark[1000];

void AracKayit(AracBilgisi);
void AracBilgisiYazdirma(Otopark);
void OtomatikKayit();

void AracEkle();
void AraclariListele();

int main(void)
{
    OtomatikKayit();

    do
    {
        int islem;
        printf("\n********** Otopark Sistemi ********** \n1. Arac Listesi \n2. Arac Ekleme\n3. Cikis\n\nIslem Numarasini Giriniz: ");
        scanf("%d", &islem);

        switch (islem)
        {
        case 1:
            AraclariListele();
            break;

        case 2:
            AracEkle();
            break;

        case 3:
            return 0;
            break;

        default:
            printf("Boyle Bir Islem Bulunmamaktatir...\n\n");
            break;
        }

    } while (1);
}

void AracKayit(AracBilgisi aracBilgisi)
{
    time_t saat;
    saat = time(NULL);

    otopark[aracsayisi].id = aracsayisi + 1;
    otopark[aracsayisi].giris_saati = localtime(&saat);
    otopark[aracsayisi].aracBilgisi = aracBilgisi;
    aracsayisi++;

    printf("\nArac Kayit Edildi.(Arac Sayisi: %d)\n\n", aracsayisi);
}

void AracBilgisiYazdirma(Otopark arac)
{
    printf("\n********************\n");
    printf("Arac ID: %d\n", arac.id);
    printf("Arac Giris Tarihi: %d:%d:%d\n", arac.giris_saati->tm_hour, arac.giris_saati->tm_min, arac.giris_saati->tm_sec);
    printf("Arac Plakasi: %s", arac.aracBilgisi.plaka);
    printf("Arac Modeli: %s", arac.aracBilgisi.model);
    printf("Arac Rengi: %s", arac.aracBilgisi.renk);
    printf("********************\n");
}

void OtomatikKayit()
{
    AracBilgisi aracBilgisi;

    strcpy(aracBilgisi.model, "BMW\n");
    strcpy(aracBilgisi.plaka, "45 BMW 45\n");
    strcpy(aracBilgisi.renk, "Siyah\n");
    AracKayit(aracBilgisi);

    strcpy(aracBilgisi.model, "MERCEDES\n");
    strcpy(aracBilgisi.plaka, "34 ASS 34\n");
    strcpy(aracBilgisi.renk, "Beyaz\n");
    AracKayit(aracBilgisi);

    strcpy(aracBilgisi.model, "AUDI\n");
    strcpy(aracBilgisi.plaka, "35 AUDI 35\n");
    strcpy(aracBilgisi.renk, "Siyah\n");
    AracKayit(aracBilgisi);

    strcpy(aracBilgisi.model, "FERRARI\n");
    strcpy(aracBilgisi.plaka, "21 AA 21\n");
    strcpy(aracBilgisi.renk, "Kirmizi\n");
    AracKayit(aracBilgisi);

    strcpy(aracBilgisi.model, "BMW\n");
    strcpy(aracBilgisi.plaka, "06 BMW 06\n");
    strcpy(aracBilgisi.renk, "Beyaz\n");
    AracKayit(aracBilgisi);
}

void AraclariListele()
{
    for (int i = 0; i < aracsayisi; i++)
    {
        AracBilgisiYazdirma(otopark[i]);
    }
}

void AracEkle()
{
    AracBilgisi aracBilgisi;

    printf("Arac Plakasini Giriniz: ");
    getchar();
    fgets(aracBilgisi.plaka, sizeof aracBilgisi.plaka, stdin);

    printf("Arac Modelini Giriniz: ");
    fgets(aracBilgisi.model, sizeof aracBilgisi.model, stdin);

    printf("Arac Rengini Giriniz: ");
    fgets(aracBilgisi.renk, sizeof aracBilgisi.renk, stdin);

    AracKayit(aracBilgisi);
}
