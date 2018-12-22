#include <stdio.h>
#include <stdlib.h>

/* Parit sayısı girildiği zaman ataması yapılacak değişkene atadık. Bütün fonksiyonlarda geçerli olması için fonksiyon dışında tanımlama yaptık. */
int parti_sayisi;

/* Oluşturulan fonksiyonların prototipleri. */
void parti_adi_duzenleme(char parti_adi[]);
void siralama(long long int oy[], char ad[]);
void mv_sayisi(long long int oy[], int t_kontenjan, int kontenjan[]);
void il_tanimlama(char parti_adi[], int il_plakasi, char t_parti_adi[],long long int t_oy[], int t_kontenjan[], int birincilik[], int sifir_mv[]);
void Turkiye_geneli(char parti_adi[], long long int oy[], int kontenjan[], char t_parti_adi[], long long int t_oy[], int t_kontenjan[],int birincilik[],int sifir_mv[]);
void Turkiye_geneli_cikti(char t_parti_adi[], long long int t_oy[], int t_kontenjan[], int birincilik[], int sifir_mv[]);

int main()
{
	int il_plakasi;

	/* Parti sayısının girilmesini istiyoruz ve 2 ile 25 arasında olamasını sağlıyoruz. */
	while(1)
	{
		printf("Lutfen Parti Sayisini Giriniz: ");
		scanf("%d",&parti_sayisi);
		if(parti_sayisi <= 25 && parti_sayisi > 1)
			break;
	}

	/* İstatistik verileri için ve seçime katılacak olan partilerin oylarından kaynaklı */
	char parti_adi[parti_sayisi], t_parti_adi[parti_sayisi];
	int t_kontenjan[parti_sayisi], birincilik[parti_sayisi], sifir_mv[parti_sayisi];
	long long int t_oy[parti_sayisi];

	/* İstatistik verilerinin içine değer olarak 0 atıyoruz. */
	for(int i=0; i<parti_sayisi; i++)
	{
		t_oy[i]=0;
		t_kontenjan[i]=0;
		birincilik[i]=0;
		sifir_mv[i]=0;
	}

	/* Sonsuz döngü içinde illerin sürekli girilmesini sağlıyoruz taki il plakası 0 girilene kadar. */
	do
	{
		/* İl plakasının girilmesini sağlıyoruz. */
		printf("\nIlin Plaka Kodunu Giriniz(Baska Il Yok ise 0 Basin): ");
		scanf("%d",&il_plakasi);

		/* İl plakasına göre fonksiyon çağrılır ve 0 girilmesi durumunda ülke geneli istatistik tablosu çıktısı verilir. */
		switch(il_plakasi)
		{
			case 0:
				Turkiye_geneli_cikti(t_parti_adi, t_oy, t_kontenjan,birincilik,sifir_mv);
				break;
			default:
				parti_adi_duzenleme(parti_adi);
				il_tanimlama(parti_adi, il_plakasi, t_parti_adi, t_oy, t_kontenjan, birincilik, sifir_mv);
				break;
		}
	}while(il_plakasi != 0);
}

/* Girilen parti sayısına göre değişkene parti isimlerini atıyoruz. */
void parti_adi_duzenleme(char parti_adi[])
{
	char harfler[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','X','Y','Z'};

	for(int i = 0; i<parti_sayisi; i++)
		parti_adi[i]=harfler[i];
}

/* İl istatistik tablosunda girilen oy dağılımlarına göre sıralama yapıyoruz. */
void siralama(long long int oy[], char ad[])
{
	long long int gecici_oy;
	char gecici_ad;
	for(int i=0; i<parti_sayisi; i++)
	{
  	     	for(int j=0; j<parti_sayisi-1-i; j++)
		{
            		if(oy[j] < oy[j+1])
			{
                		gecici_oy = oy[j];
                		oy[j] = oy[j+1];
                		oy[j+1] = gecici_oy;

				gecici_ad=ad[j];
				ad[j] = ad[j+1];
				ad[j+1] = gecici_ad;
            		}
        	}
    	}
}

/* Girilen oy dağılımlarına göre milletvekili dağılımları hesaplanıyor. */
void mv_sayisi(long long int oy[], int t_kontenjan, int kontenjan[])
{
	long long int oylar[parti_sayisi];
	int mv_indis,gecici=0;

	for(int i=0; i<parti_sayisi; i++)
	{
		oylar[i]=oy[i];
		kontenjan[i]=0;
	}

	for(int i=0; i<t_kontenjan; i++)
	{
		for(int j=0; j<parti_sayisi; j++)
		{
			if(oylar[j]>gecici)
			{
				gecici = oylar[j];
				mv_indis = j;
			}
		}
		kontenjan[mv_indis]++;
		oylar[mv_indis] = oylar[mv_indis] / 2;
		gecici=0;
	}
}

/* İl bilgilerinin girilmesi ve ülke geneli istatistik bilgilerinin hesaplanması için gerekli işlemlerin yapıldığı fonksiyon. */
void il_tanimlama(char parti_adi[], int il_plakasi, char t_parti_adi[], long long int t_oy[], int t_kontenjan[], int birincilik[], int sifir_mv[])
{
	int m_kontenjan, kontenjan[parti_sayisi];
	long long oy[parti_sayisi], toplam_oy=0;

	printf("Ilin Milletvekili Kontenjanini Giriniz: ");
	scanf("%d",&m_kontenjan);
	printf("\n");

	for(int i=0; i<parti_sayisi; i++)
	{
		printf("%c Partisi'nin Oy Sayisini Giriniz: ",parti_adi[i]);
		scanf("%lld",&oy[i]);
		toplam_oy += oy[i];
	}

	printf("\n\nIl Plaka Kodu: %d\n",il_plakasi);
	printf("Milletvekili Kontenjani: %d\n",m_kontenjan);
	printf("Geçerli Oy Sayisi: %lld\n\n",toplam_oy);

	siralama(oy, parti_adi);
	mv_sayisi(oy, m_kontenjan, kontenjan);

	printf("\t\tOy Sayisi\tOy Yuzde\tMV Sayisi\n");
	printf("\t\t---------\t--------\t---------\n");
	for(int i=0; i<parti_sayisi; i++)
		printf("%c Partisi \t %lld \t\t %.2f \t\t %d\n",parti_adi[i],oy[i],((float)(oy[i]*100)/toplam_oy),kontenjan[i]);

	Turkiye_geneli(parti_adi, oy, kontenjan, t_parti_adi, t_oy, t_kontenjan, birincilik, sifir_mv);
}
/* Ülke geneli istatistik hesaplanması için gerekli fonksiyon. */
void Turkiye_geneli(char parti_adi[], long long int oy[], int kontenjan[], char t_parti_adi[], long long int t_oy[], int t_kontenjan[], int birincilik[], int sifir_mv[])
{
	parti_adi_duzenleme(t_parti_adi);

	for(int i=0; i<parti_sayisi; i++)
	{
		for (int j=0; j<parti_sayisi; j++)
		{
			if(t_parti_adi[i] == parti_adi[j])
			{
				t_kontenjan[i]+=kontenjan[j];
				t_oy[i]+=oy[j];
				if(j == 0)
					birincilik[i]++;
				if(t_kontenjan[i] == 0)
					sifir_mv[i]++;
				break;
			}
		}
	}
}

/* Ülke geneli istatistik tablosunun çıktısı. */
void Turkiye_geneli_cikti(char t_parti_adi[], long long int t_oy[], int t_kontenjan[], int birincilik[], int sifir_mv[])
{
	int kontenjan=0, gecici_oy, gecici_ad, gecici_kontenjan, gecici_birincilik, gecici_sifir_mv;
	long long int oy=0;
	for(int i=0; i<parti_sayisi; i++)
	{
		kontenjan+=t_kontenjan[i];
		oy+=t_oy[i];
	}

	for(int i=0; i<parti_sayisi; i++)
	{
  	     	for(int j=0; j<parti_sayisi-1-i; j++)
		{
            		if(t_kontenjan[j] < t_kontenjan[j+1])
			{
                		gecici_oy = t_oy[j];
                		t_oy[j] = t_oy[j+1];
                		t_oy[j+1] = gecici_oy;

				gecici_ad=t_parti_adi[j];
				t_parti_adi[j] = t_parti_adi[j+1];
				t_parti_adi[j+1] = gecici_ad;

				gecici_kontenjan = t_kontenjan[j];
				t_kontenjan[j] = t_kontenjan[j+1];
				t_kontenjan[j+1] = gecici_kontenjan;

				gecici_birincilik = birincilik[j];
				birincilik[j] = birincilik[j+1];
				birincilik[j+1] = gecici_birincilik;

				gecici_sifir_mv = sifir_mv[j];
				sifir_mv[j] = sifir_mv[j+1];
				sifir_mv[j+1] = gecici_sifir_mv;
            		}
        	}
    	}

	printf("\nTurkiye Geneli\n");
	printf("Milletvekili Kontenjani: %d\n",kontenjan);
	printf("Toplam Gecerli Oy Sayisi: %lld\n\n",oy);
	printf("\t\tOy Sayisi\tOy Yuzdesi\tMV Sayisi\tMV Yuzdesi\tIl 1. lik Sayisi\t0 MV Il Sayisi\n");
	printf("\t\t---------\t----------\t---------\t----------\t----------------\t--------------\n");
	for(int i=0; i<parti_sayisi; i++)
		printf("%c Partisi\t %lld\t\t %.2f\t\t %d\t\t %.2f\t\t %d\t\t\t %d\n",t_parti_adi[i],t_oy[i],((float)(t_oy[i]*100)/oy),t_kontenjan[i],((float)(t_kontenjan[i]*100)/kontenjan),birincilik[i],sifir_mv[i]);
	printf("\nIktidar Partisi: %c Partisi\n",t_parti_adi[0]);
	printf("Ana Muhalefet Partisi: %c Partisi\n",t_parti_adi[1]);
}
