//
// Created by Don Koshy on 2022/10/10.
#include "stdio.h"
#include <float.h>
#include <string.h>
#include <ctype.h>
#include "stdlib.h"

#define MAX_FILE_NAME 100

FILE *fptr;
char buffer[500];
char buff2[1000];

void Decompression (char *Out_size, char *Compressed_size, unsigned CompressedLength) {

    unsigned long long Buffer = 0;
    char Bits = 0;
    while (CompressedLength) {
        while (CompressedLength && Bits < 7 * 8) {
            Buffer |= (unsigned long long)*Compressed_size++ << Bits;
            Bits += 8;
            --CompressedLength;
        }
        while (Bits > 0) {
            *Out_size++ = Buffer & 0x7F;
            Buffer >>= 7;
            Bits -= 7;
        }

        Bits = 0;
        Buffer = 0;
    }
}

void encryptDecrypt(char*, char*, char*);

void encryptDecrypt(char *input, char *output, char *key)
{
    for (int i = 0; i < strlen(input); ++i)
        output[i] = input [i] ^ key [i % strlen(key)];
}

int main(void){
    FILE *fp;
    FILE *fp2;
    int count = 0;  // Line counter
    char filename[MAX_FILE_NAME];
    char c;
    char encryptedMessage; // encryptedMessage of line for reading in file

    char Message[count];
    char key[50] = "1234";
    int const compressedSize = (int)((float)(sizeof(buffer))*(float)(6/(float)8));
    const char compressedBytes[compressedSize];
    char decompressedSize[sizeof (Message)];

// Get file name from user. The file should be
// either in current folder or complete path should be provided
    printf("Enter file name to be decrypted and decompressed: ");
    scanf("%s", filename);
// Open the file
    fp = fopen(filename, "r");

// Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 0;
    }

// Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    }
// Close the file
    fclose(fp);
    //printf("The file %s has %d lines\n ", filename, count);

//read in file to be decrypted and decompressed

// Open the file
    fp = fopen(filename, "r");
    if (fp  == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    int i=0;
    fp2 = fopen("outputAfterProcessing.txt","w");

    while( i<count ){
        fscanf(fp,"%c", &encryptedMessage);     //reading in each line from encrypted file and storing in encryptedMessage

        char decryptedMessage[strlen(compressedBytes) + 1];
        memset(decryptedMessage, '\0', sizeof(decryptedMessage));
        encryptDecrypt(&encryptedMessage, decryptedMessage, key);

        //fprintf(fp2,"%s", decryptedMessage);

        Decompression(decompressedSize,  decryptedMessage , compressedSize);
        printf("%s", buff2);
        printf("\n");
        //fprintf(fp2,"%s", buff2);
        i++;
    }
    printf("%d", count);
    //printf("%s", buff2);
    fclose(fp);
    fclose(fp2);
    return 0;

}
//
