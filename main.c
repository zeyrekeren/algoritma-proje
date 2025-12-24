#include <stdio.h>

int main()
{
    // FILE türü, C dilinde dosyalarla işlem yapabilmek için kullanılır.
    // Dosyalar adres (pointer) ile temsil edildiği için FILE * şeklinde tanımlanır.
    FILE *kaynakDosya, *yedekDosya;

    // Kullanıcıdan alınacak dosya adını tutmak için karakter dizisi
    char dosyaAdi[50];

    // Dosya içindeki konumları ve boyutu tutmak için long türünde değişken
    long konum;

    // Dosyadan okunan her bir karakteri tutacak değişken
    char karakter;

    // Döngüde sondan başa ilerlemek için sayaç
    long i;

    // Satır sonu karakterlerini kontrol etmek için kullanılan sayaç
    long a = 0;

    // Kullanıcı doğru dosya adını girene kadar çalışacak sonsuz döngü
    while(1){
        printf("Ters kopyasi alinacak dosyanin adini giriniz: ");
        scanf("%s", dosyaAdi);

        // Kullanıcının girdiği dosyayı okuma modunda açıyoruz
        kaynakDosya = fopen(dosyaAdi, "r");

        // Eğer dosya açılamazsa fopen NULL döndürür
        if (kaynakDosya == NULL) {
            printf("Okunacak dosyayi acma islemi basarisiz!\n");
            // break yok, döngü başa sarar ve tekrar dosya adı ister
        }
        else break; // Dosya başarıyla açıldıysa döngüden çık
    }

    // Ters çevrilmiş metnin yazılacağı yedek dosyayı oluşturuyoruz
    yedekDosya = fopen("yedek.bak", "w");

    // Eğer yedek dosya oluşturulamazsa hata veriyoruz
    if (yedekDosya == NULL) {
        printf("Yedek dosya olusturma islemi basarisiz!\n");
        fclose(kaynakDosya);
        return 1;
    }

    // Dosya imlecini dosyanın sonuna götürüyoruz
    fseek(kaynakDosya, 0, SEEK_END);

    // İmlecin bulunduğu konumu alarak dosyanın boyutunu öğreniyoruz
    konum = ftell(kaynakDosya);

    // Dosyayı sondan başa doğru karakter karakter okuyacağımız döngü
    for (i = konum - 1; i >= 0; i--) {

        // İmleci dosyanın i. byte'ına getiriyoruz
        fseek(kaynakDosya, i, SEEK_SET);

        // O konumdaki karakteri okuyoruz
        karakter = fgetc(kaynakDosya);

        // Eğer okunan karakter satır sonu değilse direkt yaz
        if (karakter != '\n' && karakter != '\r')
        {
            fputc(karakter, yedekDosya);
        }
        // Eğer satır sonu karakteri ise kontrol ediyoruz
        else if (karakter == '\n') {
            a++; // Satır sonu sayısını artır
            // Çift satır kaymasını önlemek için her iki '\n'de bir yazdır
            if (a == 2){
                a = 0;
                fputc('\n', yedekDosya);
            }
        }
    }

    // Dosyalarla işimiz bittiği için kapatıyoruz
    fclose(kaynakDosya);
    fclose(yedekDosya);

    // İşlemin başarılı olduğunu kullanıcıya bildiriyoruz
    printf("Dosyanin tersi olan \"yedek.bak\" olusturuldu.\n");

    return 0;
}
