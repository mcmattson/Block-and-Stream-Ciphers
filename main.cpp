#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

void xorOperation(std::vector<unsigned char> &data, const std::string &key)
{
    std::transform(data.begin(), data.end(), data.begin(), [&, i = 0](unsigned char c) mutable -> unsigned char
                   { return c ^ key[i++ % key.length()]; });
}

void padInput(const char *msg, int len, const std::string &key, std::vector<unsigned char> &newArr)
{
    const unsigned char pad = 0x81;
    const int blockSize = 16;

    int padding = blockSize - (len % blockSize);
    int newArrLen = len + (padding ? padding : blockSize);
    newArr.resize(newArrLen);

    std::copy(msg, msg + len, newArr.begin());

    // pad
    std::fill_n(newArr.begin() + len, newArrLen - len, pad);
}

void swapOperation(std::vector<unsigned char> &arr, const std::string &key)
{
    int len = arr.size();
    int keyLen = key.length();

    for (int start = 0, end = len - 1; start < end; ++start)
    {
        if (key[start % keyLen] % 2 != 0)
        {
            std::swap(arr[start], arr[end--]);
        }
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

void encrypt(const char *msg, const std::string &key, const char *outFile)
{
    int len = strlen(msg);
    std::vector<unsigned char> newArr(reinterpret_cast<const unsigned char *>(msg), reinterpret_cast<const unsigned char *>(msg) + len);
    padInput(msg, len, key, newArr);
    xorOperation(newArr, key);
    swapOperation(newArr, key);
    writeFile(outFile, newArr);
}

void decrypt(const char *msg, const std::string &key, const char *outFile)
{
    int len = strlen(msg);
    std::vector<unsigned char> newArr(reinterpret_cast<const unsigned char *>(msg), reinterpret_cast<const unsigned char *>(msg) + len);
    swapOperation(newArr, key);
    xorOperation(newArr, key);

    // de-pad
    while (!newArr.empty() && newArr.back() == static_cast<unsigned char>(0x81))
    {
        newArr.pop_back();
    }

    writeFile(outFile, newArr);
}

void BlockCiphered(const char *msg, const std::string &key, const char *mode, const char *outFile)
{
    if (*mode == 'E')
    {
        encrypt(msg, key, outFile);
    }
    else if (*mode == 'D')
    {
        decrypt(msg, key, outFile);
    }
    else
    {
        std::cerr << "    ERROR: Invalid Mode - Please Enter either 'E' for encryption or 'D' for decryption...\n";
        exit(1);
    }
}

void StreamCiphered(const char *msg, const std::string &key, const char *mode, const char *outFilename)
{
    // Encryption and Decryption are the same for XOR-based stream cipher
    if (*mode == 'E' || *mode == 'D')
    {
        size_t inputLen = strlen(msg);
        std::ofstream outputFile(outFilename, std::ios::binary);

        for (size_t i = 0; i < inputLen; ++i)
        {
            char cipherByte = msg[i] ^ key[i % key.length()];
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
                  << "Example: main B input.txt output.txt keyfile.txt E\n";
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
    std::string key((std::istreambuf_iterator<char>(keyFile)), std::istreambuf_iterator<char>());
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
