#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
 // tahtayı temizleme
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// İnversiyon sayısını hesapla
int inversiyonSay(int tahta[3][3]) {
    // Tahtayı tek boyutlu diziye çevir (0'ı atla)
    int dizi[8];
    int k = 0, i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (tahta[i][j] != 0)
                dizi[k++] = tahta[i][j];

    // İnversiyon say
    int inv = 0;
    for (i = 0; i < 8; i++)
        for (j = i + 1; j < 8; j++)
            if (dizi[i] > dizi[j])
                inv++;

    return inv;
}

// Çözülebilir mi?
int cozulebilirMi(int tahta[3][3]) {
    return (inversiyonSay(tahta) % 2 == 0);
}
// 1. Tahtayi Yazdir (printBoard)
void printBoard(int tahta[3][3]) {
    printf("\n+---+---+---+\n");
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("|");
            if (tahta[i][j] == 0)
                printf("   "); // 0'i bosluk goster
            else
                printf(" %d ", tahta[i][j]);
        }
        printf("|\n+---+---+---+\n");
    }
}

// 2. Bosluku Bul (boslukbul)
void boslukbul(int tahta[3][3], int *satir, int *sutun) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tahta[i][j] == 0) {
                *satir = i;
                *sutun = j;
                return;
            }
        }
    }
}

// 3. Hareket Et (move)
int move(int tahta[3][3], char yon) {
    int bossatir, bossutun;
    boslukbul(tahta, &bossatir, &bossutun);

    int hedefSatir = bossatir;
    int hedefSutun = bossutun;

    if (yon == 'w' || yon == 'W') hedefSatir--;
    else if (yon == 's' || yon == 'S') hedefSatir++;
    else if (yon == 'a' || yon == 'A') hedefSutun--;
    else if (yon == 'd' || yon == 'D') hedefSutun++;
    else return 0;

    if (hedefSatir >= 0 && hedefSatir < 3 && hedefSutun >= 0 && hedefSutun < 3) {
        int gecici = tahta[bossatir][bossutun];
        tahta[bossatir][bossutun] = tahta[hedefSatir][hedefSutun];
        tahta[hedefSatir][hedefSutun] = gecici;
        return 1;
    } else {
        return 0;
    }
}

// 4. ??z?ld? m?? (isSolved)
int isSolved(int tahta[3][3]) {
    int expectedValue = 1;
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == 2 && j == 2) {
                return (tahta[i][j] == 0);
            }
            if (tahta[i][j] != expectedValue) {
                return 0;
            }
            expectedValue++;
        }
    }
    return 1;
}
void karistir(int tahta[3][3]) {
    // Geçerli hamleler: w s a d
    char yonler[] = {'w', 's', 'a', 'd'};
    int i;
    for (i = 0; i < 1000; i++) {          // 1000 rastgele hamle yap
        int r = rand() % 4;               // 0-3 arası rastgele sayı
        move(tahta, yonler[r]);           // o yönde hamle yap
    }
}

// 5. Ana Yonetici (main)
int main() {
	srand(time(NULL)); 
    int tahta[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0} // cözülmüs vers
    };
     
	karistir(tahta);
    char hamle;
    int hamleSayisi = 0;
    int hatavar = 0; 

    while (1) {
		clearScreen(); 
        printBoard(tahta);
        printf("Hamle sayisi: %d\n", hamleSayisi);

        if (isSolved(tahta)) {
            printf("\nTEBRIKLER! Oyunu kazandiniz.\n");
            break;
        }
         if (hatavar)                         
            printf("[HATA] Gecersiz hamle!\n");
        else
            printf("\n");

        printf("Hamle (W-A-S-D, Cikis icin Q): ");
        scanf(" %c", &hamle);

        if (hamle == 'q' || hamle == 'Q') break;

        int basarili = move(tahta, hamle);
        if (basarili) hamleSayisi++;
        hatavar = !basarili;
    }

    return 0;
}