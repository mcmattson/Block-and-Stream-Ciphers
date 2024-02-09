#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include "Cipher.h"

// Project: Programming Assignment 1
// Name: Matthew Mattson
// Date: January 22, 2024

using namespace std;

// Driver code
int main(int argc, const char **argv)
{

    // Check for the correct amount of arguments
    if (argc != 6)
    {
        printf("ERROR: Incorrect number of arguments.\n");
        printf("Usage: <program_name> <cipher type> <input filename> <output filename> <key> <mode>\n");
        printf("  <cipher type> - 'B' for Block Cipher or 'S' for Stream Cipher\n");
        printf("  <input filename> - Path to the input file\n");
        printf("  <output filename> - Path for the output file\n");
        printf("  <key> - Encryption/Decryption key\n");
        printf("  <mode> - 'E' for Encrypt or 'D' for Decrypt\n");
        printf("Example: main B input.txt output.txt COMPUTER76543210 E\n");
        exit(1);
    }

    // Message that need to encode - This needs to come from a file (input.txt) VIA argv[2]
    ifstream iFile;
    string inFilename = argv[2];
    iFile.open(inFilename, ios::binary | ios::ate);

    if (!iFile.is_open())
    {
        printf("       ERROR:Input File is not Valid or Does not exist.\n");
        exit(1);
    }

    // File Size
    streamsize size = iFile.tellg();
    iFile.seekg(0, ios::beg);

    // Allocate memory
    char *inputStr = new char[size + 1];

    // Read file and write into Array
    if (!iFile.read(inputStr, size))
    {
        printf("        ERROR: Failed to read file.\n");
        delete[] inputStr;
        exit(1);
    }
    inputStr[size] = '\0';
    iFile.close();

    // Take the key from argv[4];
    const char *keyArg = argv[4];
    auto key = keyArg;

    // File to output to - This needs to come from a file (output.txt) VIA argv[3]
    const char *outFilename = argv[3];

    // Generate a Key that is sufficient size to msg
    char *newKey = keyGen(inputStr, key);

    // Selection of Block('B') or Stream('S') VIA argv[1]
    char cipherFunction = *argv[1];

    // This will come from argv[5] could be 'E' or 'D'
    char mode = *argv[5];

    // Function call to determine Block or Stream cypher function
    if (cipherFunction == 'B')
    {
        BlockCiphered(inputStr, newKey, &mode, outFilename);
    }
    else if (cipherFunction == 'S')
    {
        StreamCiphered(inputStr, newKey, &mode, outFilename);
    }
    else
    {
        printf("       ERROR: Invalid cipher function - Please Enter either 'B' for Block Cipher or 'S' for Stream Cipher...\n");
        delete[] inputStr;
        delete[] newKey;
        exit(1);
    }

    // Delete open arrays
    delete[] inputStr;
    delete[] newKey;

    // End
    printf("\n");
    return 0;
}