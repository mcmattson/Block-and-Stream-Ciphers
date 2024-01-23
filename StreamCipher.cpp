// Stream cipher

//  You will XOR your input stream with the following data
//  The key is (in ASCII, again) "COMPUTER76543210".
//  Bit 0 from the input file will be XORed with Bit 0 from the key
//  Bit 1 from the input file will be XORed with Bit 1 from the key
//  ...
//  Bit n-1 from the input file will be XORed with Bit n-1 from the key

//  If you reach the end of the key, start over from the beginning.

//  Note on the number of the bits. Since this is a stream, bit 0 is the first bit to arrive, bit 1 is the second
//  bit and so forth. That means the leftmost bit of the first byte is bit 0. Same with the key.

// Encryption and decryption will be performed with the same module that you design for the Stream Cipher. In other
//  words, you do not have have to design separate modules for encryption and decryption in the Stream Encryption Mode.

#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "Cipher.h"

// Project: Programming Assignment 1
// Name: Matthew Mattson
// Date: January 22, 2024

// Stream Cipher - works the same for encode and decode
void StreamCiphered(char msg[], char key[], const char *mode, const char *outFile)
{
    std::ofstream oFile;

    // Encrypt/Decrypt Arr Variables
    int EArrLen = strlen(reinterpret_cast<const char *>(msg));
    unsigned char encryptedArr[EArrLen + 1];

    // Message Variables
    int len = strlen(reinterpret_cast<const char *>(msg));
    unsigned char chArr[len + 1];

    // Key Variables
    int keyLen = strlen(reinterpret_cast<const char *>(key));
    unsigned char keyArr[keyLen + 1];

    // Select encrypt or decrypt from cmd line (does the same thing in Stream Cipher)
    if (*mode == 'E' || *mode == 'D')
    {
        strcpy(reinterpret_cast<char *>(keyArr), reinterpret_cast<const char *>(key));
        strcpy(reinterpret_cast<char *>(chArr), static_cast<const char *>(msg));
        
        for (int i = 0; i < EArrLen; ++i)
        {
            encryptedArr[i] = keyArr[i % keyLen] xor chArr[i];
        }

        oFile.open(outFile, std::ofstream::out | std::ofstream::trunc);
        // Print Values - Print to output.txt file
        for (int i = 0; i < EArrLen; i++)
        {
            oFile << encryptedArr[i];
        }
        oFile.close();

    }
    else
    {
        printf("       ERROR: Invaild Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n");
        exit(1);
    }
}