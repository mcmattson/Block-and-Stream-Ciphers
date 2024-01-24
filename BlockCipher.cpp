#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include "Cipher.h"

using namespace std;
// Block cipher
// TODO: The encryption would be a three step process : pad (if required) -> encrypt (using XOR) -> swap
// Your block size will be 128 bits. As mentioned earlier, if a block is found to be less than 128 bits, it should be
// padded with as many (0X81) bytes so as to make 128 bits or 16 bytes.

// TODO: Your algorithm will XOR the 128 bit data block with the 128 bit key in a bitwise manner, i.e. each bit of the
//  key starting from the left most bit will be XORed with each bit of a 128 bit data block, starting from the left hand
//  side.

// TODO: Your algorithm will then swap bytes of the XORed output using the following algorithm.
//  Let 'start' and 'end' be pointers which point to the start and end of the XORed output string.
//  For each byte of the key, starting from the left most byte or 0th byte, you calculate the following : (ASCII value of
//  the byte or character)mod2. This would give you either 0 or 1.
//  If the value is 0 you do not swap anything and move to the next byte of the ciphertext by incrementing the 'start'
//  pointer. Otherwise, you swap the byte pointed by the 'start' pointer with that pointed by the 'end' pointer. Then
//  increment the 'start' pointer so that it points to the next higher byte and decrement the 'end' pointer so that it
//  points to the next lower byte. If the keysize is exhausted, you restart from the first byte of the key. This process
//  is carried on until the 'start' and the 'end' pointers collide. The swap process stops and produces the required
//  encrypted output.

// TODO: The decryption process is also of three steps but proceeds in the reverse order as the encryption process :
//  swap -> decrypt (using XOR) -> remove padding (if required). The decrypted ouput should be written to the output file.
//  Because the decryption process occurs in the reverse direction of the encryption process, you cannot use the same
//  module to perform both, altough the underlying logic will be the same.

// Block Cipher - works differently for encode and decode
void BlockCiphered(char msg[], char key[], const char *mode, const char *outFile)
{
    ofstream oFile;
    // Message Variables
    int len = strlen(msg);

    // Key Variables
    int keyLen = strlen(key);
    unsigned char keyArr[keyLen + 1];
    strcpy(reinterpret_cast<char *>(keyArr), key);

    // Block and padding variables
    const char pad = 0x81;
    const int blockSize = 16;

    if (*mode == 'E')
    {
        int padding = blockSize - (len % blockSize);
        int newArrLen = len + padding;
        char *newArr = new char[newArrLen];
        unsigned char encryptedArr[newArrLen];

        // Pad
        memcpy(newArr, msg, len);
        memset(newArr + len, pad, padding);

        // XOR
        for (int i = 0; i < newArrLen; ++i)
        {
            newArr[i] = newArr[i] xor keyArr[i % keyLen];
        }

        // Copy msg into new Block
        memcpy(encryptedArr, newArr, newArrLen);

        unsigned char *startPtr = encryptedArr;
        unsigned char *endPtr = encryptedArr + newArrLen - 1;

        // Swap
        while (startPtr < endPtr)
        {
            for (int i = 0; i < keyLen; ++i)
            {
                if (keyArr[i] % 2 != 0 && startPtr < endPtr)
                {
                    swap(*startPtr, *endPtr);

                    endPtr--;
                }
                startPtr++;
            }
        }

        // Write to output
        oFile.open(outFile, ofstream::out | ofstream::trunc | ofstream::binary);
        oFile.write(reinterpret_cast<const char *>(encryptedArr), newArrLen);
        oFile.close();

        // delete new arr
        delete[] newArr;
    }
    else if (*mode == 'D')
    {
        unsigned char encryptedArr[len];
        memcpy(encryptedArr, msg, len);

        unsigned char *startPtr = encryptedArr;
        unsigned char *endPtr = encryptedArr + len - 1;

        // Swap
        while (startPtr < endPtr)
        {
            for (int i = 0; i < keyLen; ++i)
            {
                if (keyArr[i] % 2 != 0 && startPtr < endPtr)
                {
                    swap(*startPtr, *endPtr);

                    endPtr--;
                }
                startPtr++;
            }
        }

        // Debugging: Print after swap
        cout << "After Swap: ";
        for (int i = 0; i < len; i++)
            cout << encryptedArr[i];
        cout << endl;

        // XOR
        for (int i = 0; i < len; ++i)
        {
            encryptedArr[i] = encryptedArr[i] xor keyArr[i % keyLen];
        }

        // Debugging: Print after XOR
        cout << "After XOR: ";
        for (int i = 0; i < len; i++)
            cout << encryptedArr[i];
        cout << endl;

        // de-Pad
        int finalDataLen = len;
        for (int i = len; i > 0 && encryptedArr[i - 1] == pad; --i)
        {
            finalDataLen--;
        }

        // Write to output
        oFile.open(outFile, ofstream::out | ofstream::trunc | ofstream::binary);
        oFile.write(reinterpret_cast<const char *>(encryptedArr), finalDataLen);
        oFile.close();
    }
    else
    {
        printf("       ERROR: Invaild Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n");
        exit(1);
    }
}