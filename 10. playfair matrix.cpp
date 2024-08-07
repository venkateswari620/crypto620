#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define the Playfair matrix
char playfairMatrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to find the position of a character in the Playfair matrix
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') {
        ch = 'I';
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (playfairMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to preprocess the plaintext
void preprocessPlaintext(char *plaintext) {
    int len = strlen(plaintext);
    char preprocessed[100];
    int k = 0;
    
    for (int i = 0; i < len; ++i) {
        if (isalpha(plaintext[i])) {
            preprocessed[k++] = toupper(plaintext[i]);
        }
    }
    preprocessed[k] = '\0';

    // Insert 'X' between repeated characters and at the end if necessary
    len = strlen(preprocessed);
    for (int i = 0; i < len; i += 2) {
        if (preprocessed[i] == preprocessed[i+1]) {
            for (int j = len; j > i; --j) {
                preprocessed[j] = preprocessed[j-1];
            }
            preprocessed[i+1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        preprocessed[len] = 'X';
        preprocessed[len+1] = '\0';
    }

    strcpy(plaintext, preprocessed);
}

// Function to encrypt the plaintext using Playfair cipher
void encrypt(char *plaintext, char *ciphertext) {
    preprocessPlaintext(plaintext);

    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(plaintext[i], &row1, &col1);
        findPosition(plaintext[i+1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = playfairMatrix[row1][(col1 + 1) % 5];
            ciphertext[i+1] = playfairMatrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            ciphertext[i] = playfairMatrix[(row1 + 1) % 5][col1];
            ciphertext[i+1] = playfairMatrix[(row2 + 1) % 5][col2];
        } else {
            ciphertext[i] = playfairMatrix[row1][col2];
            ciphertext[i+1] = playfairMatrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at  once.";
    char ciphertext[100];

    encrypt(plaintext, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

