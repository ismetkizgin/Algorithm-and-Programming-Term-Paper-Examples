#include <stdio.h>
#include <stdlib.h>

/* Engel yüzdesini derecelendirme numarasını bulmak için hazırlanmış bir fonksiyon. */
int engel_derecesi(int engel_orani)
{
	if(engel_orani>=80)
		return 1;
	else if(engel_orani>=60 && engel_orani<80)
		return 2;
	else if(engel_orani>=40 && engel_orani<60)
		return 3;
	else if(engel_orani<40)
		return 0;
}

/* Eşin çalışmama durumunda 220 TL ödeneğin verilip verilmeme durumunu kontrol eden fonksiyon. */
float es_odenegi(char medeni_durumu, char es_durumu)
{
	if(medeni_durumu=='E' || medeni_durumu=='e')
	{
		if(es_durumu=='H' || es_durumu=='h')
			return 220;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}

/* Çocukların sayısına göre ödenek verilecek fonksiyon. */
float cocuk_odenegi(int cocuk_sayisi, int buyuk_cocuk_sayisi)
{
	return ((cocuk_sayisi - buyuk_cocuk_sayisi) * 25) + (buyuk_cocuk_sayisi * 45);
}

/* Aylık brüt ücret hesaplaması için kullanılan fonksiyon. */
float aylik_brut_ucret(float cocuk, float es, float brut)
{
	return (cocuk + es + brut);
}

/* Engelli veri indirimi için kullanılan fonksiyon. */
float engelli_indirimi(int engel_yuzdesi)
{
	if(engel_yuzdesi >= 80 && engel_yuzdesi <=100)
		return 900;
	else if(engel_yuzdesi >= 60 && engel_yuzdesi <80)
		return 470;
	else if(engel_yuzdesi >= 40 && engel_yuzdesi <60)
		return 210;
	else
		return 0;
}

/* Gelir vergisi yüzdesini hesaplıyoruz */
float gelir_vergisi_yuzdesi(float brut_ucret, float engel_yuzdesi)
{
	brut_ucret -= engelli_indirimi(engel_yuzdesi);

	if(brut_ucret < 2000)
		return 0.15;
	else if(brut_ucret >= 2000 & brut_ucret < 5000)
		return 0.20;
	else if(brut_ucret >= 5000 & brut_ucret < 10000)
		return 0.27;
	else if(brut_ucret >= 10000)
		return 0.35;
}

/* Gelir vergisini hesaplamak için kullanılan fonksiyon. */
float gelir_vergisi(float brut_ucret,float engel_yuzdesi)
{
	return (float) ((brut_ucret-engelli_indirimi(engel_yuzdesi)) * gelir_vergisi_yuzdesi(brut_ucret,engel_yuzdesi));
}

/* Aylık net ücret hesaplaması için kullanılan fonksiyon. */
float net_ucret(float brut, float vergi)
{
	return (brut - vergi);
}

/* En yüksek brüt maaşı alan ve net maaşı yüksek olan çalışanların bilgilerini tutmak için kullanılan metot ve değişkenleri.
   Dizilere eklenen ücretlerin indisi 0 olanlar brüt ücreti en yüksek olanı temsil eder 1 olanlar net ücreti en yüksek olanı temsil eder. */
float i_brut_ucret[2]={0,0}, i_gelir_vergisi[2]={0,0}, i_net_ucret[2]={0,0};
char b_ad[30], n_ad[30];
long long int i_tc[2];

void en_yuksek(float brut_ucret, float net_ucret, float vergi, long int tc, char ad[])
{
	if(brut_ucret >= i_brut_ucret[0])
	{
		i_brut_ucret[0]=brut_ucret;
		i_gelir_vergisi[0]=vergi;
		i_net_ucret[0]=net_ucret;
		i_tc[0]=tc;
		for(int i=0;i<30;i++)
			b_ad[i]=ad[i];
	}

	if(net_ucret >= i_net_ucret[1])
	{
		i_brut_ucret[1]=brut_ucret;
		i_gelir_vergisi[1]=vergi;
		i_net_ucret[1]=net_ucret;
		i_tc[1]=tc;
		for(int i=0;i<30;i++)
			n_ad[i]=ad[i];
	}
}

/* Banknot sayisini bulmak için gerekli metodumuz ve değişkenimiz aşağıda yer alıyor.
Banknot dizimizde bulunan;
0. indisimiz para birimizin miktarını tutar
1. indisimiz ise istatistik üzerinde tutulan banknot adetlerini içerir
2. indisimiz ve son indisimiz ise hesaplamasını yaptığımız kullanıcının banknotunu hesaplıyor. */
float banknot[12][3]={200,0,0,100,0,0,50,0,0,20,0,0,10,0,0,5,0,0,1,0,0,0.50,0,0,0.25,0,0,0.10,0,0,0.05,0,0,0.01,0,0};

void banknot_sayisi(float para)
{
	for(int i=0;i<12;i++)
	{
		banknot[i][2]=0;
		while(1)
		{
			if(para<banknot[i][0])
				break;
			banknot[i][1]++;
			banknot[i][2]++;
			para-=banknot[i][0];
		}
	}
}

/* Banknotların sayılarını ekrana bastırıyor. cikti değişkeni ile tek kullanıcının mı yoksa istatistiğin mi çıktısını ekrana bastırılması gerektiğini belirtiyoruz. */
void banknot_sayisi_yazdir(int cikti)
{
	printf("\n**** Aylik Net Ucretin En Az Banknot ile Odenmesi Icin Gerekli Banknot Adetleri ****\n\n");
	for(int i=0; i<12; i++)
	{
		if(banknot[i][cikti]>0)
		{
			if(i<7)
				printf("%.0f TL - %.0f Adet\n",banknot[i][0],banknot[i][cikti]);
			else
				printf("%.0f kurus - %.0f Adet\n",(banknot[i][0]*100),banknot[i][cikti]);
		}
	}
}

int main()
{
	/* İstatistik için belirlenen değişkenler. */
	float t_net_ucret=0, t_vergi=0, t_brut=0, vergi_yuzde;
	int ikibin_alti=0, calisan_sayisi=0,evli=0,es_calisma=0,cocuklu_calisan=0,t_cocuk_sayisi=0,cocuk_sayisi_uc=0,engelli_calisan=0,vergi_yuzdesi[4][2]={15,0, 20,0, 27,0, 35,0};

	do{
	/* Projede kullanılacak olan bilgiler için gerekli değişkenler tanımladık.*/
	int engel_orani, cocuk_sayisi, buyuk_cocuk_sayisi=0;
	float brut_ucret, toplam_brut_ucret, net;
	char medeni_durumu, es_durumu, engel_durumu, ad[30], devam;
	long long int tc;
	/* Proje için gerekli bilgileri kullanıcıdan çekip değişkenlere atama işlemleri yapıyoruz. */
	printf("TC Kimlik Nmaranizi Giriniz: ");
	scanf("%lld",&tc);

	printf("Ad Soyad Bilgisini Giriniz(Max 30 karekter): ");
	/* Hafızada tuttuğu verilerden dolayı gets bölümünde otomatik bir şekilde atama yapıp bu adımı atlıyordu getchar() ile bunu engelledik */
	getchar();
	fgets(ad, sizeof ad, stdin);

	while(1)
	{
		printf("Brut Ucreti Giriniz (Aylik askeri ucret ya da daha buyuk): ");
		scanf("%f",&brut_ucret);

		/* Brüt ücret askeri brüt ücretten az olmaması şartından dolayı daha düşük bir miktar girilince otomatik atanıyor. */
		if(brut_ucret >= 1777.50)
			break;
	}

	while(1)
	{
		printf("Medeni Durumunu Giriniz 'Evli/Bekar (e/E/b/B karakterleri)': ");
		scanf("%s",&medeni_durumu);

		/* Doğru bir harf girişi olup olmadığını sorguluyoruz eğer verilen bilgiler dışında bir şey girilmiş ise tekrar girmesini istiyoruz. */
		if(medeni_durumu == 'e' || medeni_durumu == 'E' || medeni_durumu == 'b' || medeni_durumu == 'B')
			break;
	}
	/* Evli olan çalışanın eşinin çalışıp çalışmadığı bilgisini alıyoruz. */
	if(medeni_durumu == 'E' || medeni_durumu == 'e')
	{
		while(1)
		{
			printf("Evli Ise Esinin Calisip Calismadigi 'Evet/Hayir (e/E/h/H karakterleri)': ");
			scanf("%s",&es_durumu);

			/* Doğru bir harf girişi olup olmadığını sorguluyoruz eğer verilen bilgiler dışında bir şey girilmiş ise tekrar girmesini istiyoruz. */
			if(es_durumu == 'e' || es_durumu == 'E' || es_durumu == 'h' || es_durumu == 'H')
				break;
		}
	}

	while(1)
	{
		printf("Bakmakla Yukumlu Oldugu Cocuk Sayisi 'tamsayi (0 ya da daha buyuk)': ");
		scanf("%d",&cocuk_sayisi);

		/* Doğru bir giriş yapmadığını sorguluyoruz eğer verilen bilgiler dışında bir şey girilmiş ise tekrar girmesini istiyoruz. */
		if(cocuk_sayisi >= 0)
			break;
	}

	/* Bakmakla yükümlü olduğu çocuk var ise bunların kaç tanesinin 6 yaşından bilginisini alıyoruz. */
	if(cocuk_sayisi>0)
	{
		while(1)
		{
			printf("6 Yasindan Buyuk Cocuk Sayisini Giriniz: ");
			scanf("%d",&buyuk_cocuk_sayisi);

			if(buyuk_cocuk_sayisi <= cocuk_sayisi && buyuk_cocuk_sayisi >=0)
				break;
		}
	}

	while(1)
	{
	printf("Engelli Durumunuz Var Mi? Evet/Hayir (e/E/h/H karakterleri): ");
	scanf("%s", &engel_durumu);

	/* Doğru bir harf girişi olup olmadığını sorguluyoruz eğer verilen bilgiler dışında bir şey girilmiş ise tekrar girmesini istiyoruz. */
	if(engel_durumu == 'e' || engel_durumu == 'E' || engel_durumu == 'h' || engel_durumu == 'H')
		break;
	}

	/* Engel durumu varsa onun yüzdesini girmesini istiyorum */
	if(engel_durumu == 'E' || engel_durumu == 'e')
	{
		while(1)
		{
			printf("Engel Oranini Giriniz 'tamsayı (1 ya da daha buyuk ve 100 ya da daha kucuk)': ");
			scanf("%d",&engel_orani);

			/* Engel oranını doğru değer aralığında girilip girilmediğini kontrol ediyoruz. */
			if(engel_orani >0 && engel_orani <=100)
				break;
		}
	}

	/* Aylik Toplam Brüt Ücreti Hesaplıyoruz. */
	brut_ucret += es_odenegi(medeni_durumu,es_durumu) + cocuk_odenegi(cocuk_sayisi, buyuk_cocuk_sayisi);

	/* Çıktı ekranı için geçerli olan kodlar. */
	printf("\n########### Kaydi Gerceklesen Calisan ##########\n\n");
	printf("TC Kimlik Numarasi: %lld\n",tc);
	printf("Ad Soyad: %s",ad);
	printf("Aylik Brut Ucreti(TL): %.2f\n",brut_ucret);
	printf("Es Icin Aile Yardim Odenegi(TL): %.2f\n",es_odenegi(medeni_durumu,es_durumu));
	printf("Cocuk Icin Aile Yardim Odenegi(TL): %.2f\n",cocuk_odenegi(cocuk_sayisi, buyuk_cocuk_sayisi));
	printf("Gelir Vergisi Kesintisi(TL): %.2f\n",gelir_vergisi(brut_ucret,engel_orani));

	if(engel_durumu == 'E' || engel_durumu == 'e')
	{
		if(engel_derecesi(engel_orani))
			printf("Engel Derecesi(1/2/3): %d\n",engel_derecesi(engel_orani));
		else
			printf("Engel Derecesi(1/2/3): %d Oraninda Engelli\n",engel_orani);
	}

	/* Net ücret hesaplaması. */
	net = net_ucret(brut_ucret,gelir_vergisi(brut_ucret,engel_orani));
	printf("Aylik Net Ucret(TL): %.2f\n",net);

	/* Net ücretin banknot hesaplaması ve ekrana bastırılması. */
	banknot_sayisi(net);
	banknot_sayisi_yazdir(2);

	/* İstatistik bilgileri oluşturulması veya güncellenmesi. */
	calisan_sayisi++;
	t_net_ucret += net;
	t_brut += brut_ucret;
	t_vergi += gelir_vergisi(brut_ucret,engel_orani);
	if(net < 2000)
		ikibin_alti++;
	if(medeni_durumu == 'e' || medeni_durumu == 'E')
	{
		evli++;
		if(es_durumu == 'e' || es_durumu == 'E')
			es_calisma++;
	}
	if(cocuk_sayisi > 0)
	{
		cocuklu_calisan++;
		t_cocuk_sayisi += cocuk_sayisi;
		if(cocuk_sayisi > 3)
			cocuk_sayisi_uc++;
	}
	if(engel_durumu == 'E' || engel_durumu == 'e')
		engelli_calisan++;
	vergi_yuzde=gelir_vergisi_yuzdesi(brut_ucret,engel_orani);
	if(vergi_yuzde == (float) 0.15)
		vergi_yuzdesi[0][1]++;
	else if(vergi_yuzde == (float) 0.20)
		vergi_yuzdesi[1][1]++;
	else if(vergi_yuzde == (float) 0.27)
		vergi_yuzdesi[2][1]++;
	else if(vergi_yuzde == (float) 0.35)
		vergi_yuzdesi[3][1]++;
	en_yuksek(brut_ucret,net,gelir_vergisi(brut_ucret,engel_orani),tc,ad);

	/* Yeni çalışan ekleyip eklemeyeceğiniz soruyoruz. */
	while(1)
	{
		printf("\nBaska Calisan Var Mi ? 'Evet/Hayir (e,E,h,H karekteri)': ");
		scanf("%s",&devam);

		/* Doğru bir harf girişi olup olmadığını sorguluyoruz eğer verilen bilgiler dışında bir şey girilmiş ise tekrar girmesini istiyoruz. */
		if(devam == 'e' || devam == 'E' || devam == 'h' || devam == 'h')
			break;
	}

	if(devam == 'h' || devam == 'H')
		break;

	}while(1);

	/* İstatistik verilerinin çıktıları. */
	printf("\n########## Istatistik Tablosu ##########\n\n");
	printf("Toplam Odenen Net Ucret(TL): %.2f\n", t_net_ucret);
	printf("Devlete Verilen Toplam Gelir Vergisi(TL): %.2f\n", t_vergi);
	printf("Tum Calisanlarin Brut Ucretlerinin Ortalamasi(TL): %.2f\n",(t_brut/calisan_sayisi));
	printf("Tum Calisanlarin Net Ucretlerinin Ortalamasi(TL): %.2f\n",(t_net_ucret/calisan_sayisi));
	printf("Aylik 2000 TL Altinda Maas Alan Calisan Sayisi: %d\n", ikibin_alti);
	printf("Evli Olanlarin Yuzdesi: %.2f\n", (float) ((evli*100)/calisan_sayisi));
	printf("Bekar Olanlarin Yuzdesi: %.2f\n",(float) (((calisan_sayisi-evli)*100)/calisan_sayisi));

	/* Evli olanların sıfır olması durumunda programın sıfır belirsizliğini ortadan kaldırmak için if koşulunu bıraktık. */
	if(evli == 0)
		evli=1;
	printf("Evli Olan Calisanlarin Icinde, Eslerinin Calisma Yuzdesi: %.2f\n",(float) ((es_calisma * 100)/evli));

	/* Çocuk bakanla hükümlü olan çalışan sayısı sıfır olması durumundan sıfır belirsizliğini ortadan kaldırmak için if koşulu bıraktık. */
	if(cocuklu_calisan == 0)
		cocuklu_calisan=1;
	printf("Sadece Bakmakla Yukumlu Cocugu Olanlar Dikkate Alinarak, Calisanlarin Bakmakla Yukumlu Olduklari Cocuk Sayisinin Ortalamasi: %.2f\n",(float) (t_cocuk_sayisi/cocuklu_calisan));
	printf("Bakmakla Yukumlu Oldugu Cocuk Sayisi 3\'ten Fazla Olan Calisanlarin Sayisi: %d\n",cocuk_sayisi_uc);
	printf("Engelli Calisan Sayisi: %d\n",engelli_calisan);
	printf("Engelli Calisan Yuzdesi: %.2f\n",(float) ((engelli_calisan*100)/calisan_sayisi));
	banknot_sayisi_yazdir(1);
	printf("\n**** Gelir Vergisi Tablosu ****\n\n");
	printf("Vergi Yuzdesi\tCalisan Sayisi\tYuzdesi\n");
	printf("-------------\t--------------\t-------\n");

	/* Dizi içine aktarılan vergi yüzdeleri bilgileri dizi içinden döngü ile çıkarıldı. */
	for(int i=0; i<4; i++)
	printf(" %d \t\t %d \t\t %.2f\n",vergi_yuzdesi[i][0],vergi_yuzdesi[i][1],(float) (vergi_yuzdesi[i][1] * 100 / calisan_sayisi));

	for(int i =0; i<2; i++)
	{
		if(i==0)
			printf("\n**** Aylik Brut Ucreti En Fazla Olan Calisan Bilgileri ****\n\n");
		else
			printf("**** Aylik Net Ucreti En Fazla Olan Calisan Bilgileri ****\n\n");

		printf("TC Kimlik Numarasi: %lld\n",i_tc[i]);
		printf("Ad Soyad: ");
		if(i==0)
			printf("%s",b_ad);
		else
			printf("%s",n_ad);
		printf("Aylik Brut Ucret: %.2f\n",i_brut_ucret[i]);
		printf("Gelir Vergisi Kesintisi: %.2f\n",i_gelir_vergisi[i]);
		printf("Aylik Net Ucret: %.2f\n\n",i_net_ucret[i]);
	}
}
