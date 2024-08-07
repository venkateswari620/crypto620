#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int dicty[26] = {0};
    int i, j, k;
    char ch;
    i = 0; j = 0;

    for (k = 0; k < strlen(key); k++) {
        ch = toupper(key[k]);
        if (ch != 'J' && dicty[ch - 'A'] == 0) {
            keyTable[i][j++] = ch;
            dicty[ch - 'A'] = 1;
            if (j == SIZE) {
                i++;
                j = 0;
            }
        }
    }

    for (k = 0; k < 26; k++) {
        if ('A' + k != 'J' && dicty[k] == 0) {
            keyTable[i][j++] = 'A' + k;
            if (j == SIZE) {
                i++;
                j = 0;
            }
        }
    }
}

void search(char keyTable[SIZE][SIZE], char a, char b, int *row1, int *col1, int *row2, int *col2) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                *row1 = i;
                *col1 = j;
            } else if (keyTable[i][j] == b) {
                *row2 = i;
                *col2 = j;
            }
        }
    }
}

void decrypt(char str[], char keyTable[SIZE][SIZE]) {
    int i, row1, col1, row2, col2;
    for (i = 0; i < strlen(str); i += 2) {
        search(keyTable, toupper(str[i]), toupper(str[i + 1]), &row1, &col1, &row2, &col2);
        if (row1 == row2) {
            str[i] = keyTable[row1][(col1 + SIZE - 1) % SIZE];
            str[i + 1] = keyTable[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            str[i] = keyTable[(row1 + SIZE - 1) % SIZE][col1];
            str[i + 1] = keyTable[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            str[i] = keyTable[row1][col2];
            str[i + 1] = keyTable[row2][col1];
        }
    }
}

int main() {
    char key[] = "MONARCHY";  // Example key
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char keyTable[SIZE][SIZE];
    generateKeyTable(key, keyTable);
    decrypt(message, keyTable);
    printf("Decrypted Message: %s\n", message);
    return 0;
}

