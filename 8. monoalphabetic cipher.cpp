#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function to remove duplicates from a string
void removeDuplicates(char* str) {
    int hash[256] = {0};
    int currentIndex = 0;
    int lastIndex = 0;

    while (str[currentIndex]) {
        char temp = str[currentIndex];
        if (hash[temp] == 0) {
            hash[temp] = 1;
            str[lastIndex++] = str[currentIndex];
        }
        currentIndex++;
    }
    str[lastIndex] = '\0';
}

// Function to generate the cipher sequence using a keyword
void generateCipherSequence(char* keyword, char* cipher) {
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphaIndex = 0;
    
    // Step 1: Copy the keyword to the cipher array, removing duplicates
    strcpy(cipher, keyword);
    removeDuplicates(cipher);
    int cipherLen = strlen(cipher);

    // Step 2: Add the remaining letters of the alphabet to the cipher array
    for (int i = 0; i < 26; i++) {
        if (!strchr(cipher, alphabet[i])) {
            cipher[cipherLen++] = alphabet[i];
        }
    }
    cipher[cipherLen] = '\0';
}

// Function to encrypt a plaintext message using the generated cipher sequence
void encrypt(char* plaintext, char* cipher, char* ciphertext) {
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; plaintext[i]; i++) {
        if (isalpha(plaintext[i])) {
            char upperChar = toupper(plaintext[i]);
            int index = strchr(alphabet, upperChar) - alphabet;
            ciphertext[i] = isupper(plaintext[i]) ? cipher[index] : tolower(cipher[index]);
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters remain the same
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char keyword[100], plaintext[100], cipher[27], ciphertext[100];
    
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    printf("Enter the plaintext message: ");
    scanf(" %[^\n]", plaintext);

    // Convert keyword to uppercase
    for (int i = 0; keyword[i]; i++) {
        keyword[i] = toupper(keyword[i]);
    }

    generateCipherSequence(keyword, cipher);

    printf("Generated cipher sequence: %s\n", cipher);

    encrypt(plaintext, cipher, ciphertext);

    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

