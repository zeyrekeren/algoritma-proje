#include <stdio.h>

int main()
{
    FILE *kaynakDosya, *yedekDosya;
    char dosyaAdi[50];
    long konum;
    char karakter;
    long i;
    long a=0;

    while(1){
        printf("Ters kopyasi alinacak dosyanin adini giriniz: ");
        scanf("%s", dosyaAdi);
        kaynakDosya = fopen(dosyaAdi, "r");


        if (kaynakDosya == NULL) {
            printf("Okunacak dosyayi acma islemi basarisiz!\n");

        }
        else break;

    }

    yedekDosya = fopen("yedek.bak", "w");


    if (yedekDosya == NULL) {
        printf("Yedek dosya olusturma islemi basarisiz!\n");
        fclose(kaynakDosya);
        return 1;
    }


    fseek(kaynakDosya, 0, SEEK_END);


    konum = ftell(kaynakDosya);


    for (i = konum - 1; i >= 0; i--) {
        fseek(kaynakDosya, i, SEEK_SET);
        karakter = fgetc(kaynakDosya);
        if (karakter != '\n' && karakter != '\r')
        {
            fputc(karakter, yedekDosya);
        }
        else if (karakter == '\n') {
            a+=1;
            if (a==2){
                a=0;
                fputc('\n', yedekDosya);
            }

        }


    }



    fclose(kaynakDosya);
    fclose(yedekDosya);

    printf("Dosyanin tersi olan \"yedek.bak\" olusturuldu.\n");

    return 0;
}
