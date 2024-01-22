#include <iostream>
#include <cstring>
#include <fstream>
#include<bits/stdc++.h>
#include <cmath>
#include "Cipher.h"

using namespace std;
// Block cipher
//TODO: The encryption would be a three step process : pad (if required) -> encrypt (using XOR) -> swap
// Your block size will be 128 bits. As mentioned earlier, if a block is found to be less than 128 bits, it should be
// padded with as many (0X81) bytes so as to make 128 bits or 16 bytes.

//TODO: Your algorithm will XOR the 128 bit data block with the 128 bit key in a bitwise manner, i.e. each bit of the
// key starting from the left most bit will be XORed with each bit of a 128 bit data block, starting from the left hand
// side.

//TODO: Your algorithm will then swap bytes of the XORed output using the following algorithm.
// Let 'start' and 'end' be pointers which point to the start and end of the XORed output string.
// For each byte of the key, starting from the left most byte or 0th byte, you calculate the following : (ASCII value of
// the byte or character)mod2. This would give you either 0 or 1.
// If the value is 0 you do not swap anything and move to the next byte of the ciphertext by incrementing the 'start'
// pointer. Otherwise, you swap the byte pointed by the 'start' pointer with that pointed by the 'end' pointer. Then
// increment the 'start' pointer so that it points to the next higher byte and decrement the 'end' pointer so that it
// points to the next lower byte. If the keysize is exhausted, you restart from the first byte of the key. This process
// is carried on until the 'start' and the 'end' pointers collide. The swap process stops and produces the required
// encrypted output.

//TODO: The decryption process is also of three steps but proceeds in the reverse order as the encryption process :
// swap -> decrypt (using XOR) -> remove padding (if required). The decrypted ouput should be written to the output file.
// Because the decryption process occurs in the reverse direction of the encryption process, you cannot use the same
// module to perform both, altough the underlying logic will be the same.

// Block Cipher - works differently for encode and decode
void BlockCiphered(char msg[], char key[], const char *mode, const char *outFile) {
    ofstream oFile;

    //Arr Variables
    int EArrLen = strlen(reinterpret_cast<const char *>(msg));
    unsigned char encryptedArr[EArrLen];

    //Message Variables
    int len = strlen(reinterpret_cast<const char *>(msg));
    //unsigned char chArr[len + 1];

    //Key Variables
    int keyLen = strlen(reinterpret_cast<const char *>(key));
    unsigned char keyArr[keyLen + 1];

    //Block and padding variables
    bitset<128> BLOCK;
    char pad = '\x81';
    int blockSize = sizeof(BLOCK);
    int blockDiff = 0;
    char arrPadding[blockDiff * 16];
    float totalBlocks = 0;

    //Total Blocks needed
    if (ceil(len % blockSize) > 0) {
        totalBlocks = ceil((float) len / (float) blockSize);
    } else {
        totalBlocks = 1;
    }
    int totalBlocksB = totalBlocks * 16;

    blockDiff = totalBlocksB - len;

    //Padding for Block
    for (int i = 0; i < blockDiff; i++) {
        arrPadding[i] = pad;
    }

    // Copy msg into new Block
    char *newArr = new char[strlen(arrPadding) + strlen(msg) + 1];
    strcpy(newArr, msg);
    strcat(newArr, arrPadding);

    int newArrLen = strlen(newArr);
    blockDiff = blockSize % newArrLen;

    // Copy padded Block into Encrypted Array
    strcpy(reinterpret_cast<char *>(encryptedArr), newArr);

    //delete new arr
    delete[] newArr;

    //pointers for 'start' and 'end' for byte swap
    int *startPtr;
    int *endPtr;

    startPtr = reinterpret_cast<int *>(encryptedArr);
    endPtr = reinterpret_cast<int *>(&encryptedArr[EArrLen - 1]);
    //Select encrypt or decrypt from cmd line (does the same thing in Stream Cipher)
    switch (*mode) {
        case 'E':
            //TODO: pad (if required) -> encrypt (using XOR) -> swap
            strcpy(reinterpret_cast<char *>(keyArr), reinterpret_cast<const char *>(key));

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

            cout << "encryptedArr: ";
            for (int i = 0; i < len; i++) {
                printf("%c", encryptedArr[i]);
            }
            cout << "\n        ";
            for (int i = 0; i < len; i++) {
                printf("%i ", valueOfChar(encryptedArr[i]));
            }
            cout << "\n\n";
            cout << "E-Arr : ";*/
            // ================ END DEBUGGING =================//

            // ==============Encrypt driver ============//
            //Your algorithm will XOR the 128 bit data block with the 128 bit key in a bitwise manner, i.e. each bit of
            // the key starting from the left most bit will be XORed with each bit of a 128 bit data block, starting from
            // the left hand side.
            for (int i = 0; i < EArrLen; i++) {
                encryptedArr[i] = encryptedArr[i] xor keyArr[i];
            }
            //XOR Each char in the two arrays
            for (int i = 0; i < EArrLen; i++) {
                //For each byte of the key, starting from the left most byte or 0th byte, you calculate the following :
                // (ASCII value of the byte or character)mod2. This would give you either 0 or 1.
                if ((key[i] % 2) == 0) {
                    //If the value is 0 you do not swap anything
                    // move to the next byte of the ciphertext by incrementing the 'start' pointer.
                    //cout << "Value = 0 | Moving to next point...\n";
                    startPtr++;
                    //cout << "startPtr = " << *startPtr << ", endPtr = " << *endPtr << "\n\n";

                    // end once both 'start' and 'end' pointers collide --> print
                } else if (startPtr == endPtr) {
                    //cout << "Pointers Collided\n";
                    exit(1);

                } else {
                    //Otherwise, you swap the byte pointed by the 'start' pointer with that pointed by the 'end' pointer.
                    //cout << "Before swap, startPtr = " << startPtr << ", endPtr = " << &endPtr << endl;
                    swap(startPtr, endPtr);
                    //cout << "After swap, startPtr = " << startPtr << ", endPtr = " << &endPtr << endl;

                    //cout << "Recording...\n";
                    swap(endPtr,startPtr);
                    //Then increment the 'start' pointer so that it points to the next higher byte
                   // cout << "Move 'Start' pointer... \n";
                    startPtr++;
                    //cout << "'Start' pointer at:";
                    //cout << startPtr << "\n";

                    //decrement the 'end' pointer so that it points to the next lower byte.
                    //cout << "Move 'End' pointer... " << endl;
                    endPtr--;
                    //cout << "'End' pointer at:";
                    //cout << endPtr << "\n\n";
                }
            }
            //} else {
            /*cout << "\n-------------End---------------\n";
            for (int i = 0; i < 1; i++) {
                cout << "&encryptedArr[" << i << "] = " << &encryptedArr[i] << endl;
            }*/

            for (int i = 0; i < EArrLen; ++i) {
                encryptedArr[i] = keyArr[i] xor encryptedArr[i];
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
            // }
            //================== FOR DEBUGGING =====================//
            /* cout << "\n        ";
             for (int i = 0; i < EArrLen; i++) {
                 printf("%i ", valueOfChar(encryptedArr[i]));
             }
             cout << "\n";*/
            // ================ END DEBUGGING =================//
            break;
        case 'D':
            //TODO: pad (if required) -> encrypt (using XOR) -> swap
            strcpy(reinterpret_cast<char *>(keyArr), reinterpret_cast<const char *>(key));

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

            cout << "encryptedArr: ";
            for (int i = 0; i < len; i++) {
                printf("%c", encryptedArr[i]);
            }
            cout << "\n        ";
            for (int i = 0; i < len; i++) {
                printf("%i ", valueOfChar(encryptedArr[i]));
            }
            cout << "\n\n";
            cout << "E-Arr : ";*/
            // ================ END DEBUGGING =================//

            // ==============Encrypt driver ============//
            //Your algorithm will XOR the 128 bit data block with the 128 bit key in a bitwise manner, i.e. each bit of
            // the key starting from the left most bit will be XORed with each bit of a 128 bit data block, starting from
            // the left hand side.
            for (int i = 0; i < EArrLen; i++) {
                encryptedArr[i] = encryptedArr[i] xor keyArr[i];
            }
            //XOR Each char in the two arrays
            for (int i = 0; i < EArrLen; i++) {
                //For each byte of the key, starting from the left most byte or 0th byte, you calculate the following :
                // (ASCII value of the byte or character)mod2. This would give you either 0 or 1.
                if ((key[i] % 2) == 0) {
                    //If the value is 0 you do not swap anything
                    // move to the next byte of the ciphertext by incrementing the 'start' pointer.
                    //cout << "Value = 0 | Moving to next point...\n";
                    startPtr++;
                    //cout << "startPtr = " << *startPtr << ", endPtr = " << *endPtr << "\n\n";

                    // end once both 'start' and 'end' pointers collide --> print
                } else if (startPtr == endPtr) {
                    //cout << "Pointers Collided\n";
                    exit(1);

                } else {
                    //Otherwise, you swap the byte pointed by the 'start' pointer with that pointed by the 'end' pointer.
                    //cout << "Before swap, startPtr = " << startPtr << ", endPtr = " << &endPtr << endl;
                    swap(startPtr, endPtr);
                    //cout << "After swap, startPtr = " << startPtr << ", endPtr = " << &endPtr << endl;

                    //cout << "Recording...\n";
                    swap(endPtr,startPtr);
                    //Then increment the 'start' pointer so that it points to the next higher byte
                    // cout << "Move 'Start' pointer... \n";
                    startPtr++;
                    //cout << "'Start' pointer at:";
                    //cout << startPtr << "\n";

                    //decrement the 'end' pointer so that it points to the next lower byte.
                    //cout << "Move 'End' pointer... " << endl;
                    endPtr--;
                    //cout << "'End' pointer at:";
                    //cout << endPtr << "\n\n";
                }
            }
            //} else {
            /*cout << "\n-------------End---------------\n";
            for (int i = 0; i < 1; i++) {
                cout << "&encryptedArr[" << i << "] = " << &encryptedArr[i] << endl;
            }*/

            for (int i = 0; i < EArrLen; ++i) {
                encryptedArr[i] = keyArr[i] xor encryptedArr[i];
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
            // }
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