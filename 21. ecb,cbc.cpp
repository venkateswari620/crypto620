#include <stdio.h>
#include <string.h>
#include <mbedtls/aes.h>
#include <mbedtls/platform.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>

// Function prototypes
void encrypt_ecb(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, int length);
void encrypt_cbc(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int length);
void encrypt_cfb(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int length);
void pad(unsigned char *plaintext, int *length);
void print_hex(const char *label, const unsigned char *data, int length);

int main() {
    unsigned char key[16];
    unsigned char iv[16];
    unsigned char plaintext[128];
    unsigned char ciphertext[128];

    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;

    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0);

    // Random key and IV generation for demonstration
    mbedtls_ctr_drbg_random(&ctr_drbg, key, sizeof(key));
    mbedtls_ctr_drbg_random(&ctr_drbg, iv, sizeof(iv));

    // Example plaintext
    strcpy((char *)plaintext, "This is a secret message.");

    // Padding plaintext
    int length = strlen((char *)plaintext);
    pad(plaintext, &length);

    // Encryptions
    encrypt_ecb(plaintext, key, ciphertext, length);
    print_hex("ECB mode ciphertext", ciphertext, length);

    encrypt_cbc(plaintext, key, iv, ciphertext, length);
    print_hex("CBC mode ciphertext", ciphertext, length);

    encrypt_cfb(plaintext, key, iv, ciphertext, length);
    print_hex("CFB mode ciphertext", ciphertext, length);

    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);

    return 0;
}

void pad(unsigned char *plaintext, int *length) {
    int pad_length = 16 - (*length % 16);
    for (int i = *length; i < *length + pad_length; i++) {
        plaintext[i] = (i == *length) ? 0x80 : 0x00;
    }
    *length += pad_length;
}

void encrypt_ecb(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, int length) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);

    for (int i = 0; i < length; i += 16) {
        mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, plaintext + i, ciphertext + i);
    }

    mbedtls_aes_free(&aes);
}

void encrypt_cbc(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int length) {
    mbedtls_aes_context aes;
    unsigned char iv_copy[16];
    memcpy(iv_copy, iv, 16);

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, length, iv_copy, plaintext, ciphertext);

    mbedtls_aes_free(&aes);
}

void encrypt_cfb(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, int length) {
    mbedtls_aes_context aes;
    unsigned char iv_copy[16];
    size_t iv_off = 0;
    memcpy(iv_copy, iv, 16);

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    mbedtls_aes_crypt_cfb128(&aes, MBEDTLS_AES_ENCRYPT, length, &iv_off, iv_copy, plaintext, ciphertext);

    mbedtls_aes_free(&aes);
}

void print_hex(const char *label, const unsigned char *data, int length) {
    printf("%s: ", label);
    for (int i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

