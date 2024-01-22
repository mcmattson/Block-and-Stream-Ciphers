//Stream cipher

//TODO: You will XOR your input stream with the following data
// The key is (in ASCII, again) "COMPUTER76543210".
// Bit 0 from the input file will be XORed with Bit 0 from the key
// Bit 1 from the input file will be XORed with Bit 1 from the key
// ...
// Bit n-1 from the input file will be XORed with Bit n-1 from the key

//TODO: If you reach the end of the key, start over from the beginning.

//TODO: Note on the number of the bits. Since this is a stream, bit 0 is the first bit to arrive, bit 1 is the second
// bit and so forth. That means the leftmost bit of the first byte is bit 0. Same with the key.

//TODO: Encryption and decryption will be performed with the same module that you design for the Stream Cipher. In other
// words, you do not have have to design separate modules for encryption and decryption in the Stream Encryption Mode.

#include <iostream>
#include <cstring>
#include <fstream>
#include<bits/stdc++.h>
#include "Cipher.h"

//Project: Programming Assignment 1
//Name: Matthew Mattson
//Date: September 11, 2022

using namespace std;


// Stream Cipher - works the same for encode and decode
void StreamCiphered(char msg[], char key[], const char *mode, const char *outFile) {
    ofstream oFile;

    //Encrypt/Decrypt Arr Variables
    int EArrLen = strlen(reinterpret_cast<const char *>(msg));
    unsigned char encryptedArr[EArrLen + 1];

    //Message Variables
    int len = strlen(reinterpret_cast<const char *>(msg));
    unsigned char chArr[len + 1];

    //Key Variables
    int keyLen = strlen(reinterpret_cast<const char *>(key));
    unsigned char keyArr[keyLen + 1];

    //Select encrypt or decrypt from cmd line (does the same thing in Stream Cipher)
    switch (*mode) {
        case 'E':

            strcpy(reinterpret_cast<char *>(keyArr), reinterpret_cast<const char *>(key));
            strcpy(reinterpret_cast<char *>(chArr), reinterpret_cast<const char *>(msg));
            //================== FOR DEBUGGING =====================//
            //Print Values
            /*cout << "\nKeyArr: ";
            for (int i = 0; i < keyLen; i++) {
                printf("%c", keyArr[i]);
            }
            cout << "\n        ";
            for (int i = 0; i < keyLen; i++) {
                printf("%i ", valueOfChar(keyArr[i]));
            }
            cout << "\n\n";

            //Print Values

            cout << "msgArr: ";
            for (int i = 0; i < len; i++) {
                printf("%c", valueOfChar(chArr[i]));
            }
            cout << "\n        ";
            for (int i = 0; i < len; i++) {
                printf("%i ", valueOfChar(chArr[i]));
            }
            cout << "\n\n";
            cout << "E-Arr : ";*/


            // ================ END DEBUGGING =================//

            // ==============Encrypt/Decrypt driver ============//

            //XOR Each char in the two arrays
            for (int i = 0; i < EArrLen; ++i) {
                encryptedArr[i] = keyArr[i] xor chArr[i];
            }

            //Replace unprintable ASCII chars
            for (int i = 0; i < EArrLen; ++i) {
                if (encryptedArr[i] < 32) {
                    encryptedArr[i] = '\x81';
                } else if (encryptedArr[i] > 128) {
                    encryptedArr[i] = '\x81';
                } else {
                    encryptedArr[i] = encryptedArr[i];
                }

            }
            oFile.open(outFile, fstream::in | fstream::out | fstream::trunc);
            //Print Values - Print to output.txt file
            for (int i = 0; i < EArrLen; i++) {
                oFile << encryptedArr[i];
            }
            oFile.close();

            //================== FOR DEBUGGING =====================//
            /* cout << "\n        ";
             for (int i = 0; i < EArrLen; i++) {
                 printf("%i ", valueOfChar(encryptedArr[i]));
             }
             cout << "\n";*/
            // ================ END DEBUGGING =================//
            break;
        case 'D':
            strcpy(reinterpret_cast<char *>(keyArr), reinterpret_cast<const char *>(key));
            strcpy(reinterpret_cast<char *>(chArr), reinterpret_cast<const char *>(msg));
            //================== FOR DEBUGGING =====================//
            //Print Values
            /*cout << "\nKeyArr: ";
            for (int i = 0; i < keyLen; i++) {
                printf("%c", keyArr[i]);
            }
            cout << "\n        ";
            for (int i = 0; i < keyLen; i++) {
                printf("%i ", valueOfChar(keyArr[i]));
            }
            cout << "\n\n";

            //Print Values

            cout << "msgArr: ";
            for (int i = 0; i < len; i++) {
                printf("%c", valueOfChar(chArr[i]));
            }
            cout << "\n        ";
            for (int i = 0; i < len; i++) {
                printf("%i ", valueOfChar(chArr[i]));
            }
            cout << "\n\n";
            cout << "E-Arr : ";
             */

            // ================ END DEBUGGING =================//

            // ==============Encrypt/Decrypt driver ============//

            //XOR Each char in the two arrays
            for (int i = 0; i < EArrLen; ++i) {
                encryptedArr[i] = keyArr[i] xor chArr[i];
            }

            //Replace unprintable ASCII chars
            for (int i = 0; i < EArrLen; ++i) {
                if (encryptedArr[i] < 32) {
                    encryptedArr[i] = '\x81';
                } else if (encryptedArr[i] > 128) {
                    encryptedArr[i] = '\x81';
                } else {
                    encryptedArr[i] = encryptedArr[i];
                }

            }
            oFile.open(outFile, fstream::in | fstream::out | fstream::trunc);
            //Print Values - Print to output.txt file
            for (int i = 0; i < EArrLen; i++) {
                oFile << encryptedArr[i];
            }
            oFile.close();

            //================== FOR DEBUGGING =====================//
            /* cout << "\n        ";
             for (int i = 0; i < EArrLen; i++) {
                 printf("%i ", valueOfChar(encryptedArr[i]));
             }
             cout << "\n";*/
            // ================ END DEBUGGING =================//
            break;
        default:
            printf("       ERROR: Invaild Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n");
            exit(1);
    }
}