/* 
   Ömer Yıldırım
   2312729003
   Veri Yapıları
   Mobilyacı Otomasyonu
*/

#include <iostream>
#include <string>
#include <locale.h>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Mobilya {
    string kategori;
    int fiyat;
    string urun_no;
    string renk;
    string isim;
    Mobilya* next;
};

Mobilya* head = NULL;

// Fonksiyon prototipleri
void giris();
void listeleme();
void arama();
void silme();
void duzenleme();
void ekle(Mobilya* yeni_mobilya);
Mobilya* ara(const string& urun_no);
void sil(const string& urun_no);
void dosya_oku();
void dosya_yaz();

int main() {
    setlocale(LC_ALL, "Turkish");

    int secim;
    int cvp;

    do {
        cout << "\n";
        system("cls");
        cout << "\n";
        cout << "|->-->-->-->--<--<--<--<-<|\n";
        cout << "|       HOŞ GELDİNİZ..    |\n";
        cout << "|                         |\n";
        cout << "|  1->  Ürün Girişi    <- |\n";
        cout << "|  2->  Ürün Listeleme <- |\n";
        cout << "|  3->  Ürün Arama     <- |\n";
        cout << "|  4->  Ürün Silme     <- |\n";
        cout << "|  5->  Ürün Düzenleme <- |\n";
        cout << "|->-->-->-->--<--<--<--<-<|\n";
        cout << "\n";
        cout << "Yapmak istediğiniz işlemi seçiniz (1/2/3/4/5): ";
        cin >> secim;
        cout << "\n";

        switch (secim) {
        case 1:
            giris();
            break;
        case 2:
            listeleme();
            break;
        case 3:
            arama();
            break;
        case 4:
            silme();
            break;
        case 5:
            duzenleme();
            break;
        default:
            cout << "Geçersiz seçim!\n";
            break;
        }

        cout << "\nAna Menüye Dönmek İçin (1), Kapatmak İçin (0): ";
        cin >> cvp;
        cout << "\n";

    } while (cvp == 1);
    return 0;
}

void ekle(Mobilya* yeni_mobilya) {
    if (!head) {
        head = yeni_mobilya;
    } else {
        Mobilya* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = yeni_mobilya;
    }
}


/* Ürün girişi yapma fonksiyonu 
 - Kullanıcıdan mobilya adı, gelen adet ve adet başına fiyatı istenir.
 - Kullanıcı her bir adet için bu bilgileri girebilir.
 - Eklenen her bir mobilya, bir bağlı listede de saklanır.*/

void giris() {
    cout << "Ürün Girişi Yapıyorsunuz..\n\n";
    int cvp;
    do {
        Mobilya* yeni_mobilya = new Mobilya;
        cout << "Ürünün Kategorisini Girniz: ";
        cin >> yeni_mobilya->kategori;
        cout << "Ürünün Ürün Numarası Girniz: ";
        cin >> yeni_mobilya->urun_no;
        cout << "Ürünün Rengini Girniz: ";
        cin >> yeni_mobilya->renk;
        cout << "Ürünün İsmini Giriniz: ";
        cin >> yeni_mobilya->isim;
        cout << "Ürünün Fiyatını Girniz: ";
        cin >> yeni_mobilya->fiyat;
        yeni_mobilya->next = NULL;

        ekle(yeni_mobilya);

        cout << "\nTekrar ürün girmek için (1/0): ";
        cin >> cvp;
        cout << "\n";
    } while (cvp == 1);
}

/* Ürün listeleme fonksiyonu
 - Her mobilyanın adı, fiyatı ve mevcut stok durumu (kalan adet) listelenir.*/

void listeleme() {
    if (!head) {
        cout << "Kayıtlı Ürün Bulunamadı..\n";
        return;
    }

    Mobilya* temp = head;
    int sayac = 1;
    cout << "   ---> ÜRÜNLER <---  \n";
    while (temp) {
        cout << "\n" << sayac << ". Ürünün Bilgileri \n";
        cout << "Kategori: " << temp->kategori << "\n";
        cout << "Numara: " << temp->urun_no << "\n";
        cout << "Renk: " << temp->renk << "\n";
        cout << "İsim: " << temp->isim << "\n";
        cout << "Fiyat: " << temp->fiyat << "\n";
        cout << "------------------------\n";
        temp = temp->next;
        sayac++;
    }
}


Mobilya* ara(const string& urun_no) {
    Mobilya* temp = head;
    while (temp) {
        if (temp->urun_no == urun_no) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/* Ürün arama fonksiyonu
 - Kullanıcıdan aranacak mobilyanın adı istenir.
 - Girilen adı “stok.dat” dosyasında arar ve eğer bulunursa ilgili mobilyanın bilgilerini ekrana yazdırır.*/

void arama() {
    string urun_no;
    cout << "Aramak İstediğiniz Ürün Numarasını Giriniz: ";
    cin >> urun_no;

    Mobilya* sonuc = ara(urun_no);
    if (sonuc) {
        cout << "\nBulunan Ürünün Bilgileri.. \n";
        cout << "Kategori: " << sonuc->kategori << "\n";
        cout << "Numara: " << sonuc->urun_no << "\n";
        cout << "Renk: " << sonuc->renk << "\n";
        cout << "İsim: " << sonuc->isim << "\n";
        cout << "Fiyat: " << sonuc->fiyat << "\n";
        cout << "------------------------\n";
    } else {
        cout << "\nAranan Ürün Bulunamadı..\n";
    }
}


/* Ürün silme fonksiyonu
 - Kullanıcıdan silinecek mobilyanın adı istenir.
 - Kullanıcı onayıyla silme işlemi gerçekleştirilir.
*/

void sil(const string& urun_no) {
    if (!head) {
        cout << "Kayıtlı Ürün Bulunamadı..\n";
        return;
    }

    if (head->urun_no == urun_no) {
        Mobilya* silinecek = head;
        head = head->next;
        delete silinecek;
        cout << "KAYIT SİLİNDİ ✓✓✓\n";
        return;
    }

    Mobilya* temp = head;
    while (temp->next && temp->next->urun_no != urun_no) {
        temp = temp->next;
    }

    if (temp->next) {
        Mobilya* silinecek = temp->next;
        temp->next = silinecek->next;
        delete silinecek;
        cout << "KAYIT SİLİNDİ ✓✓✓\n";
    } else {
        cout << "Kayıt Bulunamadı..\n";
    }
}

void silme() {
    string urun_no;
    cout << "Silmek İstediğiniz Ürün Numarasını Giriniz: ";
    cin >> urun_no;

    sil(urun_no);
}

/* Ürün düzenleme fonksiyonu
 - Kullanıcıdan düzenlenecek mobilyanın adı istenir.
 - Kullanıcı onayıyla düzenleme işlemi gerçekleştirilir.
 - Yeni bilgiler girilerek mobilyanın adı, gelen adeti ve adet başına fiyatı güncellenir.*/

void duzenleme() {
    string urun_no;
    cout << "Düzeltmek İstediğiniz Ürün Numarasını Giriniz: ";
    cin >> urun_no;

    Mobilya* duzeltilecek = ara(urun_no);
    if (duzeltilecek) {
        cout << "\nDüzeltilecek Ürünün Bilgileri.. \n";
        cout << "Kategori: " << duzeltilecek->kategori << "\n";
        cout << "Numara: " << duzeltilecek->urun_no << "\n";
        cout << "Renk: " << duzeltilecek->renk << "\n";
        cout << "İsim: " << duzeltilecek->isim << "\n";
        cout << "Fiyat: " << duzeltilecek->fiyat << "\n";
        cout << "------------------------\n";

        int secım;
        cout << "Ürün Kaydını Düzenlemek İstiyor musunuz ? (1/0): ";
        cin >> secım;

        if (secım == 1) {
            cout << "Ürünün Kategorisini Girniz: ";
            cin >> duzeltilecek->kategori;
            cout << "Ürünün Ürün Numarası Girniz: ";
            cin >> duzeltilecek->urun_no;
            cout << "Ürünün Rengini Girniz: ";
            cin >> duzeltilecek->renk;
            cout << "Ürünün İsmini Girniz: ";
            cin >> duzeltilecek->isim;
            cout << "Ürünün Fiyatını Girniz: ";
            cin >> duzeltilecek->fiyat;
            cout << "\n";
            cout << "KAYIT DÜZENLENDİ ✓✓✓\n";
        } else {
            cout << "Düzenleme iptal edildi.\n";
        }
    } else {
        cout << "Kayıt Bulunamadı..\n";
    }
}

void dosya_oku()
    {
        ifstream dosya("mobilya_verileri.txt");
        if (dosya.is_open()) {
        while (!dosya.eof()) {
            Mobilya* yeni_mobilya = new Mobilya;
            dosya >> yeni_mobilya->kategori >> yeni_mobilya->urun_no >> yeni_mobilya->renk >> yeni_mobilya->isim >> yeni_mobilya->fiyat;
            yeni_mobilya->next = NULL;
            ekle(yeni_mobilya);
        }
        dosya.close();
      } else {
        cout << "Dosya açma hatası!\n";
      }
    }

void dosya_yaz()
   {
        ofstream dosya("mobilya_verileri.txt");
    if (dosya.is_open()) {
        Mobilya* temp = head;
        while (temp) {
            dosya << temp->kategori << " " << temp->urun_no << " " << temp->renk << " " << temp->isim << " " << temp->fiyat << endl;
            temp = temp->next;
        }
        dosya.close();
    } else {
        cout << "Dosya açma hatası!\n";
    }
    }

/*
   Ömer YılIdrım
   2312729003
   Veri Yapıları
   Mobilyacı Otomasyonu
*/