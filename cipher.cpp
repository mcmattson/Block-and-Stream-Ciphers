#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

const unsigned char PADDING_BYTE = 0x81;
const int BLOCK_SIZE = 16;

void xorOperation(std::vector<unsigned char> &data, const std::vector<unsigned char> &key)
{
    for (size_t i = 0; i < data.size(); ++i)
    {
        data[i] ^= key[i % key.size()];
    }
}

void addPadding(const char *msg, int len, std::vector<unsigned char> &key, std::vector<unsigned char> &newArr)
{

    int padding = BLOCK_SIZE - (len % BLOCK_SIZE);
    int newArrLen = len + (padding ? padding : BLOCK_SIZE);
    newArr.resize(newArrLen);

    std::copy(msg, msg + len, newArr.begin());
    std::fill_n(newArr.begin() + len, newArrLen - len, PADDING_BYTE);
}

void swapOperation(std::vector<unsigned char> &data, std::vector<unsigned char> &key)
{
    int start = 0, end = data.size() - 1;
    size_t keyIndex = 0;
    while (start < end)
    {
        if ((key[keyIndex] % 2) == 1)
        {
            std::swap(data[start], data[end]);
            --end;
        }
        ++start;
        keyIndex = (keyIndex + 1) % key.size();
    }
}

void removePadding(std::vector<unsigned char> &data)
{
    while (!data.empty() && data.back() == PADDING_BYTE)
    {
        data.pop_back();
    }
}

void writeFile(const char *outFile, const std::vector<unsigned char> &data)
{
    std::ofstream oFile(outFile, std::ios::out | std::ios::binary);
    if (!oFile)
    {
        std::cerr << "  Failed to open output file." << std::endl;
        return;
    }
    oFile.write(reinterpret_cast<const char *>(data.data()), data.size());
    oFile.close();
}

void encrypt(const char *data, std::vector<unsigned char> &key, const char *outFile)
{
    int len = strlen(data);
    std::vector<unsigned char> newArr(reinterpret_cast<const unsigned char *>(data), reinterpret_cast<const unsigned char *>(data) + len);
    addPadding(data, len, key, newArr);
    xorOperation(newArr, key);
    swapOperation(newArr, key);
    writeFile(outFile, newArr);
}


void decrypt(const char *data, std::vector<unsigned char> &key, const char *outFile)
{
    int len = strlen(data);
    std::vector<unsigned char> newArr(reinterpret_cast<const unsigned char *>(data), reinterpret_cast<const unsigned char *>(data) + len);
    swapOperation(newArr, key);
    xorOperation(newArr, key);
    removePadding(newArr);
    writeFile(outFile, newArr);
}

void BlockCiphered(const char *data, std::vector<unsigned char> &key, const char *mode, const char *outFile)
{
    if (*mode == 'E')
    {
        encrypt(data, key, outFile);
    }
    else if (*mode == 'D')
    {
        decrypt(data, key, outFile);
    }
    else
    {
        std::cerr << "    ERROR: Invalid Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n";
        exit(1);
    }
}

void StreamCiphered(const char *data, std::vector<unsigned char> &key, const char *mode, const char *outFilename)
{
    // Encryption and Decryption are the same for XOR-based stream cipher
    if (*mode == 'E' || *mode == 'D')
    {
        size_t inputLen = strlen(data);
        std::ofstream outputFile(outFilename, std::ios::binary);

        for (size_t i = 0; i < inputLen; ++i)
        {
            char cipherByte = data[i] ^ key[i % key.size()];
            outputFile.put(cipherByte);
        }

        outputFile.close();
    }
    else
    {
        std::cerr << "    ERROR: Invaild Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n";
        exit(1);
    }
}

int main(int argc, const char **argv)
{
    // Check for the correct amount of arguments
    if (argc != 6)
    {
        std::cerr << "ERROR: Incorrect number of arguments.\n"
                  << "Usage: <program_name> <cipher type> <input filename> <output filename> <keyfile> <mode>\n"
                  << "  <cipher type> - 'B' for Block Cipher or 'S' for Stream Cipher\n"
                  << "  <input> - Input filename\n"
                  << "  <output> - Desired Output filename\n"
                  << "  <keyfile> - Encryption/Decryption key filename\n"
                  << "  <mode> - 'E' for Encrypt or 'D' for Decrypt\n"
                  << "Example: cipher B input.txt output.txt keyfile.txt E\n";
        return 1;
    }

    // Check KeyFile
    std::ifstream keyFile(argv[4], std::ios::ate);
    if (!keyFile.is_open())
    {
        std::cerr << "      ERROR: Key File is not Valid or Does not exist.\n";
        return 1;
    }

    std::streamsize keySize = keyFile.tellg();
    if (keySize == 0)
    {
        std::cout << "      ERROR: Key File is empty. Exiting...\n";
        return 1;
    }

    keyFile.seekg(0, std::ios::beg);
    std::vector<unsigned char> key(keySize);
    if (!keyFile.read(reinterpret_cast<char *>(key.data()), keySize))
    {
        std::cerr << "      ERROR: Failed to read key file.\n";
        return 1;
    }
    keyFile.close();

    // Check Inputfile
    std::ifstream iFile(argv[2], std::ios::binary | std::ios::ate);
    if (!iFile.is_open())
    {
        std::cerr << "       ERROR: Input Filename is not Valid or Does not exist.\n";
        return 1;
    }

    // Calculate file size and allocate memory
    std::streamsize size = iFile.tellg();

    // Check OutputFile
    if (size == 0)
    {
        std::ofstream oFile(argv[3], std::ios::trunc | std::ios::binary);
        if (!oFile.is_open())
        {
            return 1;
        }
        oFile.close();
        return 0;
    }

    std::vector<char> msgBuffer(size);
    iFile.seekg(0, std::ios::beg);

    // Read file content
    if (!iFile.read(msgBuffer.data(), size))
    {
        std::cerr << "       ERROR: Failed to read file.\n";
        return 1;
    }
    iFile.close();

    std::string msg(msgBuffer.begin(), msgBuffer.end());
    char cipherFunction = *argv[1];
    char mode = *argv[5];

    // Process encryption/decryption
    if (cipherFunction == 'B')
    {
        BlockCiphered(msg.c_str(), key, &mode, argv[3]);
    }
    else if (cipherFunction == 'S')
    {
        StreamCiphered(msg.c_str(), key, &mode, argv[3]);
    }
    else
    {
        std::cerr << "       ERROR: Invalid cipher function - Please Enter either 'B' for Block Cipher or 'S' for Stream Cipher.\n";
        return 1;
    }
    return 0;
}
