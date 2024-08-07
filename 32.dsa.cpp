#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to simulate a DSA signature with a random k
void dsa_sign(const char *message, unsigned char *signature, size_t sig_len) {
    srand(time(NULL)); // Seed for random number generation
    for (size_t i = 0; i < sig_len; i++) {
        signature[i] = message[i % strlen(message)] ^ (rand() % 256);
    }
}

// Function to simulate an RSA signature (same result for same message)
void rsa_sign(const char *message, unsigned char *signature, size_t sig_len) {
    for (size_t i = 0; i < sig_len; i++) {
        signature[i] = message[i % strlen(message)] ^ 0xAA; // Using a fixed key for XOR
    }
}

int main() {
    // Message to be signed
    const char *message = "This is a test message.";
    size_t message_len = strlen(message);
    size_t sig_len = 32; // Length of the simulated signature

    // Buffers for signatures
    unsigned char dsa_sig1[32];
    unsigned char dsa_sig2[32];
    unsigned char rsa_sig1[32];
    unsigned char rsa_sig2[32];

    // Generate DSA signatures
    dsa_sign(message, dsa_sig1, sig_len);
    dsa_sign(message, dsa_sig2, sig_len);

    // Generate RSA signatures
    rsa_sign(message, rsa_sig1, sig_len);
    rsa_sign(message, rsa_sig2, sig_len);

    // Print DSA signatures
    printf("DSA Signature 1: ");
    for (size_t i = 0; i < sig_len; i++) printf("%02x", dsa_sig1[i]);
    printf("\n");

    printf("DSA Signature 2: ");
    for (size_t i = 0; i < sig_len; i++) printf("%02x", dsa_sig2[i]);
    printf("\n");

    // Print RSA signatures
    printf("RSA Signature 1: ");
    for (size_t i = 0; i < sig_len; i++) printf("%02x", rsa_sig1[i]);
    printf("\n");

    printf("RSA Signature 2: ");
    for (size_t i = 0; i < sig_len; i++) printf("%02x", rsa_sig2[i]);
    printf("\n");

    return 0;
}
