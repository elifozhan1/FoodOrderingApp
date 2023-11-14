/******************************
** SAKARYA ÜNİVERSİTESİ
** BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
** BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
** NESNEYE DAYALI PROGRAMLAMA DERSİ
** 2022 - 2023 GÜZ DÖNEMİ
**
** ÖDEV NUMARASI: 2
** ÖĞRENCİ ADI: ELİF ÖZHAN
** ÖĞRENCİ NUMARASI: B221210001
** DERSİN ALINDIĞI GRUP: B
******************************/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale.h>

using namespace std;

ofstream DosyaYaz;
ifstream DosyaOku;

void ProgramMenu();
void YemekBilgileriMenu();
void YemekUretim();
void GelirGiderRaporu();
void YemekListesi();

int secim = 0;
int toplam_fiyat = 0;
int* fiyatPtr = &toplam_fiyat;
int toplam_maaliyet = 0;
int* maaliyetPtr = &toplam_maaliyet;

class Urun
{
public:

	string ad;
	string uretim_tarihi;
	string tuketim_tarihi;
	string malzeme1;
	string malzeme2;
	string malzeme3;
	float kalori;
	float gram;
	float fiyat;
	float maaliyet;
	float stok_durumu;

	void UrunEkleme();
	void UrunSilme();
	void UrunGuncelleme();
	void UrunRaporAlma();

};

void Urun::UrunEkleme()
{
	do
	{
		cout << "Yemek adı: ";
		cin >> ad;
		cout << "Yemeğin kalori değeri: ";
		cin >> kalori;
		cout << "Yemeğin gramı: ";
		cin >> gram;
		cout << "Yemeğin fiyatı: ";
		cin >> fiyat;
		cout << "Yemeğin maaliyeti: ";
		cin >> maaliyet;
		cout << "Yemeğin stok durumu: ";
		cin >> stok_durumu;
		cout << "Yemeğin üretim tarihi: ";
		cin >> uretim_tarihi;
		cout << "Yemeğin son tüketim tarihi: ";
		cin >> tuketim_tarihi;

		cout << "Yemeğin malzemelerini giriniz (3 adet):";
		cout << "Malzeme 1:";
		cin >> malzeme1;
		cout << "Malzeme 2:";
		cin >> malzeme2;
		cout << "Malzeme 3:";
		cin >> malzeme3;

		DosyaYaz.open("depo.txt", ios::app);
		DosyaYaz << ad << setw(20) << kalori << setw(5) << gram << setw(5) << fiyat << setw(5) << maaliyet <<
			setw(5) << stok_durumu << setw(10) << uretim_tarihi << setw(10) << tuketim_tarihi << endl;
		DosyaYaz.close();

		DosyaYaz.open("malzemeler.txt", ios::app);
		DosyaYaz << ad << setw(20) << malzeme1 << setw(20) << malzeme2 << setw(20) << malzeme3 << endl;
		DosyaYaz.close();

		DosyaYaz.open("yemek_cesit.txt", ios::app);
		DosyaYaz << ad << endl;
		DosyaYaz.close();

		cout << "Dosyaya veri ekleme işlemine devam etmek istiyor musunuz? (Evet = 1, Hayır = 0)" << endl;
		cin >> secim;

	} while (secim == 1);

}

void Urun::UrunSilme()
{

	DosyaOku.open("depo.txt");

	string silinecek_yemek;
	cout << "Silmek istediğiniz yemeğin adını yazınız." << endl;
	cin >> silinecek_yemek;

	while (DosyaOku >> ad >> kalori >> gram >> fiyat >> maaliyet >> stok_durumu >> uretim_tarihi >> tuketim_tarihi)
	{
		if (ad == silinecek_yemek)
			continue;
		{
			DosyaYaz.open("silinmeyen_kayıtlar.txt", ios::app);
			DosyaYaz << ad << setw(20) << kalori << setw(5) << gram << setw(5) << fiyat << setw(5) << maaliyet <<
				setw(5) << stok_durumu << setw(10) << uretim_tarihi << setw(10) << tuketim_tarihi << endl;
			DosyaYaz.close();
		}
	}

	DosyaOku.close();

	remove("depo.txt");
	rename("silinmeyen_kayıtlar.txt", "depo.txt");
	
	DosyaOku.open("malzemeler.txt");

	while (DosyaOku >> ad >> malzeme1 >> malzeme2 >> malzeme3)
	{
		if (ad == silinecek_yemek)
			continue;
		{
			DosyaYaz.open("silinmeyen_malzemeler.txt", ios::app);
			DosyaYaz << ad << setw(20) << malzeme1 << setw(20) << malzeme2 << setw(20) << malzeme3 << endl;
			DosyaYaz.close();
		}
	}

	DosyaOku.close();
	remove("malzemeler.txt");
	rename("silinmeyen_malzemeler.txt", "malzemeler.txt");

	DosyaOku.open("yemek_cesit.txt");

	while (DosyaOku >> ad)
	{
		if (ad == silinecek_yemek)
			continue;
		{
			DosyaYaz.open("silinmeyen_yemek_cesit.txt", ios::app);
			DosyaYaz << ad << endl;
			DosyaYaz.close();
		}
	}

	DosyaOku.close();
	remove("yemek_cesit.txt");
	rename("silinmeyen_yemek_cesit.txt", "yemek_cesit.txt");

	cout << "İstediğiniz yemek başarıyla silinmiştir.\n";
}

void Urun::UrunGuncelleme()
{
	int yapilacak_islem = 0;

	DosyaOku.open("depo.txt");

	string duzenlenecek_yemek;
	cout << "Bilgileri güncellenecek yemeğin adını yazınız." << endl;
	cin >> duzenlenecek_yemek;

	cout << "Yemeğin değiştirmek istediğiniz değerini seçiniz." << endl << endl;
	cout << "1) Kalori" << endl;
	cout << "2) Gram" << endl;
	cout << "3) Fiyat" << endl;
	cout << "4) Maaliyet" << endl;
	cout << "5) Stok durumu" << endl;
	cout << "6) Üretim tarihi" << endl;
	cout << "7) Tüketim tarihi" << endl;
	cin >> yapilacak_islem;

	while (DosyaOku >> ad >> kalori >> gram >> fiyat >> maaliyet >> stok_durumu >> uretim_tarihi >> tuketim_tarihi)
	{
		if (ad == duzenlenecek_yemek)
		{
			if (yapilacak_islem == 1)
			{
				cout << "Güncel kalori değerini giriniz: ";
				cin >> kalori;
			}

			else if (yapilacak_islem == 2)
			{
				cout << "Güncel gram değerini giriniz: ";
				cin >> gram;
			}

			else if (yapilacak_islem == 3)
			{
				cout << "Güncel fiyat değerini giriniz: ";
				cin >> fiyat;
			}

			else if (yapilacak_islem == 4)
			{
				cout << "Güncel maaliyet değerini giriniz: ";
				cin >> maaliyet;
			}

			else if (yapilacak_islem == 5)
			{
				cout << "Güncel stok durumu bilgisini giriniz: ";
				cin >> stok_durumu;
			}

			else if (yapilacak_islem == 6)
			{
				cout << "Güncel üretim tarihini giriniz: ";
				cin >> uretim_tarihi;
			}

			else if (yapilacak_islem == 7)
			{
				cout << "Güncel tüketim tarihini giriniz: ";
				cin >> tuketim_tarihi;
			}

			DosyaYaz.open("duzenlenmis.txt", ios::app);
			DosyaYaz << ad << setw(20) << kalori << setw(5) << gram << setw(5) << fiyat << setw(5) << maaliyet <<
				setw(5) << stok_durumu << setw(10) << uretim_tarihi << setw(10) << tuketim_tarihi << endl;
			DosyaYaz.close();
		}

		else
		{
			DosyaYaz.open("duzenlenmis.txt", ios::app);
			DosyaYaz << ad << setw(20) << kalori << setw(5) << gram << setw(5) << fiyat << setw(5) << maaliyet <<
				setw(5) << stok_durumu << setw(10) << uretim_tarihi << setw(10) << tuketim_tarihi << endl;
			DosyaYaz.close();
		}
	}

	DosyaOku.close();

	remove("depo.txt");
	rename("duzenlenmis.txt", "depo.txt");

}

void Urun::UrunRaporAlma()
{
	cout << "AD" << setw(20) << "CAL" << setw(5) << "GRAM" << setw(5) << "TL"  << setw(5) << "ALIŞ" <<
		setw(5) << "STOK" << setw(10) << "UT" << setw(10) << "STT \n" << endl;

	DosyaOku.open("depo.txt");

	while (!DosyaOku.eof())
	{
		
		DosyaOku >> ad >> kalori >> gram >> fiyat >> maaliyet >> stok_durumu >> uretim_tarihi >> tuketim_tarihi;

		cout << ad << setw(20) << kalori << setw(5) << gram << setw(5) << fiyat << setw(5) << maaliyet <<
			setw(5) << stok_durumu << setw(10) << uretim_tarihi << setw(10) << tuketim_tarihi << endl;

	}
	DosyaOku.close();
}

Urun yemek;

void YemekListesi()
{
	DosyaOku.open("yemek_cesit.txt");
	cout << "YEMEK LİSTESİ\n" << endl;
	while (!DosyaOku.eof())
	{

		DosyaOku >> yemek.ad;
		cout << yemek.ad << endl;

	}
	DosyaOku.close();
}


void YemekBilgileriMenu()
{
	int istek = 0;

	do
	{
		system("cls");
		cout << "Yapılacak işlem seçiniz.\n" << endl;
		cout << "1) Rapor Alma \n";
		cout << "2) Kayıt ekleme \n";
		cout << "3) Kayıt silme \n";
		cout << "4) Kayıt güncelleme \n";
		cout << "5) Ana menü \n";
		cin >> secim;

		if (secim == 1) yemek.UrunRaporAlma();
		else if (secim == 2) yemek.UrunEkleme();
		else if (secim == 3) yemek.UrunSilme();
		else if (secim == 4) yemek.UrunGuncelleme();
		else if (secim == 5) ProgramMenu();
		else
		{
			system("cls");
			cout << "Yanlış işlem numarası girdiniz." << endl << endl;
			YemekBilgileriMenu();
		}

		cout << "Yemek bilgileriyle ilgili menünün çalışmasını istiyor musunuz? (Evet = 1, Hayır = 0)" << endl;
		cin >> istek;

	} while (istek == 1);

}

void YemekUretim()
{
	system("cls");

	int yemek_sayisi = 0;
	string yapilacak_yemekler[30];
	int adet_dizisi[30];
	int fiyatdizisi[30];
	int maaliyetdizisi[30];

	YemekListesi();
	cout << "Kaç çeşit yemek üretimi yapmak istediğinizi belirtiniz." << endl;
	cin >> yemek_sayisi;

	cout << "Hangi yemeklerden üretim yaptırmak istediğinizi belirtiniz." << endl;

	for (int i = 0; i < yemek_sayisi; i++)
	{
		cout << "Üretilecek " << i + 1 << ". yemek: ";
		cin >> yapilacak_yemekler[i];
	}

	cout << "Seçtiğiniz yemeklerden kaçar tane üretim yaptırmak istediğinizi belirtiniz. (sırasıyla)" << endl;

	for (int i = 0; i < yemek_sayisi; i++)
	{
		cout << "Üretilecek " << i + 1 << ". yemek: ";
		cin >> adet_dizisi[i];
	}

	for (int i = 0; i < yemek_sayisi; i++)
	{
		DosyaYaz.open("siparis_listesi.txt", ios::app);
		DosyaYaz << yapilacak_yemekler[i] << setw(20) << adet_dizisi[i] << endl;
		DosyaYaz.close();
	}

	cout << "Sipariş listeniz başarıyla oluşturulmuştur.\n" << endl;
	cout << "SİPARİŞ LİSTESİ\n" << endl;
	cout << "AD" << setw(20) << "ADET" << endl;

	for (int i = 0; i < yemek_sayisi; i++)
	{
		cout << yapilacak_yemekler[i] << setw(20) << adet_dizisi[i] << endl;
	}

	for (int i = 0; i < yemek_sayisi; i++)
	{
		DosyaOku.open("depo.txt");

		while (!DosyaOku.eof())
		{

			if (yemek.ad == yapilacak_yemekler[i])
			{
				fiyatdizisi[i] = yemek.fiyat * adet_dizisi[i];
				maaliyetdizisi[i] = yemek.maaliyet * adet_dizisi[i];

				if (yemek.stok_durumu < adet_dizisi[i])
				{
					DosyaYaz.open("ihtiyac_listesi.txt", ios::app);
					DosyaYaz << yemek.ad << (adet_dizisi[i] - yemek.stok_durumu);
					DosyaYaz.close();

					cout << "Stokta istediğiniz adette yemek bulunmamaktadır.\n";
					cout << "Beklediğiniz için teşekkürler.\n";
				}
			}
		}
		DosyaOku.close();
	}

	for (int i = 0; i < yemek_sayisi; i++)
	{
		toplam_fiyat += fiyatdizisi[i];
	}

	for (int i = 0; i < yemek_sayisi; i++)
	{
		toplam_maaliyet += maaliyetdizisi[i];
	}

}

void GelirGiderRaporu()
{
	cout << "Gelir Gider Raporu \n";
	cout << "GELİR" << setw(20) << "MAALİYET" << endl;
	cout << *fiyatPtr << setw(20) << *maaliyetPtr <<  endl;
}

void ProgramMenu()
{
	int istek = 0;

	do
	{
		system("cls");
		cout << "HOŞ GELDİNİZ" << endl << "İşlem seçiniz" << endl << endl;

		cout << "1) Yemek bilgileri işlemleri \n";
		cout << "2) Yemek üretim \n";
		cout << "3) Gelir gider raporu \n";
		cin >> secim;

		if (secim == 1) YemekBilgileriMenu();
		else if (secim == 2) YemekUretim();
		else if (secim == 3) GelirGiderRaporu();
		else
		{
			system("cls");
			cout << "Yanlış işlem numarası girdiniz." << endl << endl;
			ProgramMenu();
		}

		cout << "Programın çalışmaya devam etmesini istiyor musunuz? (Evet = 1, Hayır = 0)" << endl;
		cin >> istek;

	} while (istek == 1);
}

int main()
{
	setlocale(LC_ALL, "Turkish");
	ProgramMenu();
}