#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

void swapBytes(unsigned char &a, unsigned char &b)
{
    unsigned char temp = a;
    a = b;
    b = temp;
}

char *keyGen(const char *msg, const char *key)
{
    size_t keyLength = strlen(key);
    char *newKey = new char[keyLength + 1];
    strcpy(newKey, key);
    return newKey;
}

void BlockCiphered(const char *msg, char *key, const char *mode, const char *outFile)
{
    int keyLen = strlen(key);
    unsigned char keyArr[keyLen + 1];
    // Assuming key is of correct length (16 bytes for 128 bits) and mode is 'E' for encryption
    if (*mode == 'E')
    {
        ofstream oFile;

        // Message Variables
        int len = strlen(msg);

        // Key Variables
        strcpy(reinterpret_cast<char *>(keyArr), key);

        // Block and padding variables
        const char pad = 0x81;
        const int blockSize = 16;

        int padding = blockSize - (len % blockSize);
        int newArrLen = len + (padding ? padding : blockSize); // Ensure padding for alignment
        unsigned char *newArr = new unsigned char[newArrLen];

        // Pad and XOR
        memcpy(newArr, msg, len);
        memset(newArr + len, pad, newArrLen - len); // Apply padding

        for (int i = 0; i < newArrLen; ++i)
        {
            newArr[i] ^= keyArr[i % keyLen]; // XOR operation
        }

        unsigned char *startPtr = newArr;
        unsigned char *endPtr = newArr + newArrLen - 1;

        // Swap
        while (startPtr < endPtr)
        {
            for (int i = 0; i < keyLen && startPtr < endPtr; ++i)
            {
                if (keyArr[i] % 2 != 0)
                {
                    swapBytes(*startPtr, *endPtr);
                    endPtr--;
                }
                startPtr++;
            }
        }

        // Write to output
        oFile.open(outFile, ios::out | ios::binary);
        if (!oFile)
        {
            cerr << "Failed to open output file." << endl;
            delete[] newArr;
            return;
        }
        oFile.write(reinterpret_cast<char *>(newArr), newArrLen);
        oFile.close();

        delete[] newArr; // Cleanup
    }

    // Decryption
    else if (*mode == 'D')
    {
        // Assuming msg contains the encrypted data
        int len = strlen(msg);
        unsigned char *encryptedArr = new unsigned char[len + 1];
        memcpy(encryptedArr, msg, len);
        encryptedArr[len] = '\0'; // Ensure null-termination for string operations

        // Key Variables
        int keyLen = strlen(key);
        unsigned char keyArr[keyLen + 1];
        strcpy(reinterpret_cast<char *>(keyArr), key);

        // Reverse the process of encryption
        // First, reverse swap using the same key
        unsigned char *startPtr = encryptedArr;
        unsigned char *endPtr = encryptedArr + len - 1;

        // The swapping logic should mirror the encryption's logic, adjusted for decryption
        while (startPtr < endPtr)
        {
            for (int i = 0; i < keyLen && startPtr < endPtr; ++i)
            {
                if (keyArr[i] % 2 != 0)
                {
                    swapBytes(*startPtr, *endPtr);
                    endPtr--;
                }
                startPtr++;
            }
            // Reset pointers if they have not met
            if (startPtr < endPtr)
            {
                startPtr = encryptedArr;
                endPtr = encryptedArr + len - 1;
            }
        }

        // XOR to decrypt
        for (int i = 0; i < len; ++i)
        {
            encryptedArr[i] ^= keyArr[i % keyLen];
        }

        // Remove padding
        int realLen = len;
        while (realLen > 0 && encryptedArr[realLen - 1] == static_cast<unsigned char>(0x81))
        {
            realLen--;
        }

        // Output decrypted data
        ofstream oFile(outFile, ios::out | ios::trunc | ios::binary);
        if (!oFile)
        {
            cerr << "Failed to open output file for writing decrypted content." << endl;
            delete[] encryptedArr;
            return;
        }
        oFile.write(reinterpret_cast<char *>(encryptedArr), realLen);
        oFile.close();

        delete[] encryptedArr; // Cleanup
    }

    else
    {
        printf("       ERROR: Invaild Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n");
        exit(1);
    }
}

void StreamCiphered(const char *msg, char *key, const char *mode, const char *outFilename)
{
    if (*mode == 'E' || *mode == 'D')
    {
        size_t inputLen = strlen(msg);
        ofstream outputFile(outFilename, ios::binary);

        // Encryption and Decryption are the same for XOR-based stream cipher
        for (size_t i = 0; i < inputLen; ++i)
        {
            char cipherByte = msg[i] ^ key[i % strlen(key)];
            outputFile.put(cipherByte);
        }

        outputFile.close();
    }
    else
    {
        printf("       ERROR: Invaild Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n");
        exit(1);
    }
}

int main(int argc, const char **argv)
{
    // Check for the correct amount of arguments
    if (argc != 6)
    {
        cout << "ERROR: Incorrect number of arguments.\n"
             << "Usage: <program_name> <cipher type> <input filename> <output filename> <key> <mode>\n"
             << "  <cipher type> - 'B' for Block Cipher or 'S' for Stream Cipher\n"
             << "  <input filename> - Path to the input file\n"
             << "  <output filename> - Path for the output file\n"
             << "  <key> - Encryption/Decryption key\n"
             << "  <mode> - 'E' for Encrypt or 'D' for Decrypt\n"
             << "Example: main B input.txt output.txt COMPUTER76543210 E\n";
        return 1;
    }

    ifstream iFile(argv[2], ios::binary | ios::ate);
    if (!iFile.is_open())
    {
        cout << "       ERROR: Input File is not Valid or Does not exist.\n";
        return 1;
    }

    // Calculate file size and allocate memory
    streamsize size = iFile.tellg();
    iFile.seekg(0, ios::beg);
    char *msg = new char[size + 1];

    // Read file content
    if (!iFile.read(msg, size))
    {
        cout << "       ERROR: Failed to read file.\n";
        delete[] msg;
        return 1;
    }
    msg[size] = '\0'; // Null-terminate the string
    iFile.close();

    // Generate a key of sufficient size
    char *newKey = keyGen(msg, argv[4]);

    // Selection of cipher type and mode
    char cipherFunction = *argv[1];
    char mode = *argv[5];

    // Process encryption/decryption
    if (cipherFunction == 'B')
    {
        BlockCiphered(msg, newKey, &mode, argv[3]);
    }
    else if (cipherFunction == 'S')
    {
        StreamCiphered(msg, newKey, &mode, argv[3]);
    }
    else
    {
        cout << "       ERROR: Invalid cipher function - Please Enter either 'B' for Block Cipher or 'S' for Stream Cipher.\n";
        delete[] msg;
        delete[] newKey;
        return 1;
    }

    // Cleanup
    delete[] msg;
    delete[] newKey;

    return 0;
}
