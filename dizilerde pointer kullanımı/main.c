#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int diziSayilar[10], diziCift[10], diziTek[10];
    int *diziPtr = &diziSayilar[0];
    int *tekPtr = &diziTek[0];
    int *ciftPtr = &diziCift[0];

    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {
        *(diziPtr + i) = 1 + rand() % 99;
    }

    int iTek = 0, iCift = 0;
    for (int i = 0; i < 10; i++)
    {
        if (*(diziPtr + i) % 2 == 0)
        {
            *(ciftPtr + iCift) = *(diziPtr + i);
            iCift++;
        }
        else
        {
            *(tekPtr + iTek) = *(diziPtr + i);
            iTek++;
        }
    }

    printf("********** Tek  Sayilar **********\n");
    for (int i = 0; i < iTek; i++)
    {
        printf("%d\t", *(tekPtr + i));
    }

    printf("\n********** Cift Sayilar **********\n");
    for (int i = 0; i < iCift; i++)
    {
        printf("%d\t", *(ciftPtr + i));
    }

    printf("\n");
}