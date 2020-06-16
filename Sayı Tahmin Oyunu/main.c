#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int sayi = 5 + rand() % 500;

    int puan = 0, i = 1;
    while (i != 6)
    {
        int tahmin;
        printf("%d. Tahmininizi Giriniz: ", i);
        scanf("%d", &tahmin);

        if (tahmin < 5 || tahmin > 500)
        {
            printf("Lutfen dogru aralikta sayi giriniz !\n\n");
            continue;
        }

        if (tahmin == sayi)
        {
            puan += 100;
            printf("\nTebrik ederiz !\n%d. Tahminde dogru cevabi verdiniz. Puanınız: %d\n\n", i, puan);
            return 0;
        }
        else if (tahmin < sayi)
        {
            puan -= 20;
            printf("\nTahmininiz, tutulan sayidan küçük bir sayi...\n\n");
        }
        else if (tahmin > sayi)
        {
            puan -= 20;
            printf("\nTahmininiz, tutulan sayidan büyük bir sayi...\n\n");
        }

        i++;
    }

    printf("Kaybettiniz !\nTahmin edilmeye calisilan sayi: %d\n\n", sayi);
    return 0;
}