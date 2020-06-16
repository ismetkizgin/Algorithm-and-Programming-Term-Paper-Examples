#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int **matrisOlustur(int satirSayisi, int sutunSayisi);
int **matrisRandomDoldur(int satirSayisi, int sutunSayisi, int **matris);
int **matrisSirala(int satirSayisi, int sutunSayisi, int **matris);
int **matrisTranspoze(int satirSayisi, int sutunSayisi, int **matris);
FILE *txtOpen(char dosyaYolu[], char x[]);
void transpozeDosyasiniYaz(int satirSayisi, int sutunSayisi, int **matris);
int kaprekarKontrol(int sayi);
void kaprekarDosyasiniYaz(int satirSayisi, int sutunSayisi, int **matris);

int main(void)
{
    int **matris;
    int satirSayisi, sutunSayisi;

    printf("Satir sayisi giriniz: ");
    scanf("%d", &satirSayisi);
    printf("Sutun sayisi giriniz: ");
    scanf("%d", &sutunSayisi);

    matris = matrisOlustur(satirSayisi, sutunSayisi);
    matris = matrisRandomDoldur(satirSayisi, sutunSayisi, matris);
    matris = matrisSirala(satirSayisi, sutunSayisi, matris);

    for (int i = 0; i < satirSayisi; i++)
    {
        for (int j = 0; j < sutunSayisi; j++)
            printf("%d ", matris[i][j]);

            printf("\n");
    }
    // transpozeDosyasiniYaz(satirSayisi, sutunSayisi, matris);
    // kaprekarDosyasiniYaz(satirSayisi, sutunSayisi, matris);

    return 0;
}

int **matrisOlustur(int satirSayisi, int sutunSayisi)
{
    int **matris;
    matris = (int **)malloc(satirSayisi * sizeof(int));
    if (matris == NULL)
        printf("Yetersiz bellek!");

    for (int i = 0; i < satirSayisi; i++)
    {
        matris[i] = malloc(sutunSayisi * sizeof(int));
        if (matris[i] == NULL)
            printf("Yetersiz bellek!");
    }

    return matris;
}

int **matrisRandomDoldur(int satirSayisi, int sutunSayisi, int **matris)
{
    srand(time(NULL));
    for (int i = 0; i < satirSayisi; i++)
    {
        for (int j = 0; j < sutunSayisi; j++)
            matris[i][j] = 5 + rand() % 40000;
    }

    return matris;
}

int **matrisSirala(int satirSayisi, int sutunSayisi, int **matris)
{
    int temp;
    for (int i = 0; i < satirSayisi * sutunSayisi - 1; i = i + 1)
        for (int j = 0; j < satirSayisi * sutunSayisi - 1 - i; j = j + 1)
            if (matris[j / sutunSayisi][j % sutunSayisi] > matris[(j + 1) / sutunSayisi][(j + 1) % sutunSayisi])
            {
                temp = matris[j / sutunSayisi][j % sutunSayisi];
                matris[j / sutunSayisi][j % sutunSayisi] = matris[(j + 1) / sutunSayisi][(j + 1) % sutunSayisi];
                matris[(j + 1) / sutunSayisi][(j + 1) % sutunSayisi] = temp;
            }

    return matris;
}

int **matrisTranspoze(int satirSayisi, int sutunSayisi, int **matris)
{
    int **matrisT;
    matrisT = matrisOlustur(satirSayisi, sutunSayisi);

    for (int i = 0; i < satirSayisi; i++)
    {
        for (int j = 0; j < sutunSayisi; j++)
        {
            matrisT[j][i] = matris[i][j];
        }
    }
    return matrisT;
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

void transpozeDosyasiniYaz(int satirSayisi, int sutunSayisi, int **matris)
{
    int **matrisT;

    matrisT = matrisOlustur(satirSayisi, sutunSayisi);
    matrisT = matrisTranspoze(satirSayisi, sutunSayisi, matris);

    FILE *txtTranspoze;
    txtTranspoze = txtOpen("transpoze.txt", "w");

    fprintf(txtTranspoze, "***** Matris *****\n");
    for (int i = 0; i < satirSayisi; i++)
    {
        for (int j = 0; j < sutunSayisi; j++)
        {
            fprintf(txtTranspoze, "%2d\t", matris[i][j]);
        }
        fprintf(txtTranspoze, "\n");
    }

    fprintf(txtTranspoze, "\n\n***** Transpoze Matris *****\n");
    for (int i = 0; i < satirSayisi; i++)
    {
        for (int j = 0; j < sutunSayisi; j++)
        {
            fprintf(txtTranspoze, "%2d\t", matrisT[i][j]);
        }
        fprintf(txtTranspoze, "\n");
    }
    fclose(txtTranspoze);

    printf("\nYazdirma işlemi tamam!\n");
}

int kaprekarKontrol(int sayi)
{
    if (sayi == 1)
        return 1;
    int sqr_n = pow(sayi, 2);
    int ctr_digits = 0;
    while (sqr_n)
    {
        ctr_digits++;
        sqr_n /= 10;
    }
    sqr_n = pow(sayi, 2);
    for (int r_digits = 1; r_digits < ctr_digits; r_digits++)
    {
        int eq_parts = pow(10, r_digits);

        if (eq_parts == sayi)
            continue;
        int sum = sqr_n / eq_parts + sqr_n % eq_parts;
        if (sum == sayi)
            return 1;
    }
    return 0;
}

void kaprekarDosyasiniYaz(int satirSayisi, int sutunSayisi, int **matris)
{
    FILE *txtKaprekar;
    txtKaprekar = txtOpen("kaprekar.txt", "w");
    int state = 0;
    for (int i = 0; i < satirSayisi; i++)
    {
        for (int j = 0; j < sutunSayisi; j++)
        {
            if (kaprekarKontrol(matris[i][j]))
            {
                state = 1;
                fprintf(txtKaprekar, "%d \n", matris[i][j]);
            }
        }
    }
    fclose(txtKaprekar);

    if (!state)
    {
        remove("kaprekar.txt");
        printf("\nKaprekar Yok !\n");
    }
}
