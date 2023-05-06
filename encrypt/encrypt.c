#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define KEY_SIZE 32 // AES-256 key size in bytes

int encrypt_file(const char *input_file, const char *output_file, const unsigned char *key)
{
    // Initialize cipher context
    EVP_CIPHER_CTX *ctx;
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        return -1;
    }
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, NULL)) {
        return -1;
    }

    // Open input and output files
    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");
    if (!fin || !fout) {
        return -1;
    }

    // Read and encrypt input file in chunks
    unsigned char inbuf[4096], outbuf[4096 + EVP_MAX_BLOCK_LENGTH];
    int inlen, outlen;
    while ((inlen = fread(inbuf, 1, sizeof(inbuf), fin)) > 0) {
        if (1 != EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
            return -1;
        }
        fwrite(outbuf, 1, outlen, fout);
    }

    // Finalize encryption
    if (1 != EVP_EncryptFinal_ex(ctx, outbuf, &outlen)) {
        return -1;
    }
    fwrite(outbuf, 1, outlen, fout);

    // Clean up
    fclose(fin);
    fclose(fout);
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}

int main()
{
    // Generate random key
    unsigned char key[KEY_SIZE];
    if (1 != RAND_bytes(key, KEY_SIZE)) {
        return -1;
    }

    // Encrypt input file and write to output file
    const char *input_file = "plaintext.txt";
    const char *output_file = "ciphertext.enc"; 
    if (0 != encrypt_file(input_file, output_file, key)) {
        return -1;
    }

    printf("File encryption complete. Key: ");
    for (int i = 0; i < KEY_SIZE; i++) {
        printf("%02x", key[i]);
    }
    printf("\n");
    return 0;
}
