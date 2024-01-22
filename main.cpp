#include <iostream>
#include <cstring>
#include <fstream>
#include<bits/stdc++.h>
#include <cmath>
#include "Cipher.h"

//Project: Programming Assignment 1
//Name: Matthew Mattson
//Date: September 11, 2022

using namespace std;

// Driver code
int main(int argc, const char **argv) {

    //Check for the correct amount of arguments
    if (argc != 6) {
        printf("       ERROR:Incorrect amount of arguments\n");//TODO: REDO WITH USAGE EXAMPLE
        exit(1);
    }

    // Take the key from argv[4];
    const char *keyArg = NULL;
    keyArg = argv[4];
    auto key = keyArg;

    // File to output to - This needs to come from a file (output.txt) VIA argv[3]
    const char *outFilename = argv[3];

    // Message that need to encode - This needs to come from a file (input.txt) VIA argv[2]
    ifstream iFile;
    string inFilename = argv[2];
    char inputStr[1000] = " ";

    //Read file and write into Array
    iFile = ifstream(inFilename, ios_base::in);
    if (iFile.is_open()) {
        char c;
        int i = 0;

        //Write file to Array
        while (iFile.get(c)) {
            inputStr[i] = c;
            i++;
        }
        //Close File
        iFile.close();
        inputStr[i] = '\0';
    } else {
        printf("       ERROR: File could not be open or does not exist!\n");
        exit(1);
    }
    //Generate a Key that is sufficient size to msg
    char *newKey = keyGen(inputStr, key);

    // Selection of Block('B') or Stream('S') VIA argv[1]
    char cipherFunction = *argv[1];

    // This will come from argv[5] could be 'E' or 'D'
    char mode = *argv[5];

    //If file is open
    if (!iFile.is_open()) {
        // Function call to determine Block or Stream cypher function
        switch (cipherFunction) {
            case 'B':
                BlockCiphered(inputStr, newKey, &mode, outFilename);
                break;
            case 'S':
                StreamCiphered(inputStr, newKey, &mode, outFilename);
                break;
            default:
                printf("       ERROR: Invalid cipher function - Please Enter either 'B' for Block Cipher or 'S' for Stream Cipher...\n");
                exit(1);
        }
        //Else Error with message
    } else {
        printf("       ERROR:Input File is not Valid or Does not exist.\n");
        exit(1);
    }

    //Delete open array
    delete[] newKey;

    //End
    printf("\n");
    return 0;
}