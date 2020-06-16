#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HP 100
#define DOSYA_ADI "log.txt"

int AralarindaAsalSayi(int, int);
int *EngelEkleme(int, int *);
int BubbleSort(int *, int);
FILE *txtOpen(char[], char[]);

int main(void)
{
    srand(time(NULL));
    int hp = HP;
    int engelSayisi;

    int parkurUzunlugu = 50 + rand() % 50;

    int *engeller = EngelEkleme(parkurUzunlugu, &engelSayisi);

    BubbleSort(engeller, engelSayisi);

    FILE *txtLog;
    txtLog = txtOpen(DOSYA_ADI, "w");

    printf("Yarisma Basladi !!!\nYarismaci HP = 100\n");
    fprintf(txtLog, "Yarisma Basladi !!!\nYarismaci HP = 100\n");

    for (int i = 0; i < engelSayisi; i++)
    {
        printf("Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n", engeller[i]);
        fprintf(txtLog, "Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n", engeller[i]);

        printf("%d. metrede bir engel var. %d ve %d aralarinda", engeller[i], hp, engeller[i]);
        fprintf(txtLog, "%d. metrede bir engel var. %d ve %d aralarinda", engeller[i], hp, engeller[i]);

        int asalDurumu = AralarindaAsalSayi(engeller[i], hp);

        if (asalDurumu)
        {
            hp -= engeller[i];
            printf(" asaldir.\n");
            fprintf(txtLog, " asaldir.\n");
        }
        else
        {
            printf(" asal değildir.\n");
            fprintf(txtLog, " asal değildir.\n");
        }

        printf("Yarismaci HP: %d\n", hp);
        fprintf(txtLog, "Yarismaci HP: %d\n", hp);

        if (hp < 1)
        {
            printf("Uzgunum !!! Yarismayi Tamamlayamadin.\n");
            fprintf(txtLog, "Uzgunum !!! Yarismayi Tamamlayamadin.\n");
            return 0;
        }
    }
    printf("Tebrikler !!! Yarismayi %d HP ile bitirdiniz.\n", hp);
    fprintf(txtLog, "Tebrikler !!! Yarismayi %d HP ile bitirdiniz.\n", hp);

    fclose(txtLog);
}

int AralarindaAsalSayi(int s1, int s2)
{
    int asal = 1;

    if (s2 > s1)
    {
        int temp = s1;
        s1 = s2;
        s2 = temp;
    }

    for (int i = 2; i < (s1 - 1); i++)
    {
        if (s1 % i == 0 && s2 % i == 0)
        {
            asal = 0;
            break;
        }
    }

    return asal;
}

int *EngelEkleme(int parkurUzunlugu, int *engelSayisi)
{
    *engelSayisi = 2 + rand() % 3;
    int *engeller;

    engeller = (int *)calloc(*engelSayisi, sizeof(int));

    for (int i = 0; i < *engelSayisi; i++)
    {
        int engel = 0;
        do
        {
            engel = 5 + rand() % parkurUzunlugu;
            for (int j = 0; j < *engelSayisi; j++)
            {
                if (engeller[j] == engel)
                    engel = 0;
            }
        } while (engel == 0);

        engeller[i] = engel;
    }

    return engeller;
}

int BubbleSort(int *dizi, int diziBoyutu)
{
    for (int i = 0; i < diziBoyutu - 1; i++)
    {
        for (int j = 0; j < diziBoyutu - i - 1; j++)
        {
            if (dizi[j] > dizi[j + 1])
            {
                int temp = dizi[j];
                dizi[j] = dizi[j + 1];
                dizi[j + 1] = temp;
            }
        }
    }
}

FILE *txtOpen(char dosyaYolu[], char x[])
{
    FILE *fp;

    if ((fp = fopen(dosyaYolu, x)) == NULL)
    {
        printf("%s Dosyasi Acilmadi...\n", dosyaYolu);
        exit(1);
    }

    return fp;
}
