#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define bDosyasi "BireyselMusteri.txt"
#define tDosyasi "TicariMusteri.txt"
#define hDosyasi "Hesaplar.txt"
#define rDosyasi "Rapor.txt"
#define dDosyasi "Dekont.txt"

typedef enum
{
	Ekle,
	Guncelle,
	Sil,
	Musteri,
	Hesap,
	ParaYatirma,
	ParaCekme,
	ParaHavale
}islemTuru;

typedef struct
{
	int no;
	char ad[50];
	char soyad[50];
	int tipi;
}musteriBilgileri;

typedef struct
{
	int mNo;
	int hNo;
	float bakiye;
}hesapBilgileri;

typedef struct
{
	int hNo;
	int havaleNo;
	musteriBilgileri pBilgi;
	time_t tarih;
	islemTuru islem;
	float islemTutari;
}raporBilgileri;

FILE *txtOpen(char[],char[]);
int yeniNo(islemTuru);

//Müşteri işlemleri fonksiyonları...

int musteriVarlikSorgusu(int);
musteriBilgileri *musteriBilgiGirisi(islemTuru);
void musteriBilgiCiktisi(musteriBilgileri *);
int musteriNoSorgu(int *, int *);

void musteriListesi();
void musteriEkle(musteriBilgileri *);
void musteriSil(islemTuru, ...);
void musteriGuncelle();
void musteriIslemleri();

//Banka işlemleri fonksiyonları...

int hesapVarlikSorgusu(int);
hesapBilgileri *hesaplar(int, int *);
int gunlukLimit(int);

void hesapOzet(int);
void hesapKapatma(int);
void paraHavale(musteriBilgileri *);
void hesapIslemleri(islemTuru, musteriBilgileri *);
void hesapListesi(int);
void hesapAcma(int);
void bankaIslemleri();

//Rapor işlemleri fonksiyonları...
void raporIslemleri(islemTuru, int);
void rapor();

int main()
{
	srand(time(0));
	while(1)
	{
		int islem;
		printf("\n1. Musteri Islemleri\n2. Banka Islemleri\n3. Gelir-Gider Raporu\n4. Cikis\n\n");

		printf("Lutfen bir islem seciniz: ");
		scanf("%d",&islem);

		switch(islem)
		{
			case 1:
				musteriIslemleri();
				break;
			case 2:
				bankaIslemleri();
				break;
			case 3:
				rapor();
				break;
			case 4:
				exit(1);
				break;
			default:
				printf("Yanlis islem secimi yaptiniz lutfen dogru islem seciniz...\n\n");
				break;
		}
	}
}

FILE *txtOpen(char dosyaYolu[],char x[])
{
	FILE *fp;

	if((fp = fopen(dosyaYolu, x)) == NULL)
	{
		printf("%s Dosyasi Acilmadi...\n",dosyaYolu);
		exit(1);
	}

	return fp;
}

int yeniNo(islemTuru islem)
{
	int random;
	while(1)
	{
		random = rand();
		if(islem == Musteri && musteriVarlikSorgusu(random) == 0)
			break;
		else if(hesapVarlikSorgusu(random) == 0)
			break;
	}

	return random;
}

//Müşteri işlem fonksiyonları...
int musteriVarlikSorgusu(int mNo)
{
	musteriBilgileri  *pBilgi;
	pBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));

	FILE *fp;

	fp = txtOpen(bDosyasi,"rb");
	while(fread(pBilgi, sizeof(*pBilgi), 1, fp) == 1)
	{
		if(pBilgi->no == mNo)
			return 1;
	}

	fp = txtOpen(tDosyasi,"rb");
	while(fread(pBilgi, sizeof(*pBilgi), 1, fp) == 1)
	{
		if(pBilgi->no == mNo)
			return 2;
	}

	fclose(fp);
	return 0;
}

musteriBilgileri *musteriBilgiGirisi(islemTuru islem)
{
	musteriBilgileri *pBilgi;
	pBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));

	if(islem == Ekle)
		pBilgi->no = yeniNo(Musteri);

	printf("Lutfen Adinizi Giriniz: ");
	getchar();
	gets(pBilgi->ad);
	printf("Lutfen Soyadinizi Giriniz: ");
	gets(pBilgi->soyad);
	while(1)
	{
		printf("1. Bireysel Musteri\n2. Ticari Musteri\n\nLutfen bir Musteri Tipi Seciniz: ");
		scanf("%d",&pBilgi->tipi);
		if(pBilgi->tipi == 1 || pBilgi->tipi == 2)
			break;
		else
			printf("Dogru bir Musteri Tipi seciniz lutfen...");
	}

	return pBilgi;
}

void musteriBilgiCiktisi(musteriBilgileri *pBilgi)
{
	printf("\nMusteri Numarasi: %d\n",pBilgi->no);
	printf("Musteri Adi: %s\n",pBilgi->ad);
	printf("Musteri Soyadi: %s\n",pBilgi->soyad);

	if(pBilgi->tipi == 1)
		printf("Musteri Tipi: Bireysel Musteri\n");
	else
		printf("Musteri Tipi: Ticari Musteri\n");
}

void musteriIslemleri()
{
	musteriBilgileri *pBilgi;
	int islem;
	do
	{
		printf("\n********** Musteri Islemleri *********\n\n1. Musteri Listesi\n2. Musteri Ekle\n3. Musteri Guncelle\n4. Musteri Sil\n5. Onceki Menuye Geri Don\n6. Cikis\n\n");

		printf("Lutfen bir Musteri Islemi seciniz: ");
		scanf("%d",&islem);

		switch(islem)
		{
			case 1:
				musteriListesi();
				break;
			case 2:
				pBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));
				pBilgi = musteriBilgiGirisi(Ekle);
				musteriEkle(pBilgi);
				break;
			case 3:
				musteriGuncelle();
				break;
			case 4:
				musteriSil(Sil);
				break;
			case 5:
				break;
			case 6:
				exit(1);
				break;
			default:
				printf("Yanlis islem secimi yaptiniz lutfen dogru islem seciniz...\n\n");
				break;
		}
	}while(islem != 5);
}

void musteriListesi()
{
	int islem;
	FILE *fp;
	musteriBilgileri *pBilgi;
	pBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));

	do
	{
		printf("\n*********** Musteri Listeleri *********\n\n1. Bireysel Musteri Listesi\n2. Ticari Musteri Listesi\n3. Onceki Menuye Geri Don\n4. Cikis\n\n");

		printf("Lutfen bir Musteri Islemi seciniz: ");
		scanf("%d",&islem);

		switch(islem)
		{
			case 1:
				fp = txtOpen(bDosyasi,"rb");
				printf("\n********************\n");
				while(fread(pBilgi, sizeof(*pBilgi), 1, fp) == 1)
				{
					musteriBilgiCiktisi(pBilgi);
				}
				printf("\n********************\n");
				fclose(fp);
				break;
			case 2:
				fp = txtOpen(tDosyasi,"rb");
				printf("\n********************\n");
				while(fread(pBilgi, sizeof(*pBilgi), 1, fp) == 1)
				{
					musteriBilgiCiktisi(pBilgi);
				}
				printf("\n********************\n");
				fclose(fp);
				break;
			case 3:
				break;
			case 4:
				exit(1);
				break;
			default:
				printf("Yanlis islem secimi yaptiniz lutfen dogru islem seciniz...\n\n");
				break;
		}
	}while(islem != 3);
}

void musteriEkle(musteriBilgileri *pBilgi)
{
	FILE *fp;

	if(pBilgi->tipi == 1)
		fp = txtOpen(bDosyasi,"ab");
	else
		fp = txtOpen(tDosyasi,"ab");

	if(fwrite(pBilgi, sizeof(*pBilgi), 1, fp) !=1)
	{
		printf("Dosya yazma hatasi...\n");
		exit(1);
	}

	fclose(fp);
	printf("\nMusteri Kayit Isleminiz Basarili Bir Sekilde Gerceklestirilmistir...\n");
}

int musteriNoSorgu(int *mNo, int *mTipi)
{
	int no, tipi;
	while(1)
	{
		printf("Islem Yapilacak Musteri No (Cikis: 0): ");
		scanf("%d", &no);

		if(no == 0)
			return 0;
		else if((tipi = musteriVarlikSorgusu(no)) != 0)
			break;
		else
			printf("Boyle bir musteri numarasi bulunmamaktadir. Lutfen musteri numaranizi kontrol edip tekrar giriniz veya cikmak icin 0 giriniz...\n\n");
	}

	*mNo = no;
	*mTipi = tipi;
	return 1;
}

void musteriSil(islemTuru islem, ...)
{
	musteriBilgileri *pBilgi;
	pBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));
	int mTipi,mNo;

	if(islem == Sil)
		if(!musteriNoSorgu(&mNo,&mTipi))
			return;
	else
	{
		va_list no;
		va_start(no,1);
		mNo = va_arg(no, int);
		va_end(no);

		mTipi = musteriVarlikSorgusu(mNo);
	}

	FILE *fp, *temp;
	char *dosya;

	if(mTipi == 1)
	{
		dosya = (char *) malloc(sizeof(char)* strlen(bDosyasi));
		strcpy(dosya, bDosyasi);
	}
	else
	{
		dosya = (char *) malloc(sizeof(char)* strlen(tDosyasi));
		strcpy(dosya, tDosyasi);
	}

	fp = txtOpen(dosya, "rb+");
	temp = txtOpen("temp.txt","wb");

	while(fread(pBilgi, sizeof(*pBilgi), 1, fp) == 1)
	{
		if(pBilgi->no != mNo)
			if(fwrite(pBilgi, sizeof(*pBilgi), 1, temp) !=1)
			{
				printf("Dosya yazma hatasi...\n");
				exit(1);
			}
	}
	fclose(fp);
	fclose(temp);
	remove(dosya);
	rename("temp.txt", dosya);

	if(islem == Sil)
		printf("\nSilme Isleminiz Basarili Bir Sekilde Gerceklestirilmistir...\n");
}

void musteriGuncelle()
{
	musteriBilgileri *pBilgi,*pgBilgi;
	pBilgi = pgBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));
	int mTipi,mNo;
	char *dosya;

	if(!musteriNoSorgu(&mNo,&mTipi))
		return;

	pgBilgi = musteriBilgiGirisi(Guncelle);
	pgBilgi->no = mNo;

	FILE *fp, *fpD;

	if(mTipi == 1)
	{
		dosya = (char *) malloc(sizeof(char)* strlen(tDosyasi));
		strcpy(dosya, tDosyasi);
		fp = fopen(bDosyasi,"rb+");
	}
	else
	{
		dosya = (char *) malloc(sizeof(char)* strlen(bDosyasi));
		strcpy(dosya, bDosyasi);
		fp = fopen(tDosyasi,"rb+");
	}

	for(int i=0; fread(pBilgi, sizeof(*pBilgi), 1, fp) == 1; i++)
	{
		if(pBilgi->no == pgBilgi->no)
		{
			if(pBilgi->tipi == pgBilgi->tipi)
			{
				fseek(fp, i*sizeof(*pgBilgi), SEEK_SET);
				if(fwrite(pgBilgi, sizeof(*pgBilgi), 1, fp) != 1)
				{
					printf("Guncelleme sirasinda dosya yazma hatasi olustu lutfen bir daha deneyin...\n\n");
					exit(1);
				}
				else
					break;
			}
			else
			{
				musteriSil(Guncelle, pBilgi->no);
				musteriEkle(pgBilgi);
			}
		}
	}
	fclose(fp);

	printf("\nMusteri Bilgileri Guncellenmistir Basarili Bir Sekilde...\n");
}

//Banka işlem fonksiyonları
int hesapVarlikSorgusu(int hNo)
{
	hesapBilgileri  *pHesap;
	pHesap = (hesapBilgileri *) malloc(sizeof(hesapBilgileri));

	FILE *fp;

	fp = txtOpen(hDosyasi,"rb");
	while(fread(pHesap, sizeof(*pHesap), 1, fp) == 1)
	{
		if(pHesap->hNo == hNo)
			return 1;
	}

	fclose(fp);
	return 0;
}

hesapBilgileri *hesaplar(int mNo, int *hesapSayisi)
{
	hesapBilgileri *pHesap, *temp;
	pHesap = (hesapBilgileri *) malloc(sizeof(hesapBilgileri));

	FILE *fp;
	fp = txtOpen(hDosyasi,"rb");

	int i = 0;
	while(fread(pHesap, sizeof(*pHesap), 1, fp) == 1)
	{
		if(pHesap->mNo == mNo)
			i++;
	}

	*hesapSayisi = i;
	temp = (hesapBilgileri *) malloc(sizeof(hesapBilgileri) * i);
	rewind(fp);
	i = 0;

	while(fread(pHesap, sizeof(*pHesap), 1, fp) == 1)
	{
		if(pHesap->mNo == mNo)
		{
			(temp + i)->mNo = pHesap->mNo;
			(temp + i)->hNo = pHesap->hNo;
			(temp + i)->bakiye = pHesap->bakiye;
			i++;
		}
	}
	return temp;
}

int gunlukLimit(int hNo)
{
	int toplam = 0;
	raporBilgileri *pRapor;
	pRapor = (raporBilgileri *) malloc(sizeof(raporBilgileri));
	time_t t = time(NULL);
	struct tm *tarih, *temp;
	temp = localtime(&t);

	FILE *fp;
	fp = txtOpen(dDosyasi,"rb");

	while(fread(pRapor, sizeof(*pRapor), 1, fp) == 1)
	{
		if(pRapor->hNo == hNo || pRapor->islem != ParaHavale)
		{
			tarih = localtime(&pRapor->tarih);
			if(tarih->tm_mday == temp->tm_mday && tarih->tm_mon == temp->tm_mon && tarih->tm_year == temp->tm_year)
				toplam += pRapor->islemTutari;
		}
	}
	return toplam;
}

void bankaIslemleri()
{
	musteriBilgileri *pBilgi;
	pBilgi = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));

	if(!musteriNoSorgu(&pBilgi->no, &pBilgi->tipi))
		return;

	int islem;
	do
	{
		printf("\n********** Banka Islemleri *********\n\n1. Hesap Listesi\n2. Hesap Ac\n3. Para Cekme\n4. Para Yatirma\n5. Havale\n6. Hesap Ozeti\n7. Hesap Kapatma\n8. Onceki Menuye Geri Don\n9. Cikis\n\n");

		printf("Lutfen bir Musteri Islemi seciniz: ");
		scanf("%d",&islem);

		switch(islem)
		{
			case 1:
				hesapListesi(pBilgi->no);
				break;
			case 2:
				hesapAcma(pBilgi->no);
				break;
			case 3:
				hesapIslemleri(ParaCekme, pBilgi);
				break;
			case 4:
				hesapIslemleri(ParaYatirma, pBilgi);
				break;
			case 5:
				paraHavale(pBilgi);
				break;
			case 6:
				hesapOzet(pBilgi->no);
				break;
			case 7:
				hesapKapatma(pBilgi->no);
				break;
			case 8:
				break;
			case 9:
				exit(1);
				break;
			default:
				printf("Yanlis islem secimi yaptiniz lutfen dogru islem seciniz...\n\n");
				break;
		}
	}while(islem != 8);
}

void hesapListesi(int mNo)
{
	int hesapSayisi;
	hesapBilgileri *pHesap;
	pHesap = hesaplar(mNo, &hesapSayisi);

	printf("\n********************\n");
	for(int i=0; i<hesapSayisi; i++)
		printf("\n* %d. Hesap\nHesap No: %d\nBakiye: %.2f\n",(i + 1),(pHesap + i)->hNo, (pHesap + i)->bakiye);
	printf("\n********************\n");
}

void hesapAcma(int mNo)
{
	hesapBilgileri *pHesap;
	pHesap = (hesapBilgileri *) malloc(sizeof(hesapBilgileri));

	FILE *fp;

	pHesap->mNo = mNo;
	pHesap->hNo = yeniNo(Hesap);
	pHesap->bakiye = 0;

	fp = txtOpen(hDosyasi, "ab");

	if(fwrite(pHesap, sizeof(*pHesap), 1, fp) != 1)
	{
		printf("%s Dosyasina yazmada hata olustu...\n",hDosyasi);
		exit(1);
	}

	printf("\nMusteri No: %d\nHesap No: %d\nBakiye: %.2f\n\nHesap Acma Isleminiz Onaylanmistir Bilgileriniz Ust Kisimda Yer Almaktadir...\n",pHesap->mNo,pHesap->hNo,pHesap->bakiye);
	fclose(fp);
}

void hesapIslemleri(islemTuru islem, musteriBilgileri *pBilgi)
{
	int hesapSayisi;
	hesapBilgileri *temp, *pHesap;
	pHesap = (hesapBilgileri *) malloc(sizeof(hesapBilgileri));
	temp = hesaplar(pBilgi->no, &hesapSayisi);

	int hesapSecim;
	float tutar;

	printf("\nIslem Yapilacak Tutari Giriniz: ");
	scanf("%f",&tutar);

	while(1)
	{
		hesapListesi(pBilgi->no);
		printf("Lutfen bir hesap seciniz (Cikis: 0): ");
		scanf("%d", &hesapSecim);
		if(hesapSecim > 0 && hesapSecim <= hesapSayisi)
			if((temp + hesapSecim - 1)->bakiye < tutar && islem == ParaCekme)
				printf("\nIslem yapacaginiz hesapta yeterli tutar bulunmamaktadir. Yeni bir hesap seciniz veya Cikis icin 0 giriniz...\n");
			else
				break;
		else if(hesapSecim == 0)
			return;
		else
			printf("\nYanlis secim yaptiniz lutfen dogru bir hesap secimi yapiniz veya Cikis icin 0 giriniz...\n");
	}

	if(islem == ParaCekme)
		if((gunlukLimit((temp + hesapSecim - 1)->hNo) + tutar) >=750 && pBilgi->tipi == 1)
		{
			printf("\nGunluk para cekme limitine ulasilmistir.\n");
			return;
		}
		else if((gunlukLimit((temp + hesapSecim - 1)->hNo) + tutar) >=1500 && pBilgi->tipi == 2)
		{
			printf("\nGunluk para cekme limitine ulasilmistir.\n");
			return;
		}

	FILE *fp;
	fp = txtOpen(hDosyasi, "rb+");

	for(int i=0; fread(pHesap, sizeof(*pHesap), 1, fp) == 1; i++)
	{
		if(pHesap->hNo == (temp + hesapSecim - 1)->hNo)
		{
			if(islem == ParaYatirma)
				pHesap->bakiye += tutar;
			else
				pHesap->bakiye -= tutar;

			fseek(fp, i*sizeof(*pHesap), SEEK_SET);
			if(fwrite(pHesap, sizeof(*pHesap), 1, fp) != 1)
			{
				printf("Islem sirasinda dosya yazma hatasi olustu lutfen bir daha deneyin...\n\n");
				exit(1);
			}
		}
	}

	raporBilgileri *pRapor;
	pRapor = (raporBilgileri *) malloc(sizeof(raporBilgileri));

	pRapor->hNo = (temp + hesapSecim - 1)->hNo;
	if(islem == ParaCekme)
		pRapor->islem = ParaCekme;
	else
		pRapor->islem = ParaYatirma;
	pRapor->islemTutari = tutar;
	pRapor->tarih = time(NULL);
	fp = txtOpen(dDosyasi,"ar");
	if(fwrite(pRapor, sizeof(*pRapor), 1, fp) != 1)
	{
		printf("Islem sirasinda dosya yazma hatasi olustu lutfen bir daha deneyin...\n\n");
		exit(1);
	}
	fclose(fp);
	raporIslemleri(islem, tutar);
	printf("\nIsleminiz basarili bir sekilde gerceklestirilmistir...\n");
}

void paraHavale(musteriBilgileri *pBilgi)
{
	int hesapSayisi, hesapSecim, havaleNo;
	float tutar;
	hesapBilgileri *temp, *pHesap;
	pHesap = (hesapBilgileri *) malloc(sizeof(hesapBilgileri));
	temp = hesaplar(pBilgi->no, &hesapSayisi);

	printf("\nIslem Yapilacak Tutari Giriniz: ");
	scanf("%f",&tutar);

	while(1)
	{
		hesapListesi(pBilgi->no);
		printf("Lutfen bir hesap seciniz (Cikis: 0): ");
		scanf("%d", &hesapSecim);
		if(hesapSecim > 0 && hesapSecim <= hesapSayisi)
			if((temp + hesapSecim - 1)->bakiye < tutar)
				printf("\nIslem yapacaginiz hesapta yeterli tutar bulunmamaktadir. Yeni bir hesap seciniz veya Cikis icin 0 giriniz... \n");
			else
				break;
		else if(hesapSecim == 0)
			return;
		else
			printf("\nYanlis secim yaptiniz lutfen dogru bir hesap secimi yapiniz veya Cikis icin 0 giriniz...\n");
	}

	while(1)
	{
		printf("Havale edilecek hesap numarasini giriniz: ");
		scanf("%d",&havaleNo);

		if(hesapVarlikSorgusu(havaleNo))
			break;
		else if(havaleNo == 0)
			return;
		else
			printf("\nLutfen dogru bir hesap numarasi giriniz veya Cikis icin 0 giriniz\n");
	}

	FILE *fp;
	fp = txtOpen(hDosyasi, "rb+");

	for(int i=0; fread(pHesap, sizeof(*pHesap), 1, fp) == 1; i++)
	{
		if(pHesap->hNo == (temp + hesapSecim - 1)->hNo || pHesap->hNo == havaleNo)
		{
			if(pHesap->hNo == havaleNo)
				if(pBilgi->tipi == 1)
					pHesap->bakiye += tutar -  (float)(tutar * 2) / 100;
				else
					pHesap->bakiye += tutar;
			else
				pHesap->bakiye -= tutar;

			fseek(fp, i*sizeof(*pHesap), SEEK_SET);
			if(fwrite(pHesap, sizeof(*pHesap), 1, fp) != 1)
			{
				printf("Islem sirasinda dosya yazma hatasi olustu lutfen bir daha deneyin...\n\n");
				exit(1);
			}
		}
	}

	raporBilgileri *pRapor;
	pRapor = (raporBilgileri *) malloc(sizeof(raporBilgileri));
	musteriBilgileri *aktar;
	aktar = (musteriBilgileri *) malloc(sizeof(musteriBilgileri));

	if(pBilgi->tipi == 1)
		fp = txtOpen(bDosyasi,"rb");
	else
		fp = txtOpen(tDosyasi,"rb");

	while(fread(aktar, sizeof(*aktar), 1, fp) == 1)
	{
		if(pBilgi->no == aktar->no)
			break;
	}

	pRapor->hNo = (temp + hesapSecim - 1)->hNo;
	pRapor->islem = ParaHavale;
	pRapor->islemTutari = tutar;
	pRapor->tarih = time(NULL);
	pRapor->pBilgi = *aktar;
	pRapor->havaleNo = havaleNo;
	fp = txtOpen(dDosyasi,"ar");
	if(fwrite(pRapor, sizeof(*pRapor), 1, fp) != 1)
	{
		printf("Islem sirasinda dosya yazma hatasi olustu lutfen bir daha deneyin...\n\n");
		exit(1);
	}
	fclose(fp);
	if(pBilgi->tipi == 1)
		raporIslemleri(ParaHavale, tutar);
	printf("\nIsleminiz basarili bir sekilde gerceklestirilmistir...\n");
}

void hesapKapatma(int mNo)
{
	int hesapSayisi, hesapSecim;
	hesapBilgileri *temp, *pHesap;
	pHesap = (hesapBilgileri *) malloc(sizeof(hesapBilgileri));
	temp = hesaplar(mNo, &hesapSayisi);

	while(1)
	{
		hesapListesi(mNo);
		printf("Lutfen bir hesap seciniz (Cikis: 0): ");
		scanf("%d", &hesapSecim);
		if(hesapSecim > 0 && hesapSecim <= hesapSayisi)
			if((temp + hesapSecim - 1)->bakiye > 0)
				printf("\nHesap kapatma icin bakiyenin sifir olmasi gerekmektedir. Yeni bir hesap seciniz veya Cikis icin 0 giriniz...\n");
			else
				break;
		else if(hesapSecim == 0)
			return;
		else
			printf("\nYanlis secim yaptiniz lutfen dogru bir hesap secimi yapiniz veya Cikis icin 0 giriniz...\n");
	}

	FILE *fp, *fpTemp;
	fp = txtOpen(hDosyasi,"rb");
	fpTemp = txtOpen("temp.txt","wb");

	while(fread(pHesap, sizeof(*pHesap), 1, fp) == 1)
	{
		if((temp + hesapSecim - 1)->hNo != pHesap->hNo)
			if(fwrite(pHesap, sizeof(*pHesap), 1, fpTemp) != 1)
			{
				printf("\nHesap kapatma sirasinda bir hata olustu lutfen tekrar deneyiniz...\n");
				exit(1);
			}
	}
	fclose(fp);
	fclose(fpTemp);
	remove(hDosyasi);
	rename("temp.txt", hDosyasi);
	printf("\nIsleminiz basarili bir sekilde gerceklestirilmistir...\n");
}

long int tarihSaniyeHesaplama(int g1, int a1, int y1)
{
	int g, a, y, g2, a2, y2;
	g2 = 01;
	a2 = 01;
	y2 = 1970;

	if (g1<g2)
	{
        	a1=a1-1;
        	g1=g1+30;
    	}
	if (a1<a2)
	{
        	y1=y1-1;
		a1=a1+12;
    	}
	g=g1-g2; a=a1-a2; y=y1-y2;
	long int saniye = 0;
	saniye += y * 31557600;
	saniye += a * 2629800;
	saniye += g * 86400;
	return saniye;
}

void hesapOzet(int mNo)
{
	int hesapSayisi, hesapSecim, hNo;
	raporBilgileri *pRapor;
	pRapor = (raporBilgileri *) malloc(sizeof(raporBilgileri));
	hesapBilgileri *temp;
	temp = hesaplar(mNo, &hesapSayisi);

	while(1)
	{
		hesapListesi(mNo);
		printf("Lutfen bir hesap seciniz (Cikis: 0): ");
		scanf("%d", &hesapSecim);
		if(hesapSecim > 0 && hesapSecim <= hesapSayisi)
			break;
		else if(hesapSecim == 0)
			return;
		else
			printf("\nYanlis secim yaptiniz lutfen dogru bir hesap secimi yapiniz veya Cikis icin 0 giriniz...\n");
	}

	hNo = (temp + hesapSecim - 1)->hNo;

	long int btarih, starih;
	int g,a,y;
	printf("Lutfen bir tarih giriniz(Bicim: 01/01/2019): ");
	scanf("%d/%d/%d",&g,&a,&y);
	btarih = tarihSaniyeHesaplama(g,a,y);
	printf("Lutfen bir tarih giriniz(Bicim: 01/01/2018): ");
	scanf("%d/%d/%d",&g,&a,&y);
	starih = tarihSaniyeHesaplama(g,a,y);
	printf("%ld\n",starih);

	if(btarih < starih)
	{
		long int temp = btarih;
		btarih = starih;
		starih = btarih;
	}

	FILE *fp;
	fp = txtOpen(dDosyasi,"rb");

	while(fread(pRapor, sizeof(*pRapor), 1, fp) == 1)
	{
		if(btarih >= pRapor->tarih && starih <= pRapor->tarih)
		if(pRapor->hNo == hNo || pRapor->havaleNo == hNo)
		{
			if(pRapor->islem == ParaCekme)
				printf("\nIslem Turu: Para Cekme\nIslem Tarihi: %sIslem Tutari: %.2f\n", ctime(&pRapor->tarih), pRapor->islemTutari);
			else if(pRapor->islem == ParaYatirma)
				printf("\nIslem Turu: Para Yatirma\nIslem Tarihi: %sIslem Tutari: %.2f\n", ctime(&pRapor->tarih), pRapor->islemTutari);
			else if(pRapor->islem == ParaHavale || pRapor->hNo == hNo)
				printf("\nIslem Turu: Gelen Havale\nIslem Tarihi: %sIslem Tutari: %.2f\n***Gonderen Bilgileri***\nMusteri No: %d\nHesap No: %d\nMusteri Adi: %s %s\n", ctime(&pRapor->tarih), pRapor->islemTutari,pRapor->pBilgi.no, pRapor->havaleNo, pRapor->pBilgi.ad, pRapor->pBilgi.soyad);
			else
				printf("\nIslem Turu: Giden Havale\nIslem Tarihi: %sIslem Tutari: %.2f\n***Gonderilen Hesap Bilgileri***\nMusteri No: %d\nHesap No: %d\nMusteri Adi: %s %s\n", ctime(&pRapor->tarih), pRapor->islemTutari, pRapor->pBilgi.no, pRapor->havaleNo, pRapor->pBilgi.ad, pRapor->pBilgi.soyad);
		}
	}
	fclose(fp);
}

//Rapor işlem fonksiyonları
void raporIslemleri(islemTuru islem, int islemTutar)
{
	float bankaHazinesi, cekilenPara, yatirilanPara;
	FILE *fp;
	fp = txtOpen(rDosyasi,"rb+");
	fscanf(fp, "%f %f %f", &bankaHazinesi, &cekilenPara, &yatirilanPara);
	rewind(fp);

	if(islem == ParaCekme)
		cekilenPara += islemTutar;
	else if(islem == ParaYatirma)
		yatirilanPara += islemTutar;
	else
		bankaHazinesi += (float)(islemTutar * 2) / 100;

	fprintf(fp, "%.2f %.2f %.2f",bankaHazinesi, cekilenPara, yatirilanPara);
	fclose(fp);
}

void rapor()
{
	float bankaHazinesi, cekilenPara, yatirilanPara;
	FILE *fp;
	fp = txtOpen(rDosyasi,"rb");
	fscanf(fp, "%f %f %f", &bankaHazinesi, &cekilenPara, &yatirilanPara);
	printf("\nBanka Hazinesi: %.2f\nBankada Bulunan Para: %.2f\nBankaya Yatirilan Toplam Para: %.2f\nBankadan Cekilen Toplam Para: %.2f\n",bankaHazinesi,(float)(yatirilanPara - cekilenPara), yatirilanPara, cekilenPara);
	fclose(fp);
}
