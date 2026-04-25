#include <stdio.h>
#include <stdlib.h>

// 1. Tahtayý Yazdýr (printBoard)
void printBoard(int tahta[3][3]) {
    printf("\n+---+---+---+\n");
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("|");
            if (tahta[i][j] == 0)
                printf("   "); // 0'ý boþluk göster
            else
                printf(" %d ", tahta[i][j]);
        }
        printf("|\n+---+---+---+\n");
    }
}

// 2. Boþluðu Bul (boslukbul)
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
void move(int tahta[3][3], char yon) {
    int bossatir, bossutun;
    boslukbul(tahta, &bossatir, &bossutun);

    int hedefSatir = bossatir;
    int hedefSutun = bossutun;

    if (yon == 'w' || yon == 'W') hedefSatir--;
    else if (yon == 's' || yon == 'S') hedefSatir++;
    else if (yon == 'a' || yon == 'A') hedefSutun--;
    else if (yon == 'd' || yon == 'D') hedefSutun++;
    else return;

    if (hedefSatir >= 0 && hedefSatir < 3 && hedefSutun >= 0 && hedefSutun < 3) {
        int gecici = tahta[bossatir][bossutun];
        tahta[bossatir][bossutun] = tahta[hedefSatir][hedefSutun];
        tahta[hedefSatir][hedefSutun] = gecici;
    } else {
        printf("\n[HATA] Gecersiz hamle!\n");
    }
}

// 4. Çözüldü mü? (isSolved)
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

// 5. Ana Yönetici (main)
int main() {
    int tahta[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 0, 8} // Çözülmeye yakýn bir örnek
    };
    char hamle;

    while (1) {

        printBoard(tahta);

        if (isSolved(tahta)) {
            printf("\nTEBRIKLER! Oyunu kazandiniz.\n");
            break;
        }

        printf("Hamle (W-A-S-D, Cikis icin Q): ");
        scanf(" %c", &hamle);

        if (hamle == 'q' || hamle == 'Q') break;

        move(tahta, hamle);
    }

    return 0;
}
