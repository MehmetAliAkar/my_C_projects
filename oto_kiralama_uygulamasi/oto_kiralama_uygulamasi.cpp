#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

struct musteri {
	char ad[20];
	char soyad[20];
	char tel[20];
	char adres[20];
	char id[20];
	char parola[20];
	char parolaTekrar[20];
};


struct oto {
	int siraNo;
	char marka[20];
	char model[20];
	int fiyat;
};


void aracKirala(struct musteri m1)
{
	FILE* filep;
	FILE* filep2;
	struct oto o1;
	int siraNo,toplamFiyat,gunSayisi;
	char tarih[20];
	int cevap;
	bool control = false;

	filep = fopen("araclar.txt", "r");
	if (filep == NULL)
	{
		printf("\nError,unable to open the file.");
		exit(0);
	}
	else
	{
		y:
		printf("\n------------- ARACLAR -------------\n");
		printf("\nSIRANO\t%-15s\t%-15s\tFIYAT\n","MARKA","MODEL");

		while (fscanf(filep, "%d%s%s%d", &o1.siraNo, o1.marka, o1.model, &o1.fiyat) != EOF)
		{
			printf("%d\t%-15s\t%-15s\t%d\n", o1.siraNo, o1.marka, o1.model, o1.fiyat);
		}
		rewind(filep);
		x:
		printf("\nAlmak istediginiz arac nosunu giriniz.");
		scanf("%d", &siraNo);
		
		while (fscanf(filep, "%d%s%s%d", &o1.siraNo, o1.marka, o1.model, &o1.fiyat) != EOF)
		{
			if (siraNo == o1.siraNo)	
			{
				control = true;
				break;
			}
		}

		if (control == false)
		{
			printf("\nAradiginiz numaraya ait arac bulunamadi.Lutfen yeni arac no giriniz.");
			goto x;
		}
		else
		{
			system("cls");
			printf("\nKiralamak istediginiz arac bilgileri:\n");
			printf("\nSIRANO\t%-15s\t%-15s\tFIYAT\n", "MARKA", "MODEL");
			printf("%d\t%-15s\t%-15s\%d\n", o1.siraNo, o1.marka, o1.model, o1.fiyat);
			printf("\nAraci kac gun kiralayacaksiniz:"); scanf("%d", &gunSayisi);
			toplamFiyat = gunSayisi * o1.fiyat;
			printf("\nOdemenin gereken fiyat: %d", toplamFiyat);
			printf("\nTutari onayliyor musunuz (evet : 1 - hayir : 0) : ");	scanf("%d", &cevap);
			if (cevap==1)
			{
				printf("\nIslem onaylanmıstir.");
			}
			else
			{
				printf("Ana Sayfaya Yonlendiriliyorsunuz...");
				goto y;
				system("cls");
			}
		}

		filep2 = fopen("kiralananAraclar.txt", "a");
		if (filep2 == NULL)
		{
			printf("File cannot opened.");
		}
		else
		{
			fprintf(filep2, "\n");
			fprintf(filep2, "arac bilgileri    : %d\t%s\t%s\t%d\n", o1.siraNo, o1.marka, o1.model, o1.fiyat);
			fprintf(filep2, "musteri bilgileri : %s\t%s\t%s\t%s\n", m1.ad, m1.soyad, m1.adres, m1.tel);
			fprintf(filep2, "odenecek tutar = %d\n", toplamFiyat);
			fprintf(filep2, "------------------------\n");
		}
		fclose(filep2);

	}
	fclose(filep);


}

void yeniKayit()
{
	struct musteri m1;
	a:
	printf("\n---------- YENI MUSTERI KAYIT EKRANI -------------\n");
	printf("\nisim			: ");	scanf(" %[^\n]s", m1.ad);
	printf("\nsoyisim			: ");	scanf(" %[^\n]s", m1.soyad);
	printf("\ntel			: ");	scanf(" %[^\n]s", m1.tel);
	printf("\nadres			: ");	scanf(" %[^\n]s", m1.adres);
	printf("\nID			: ");	scanf(" %[^\n]s", m1.id);
	printf("\nparola			: ");	scanf(" %[^\n]s", m1.parola);
	printf("\nparola tekrar		: ");	scanf(" %[^\n]s", m1.parolaTekrar);

	/*char ch = getchar();
	int i = 0;
	while (ch != 32)
	{
		m1.parola[i] = ch;
		printf(" * ");
		ch = getchar();
		i++;
	}
	m1.parola[i] = '\0';

	printf("\nparola tekrar : ");
	i = 0;
	ch = getchar();
	while (ch != 32)
	{
		m1.parolaTekrar[i]=ch;
		printf(" * ");
		ch = getchar();
		i++;
	}
	m1.parolaTekrar[i] = '\0';*/

	if (strcmp(m1.parola, m1.parolaTekrar) == 0 && strlen(m1.parola)>=8)
	{
		FILE* filep;
		filep = fopen("musteriler.bin", "a+b");
		if (filep == NULL)
		{
			printf("\nUnable to access to the file.");
			exit(0);
		}
		else
		{
			fwrite(&m1, sizeof(struct musteri), 1, filep);
			printf("\nMusteri kaydi basariyla gerceklestirildi.");
			fclose(filep);
		}
	}
	else
	{
		printf("\nGecersiz sifre girildi. Lutfen bilgileri yeniden giriniz.");	Sleep(10);
		system("cls");
		goto a;
	}

}

void aracEkle()
{
	struct oto o1;
	FILE* filep;
	filep = fopen("araclar.txt", "a");
	if (filep == NULL)
	{
		printf("\nUnable to access to the file.");
		exit(0);
	}
	else
	{
		printf("\n-------- ARAC KAYIT EKRANI ------------\n");
		printf("\nArac bilgilerini giriniz : \n");
		printf("\nSira No : ");	scanf("%d", &o1.siraNo);
		printf("\nMarka   : ");	scanf("%s", o1.marka);
		printf("\nModel   : ");	scanf("%s", o1.model);
		printf("\nFiyat   : ");	scanf("%d", &o1.fiyat);

		fprintf(filep,"\n%d\t%-15s\t%-15s\t%d",o1.siraNo,o1.marka,o1.model,o1.fiyat);
	}
		fclose(filep);
}

int menu()
{
	int secim;
	printf("\n********	ANA MENU	********\n");
	printf("1->GIRIS\n");
	printf("2->YENI ARAC KAYDI\n");
	printf("3->YENI KAYIT\n");
	printf("4->CIKIS\n");
	printf("Secim : ");	scanf("%d", &secim);

	return secim;
}

void giris()
{
	FILE* filep;
	bool control = false;
	filep = fopen("musteriler.bin", "r+b");
	if (filep == NULL)
	{
		printf("ERROR,UNABLE TO OPEN FILE");
		exit(0);
	}
	else
	{
		a:
		char mus_id[20];
		char mus_parola[20];
		struct musteri m1;
		printf("\nMusteri ID giriniz:");
		scanf(" %[^\n]s", mus_id);
		printf("\mMusteri parola giriniz: ");
		scanf("  %[^\n]s", mus_parola);
		while ((fread(&m1, sizeof(struct musteri), 1, filep)) != NULL)
		{
			if ((strcmp(mus_id, m1.id) == 0)	&& (strcmp(mus_parola,m1.parola)==0))
			{
				system("cls");
				printf("\nHosgeldiniz %s %s\n", m1.ad, m1.soyad);
				control = true;
				break;
			}
		}

		if (control == false)
		{
			printf("\nHatali kullanici adi ve ya parola girisi!!!");
			goto a;
		}
		else
		{
			aracKirala(m1);
		}
	}
}


int main()
{
	while (1)
	{
		int secim = menu();
		switch (secim)
		{
			case 1:
				giris();
				break;
			case 2:
				aracEkle();
				break;
			case 3:
				yeniKayit();
				break;
			case 4:
				exit(0);
				break;
			default:
				printf("\nLutfen gecerli bir islem giriniz.");
		}
	}

}