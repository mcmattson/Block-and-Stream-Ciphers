#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int BLOCK_SIZE = 16;
const int PADDING_BYTE = 0x81;

// function to pad the input file with 0x81 until it is 128 bits (16 bytes) in size
void padFile(fstream &inFile, fstream &outFile)
{
    char buffer[BLOCK_SIZE];
    memset(buffer, 0, BLOCK_SIZE);
    int bytesRead;

    while ((bytesRead = inFile.readsome(buffer, BLOCK_SIZE)) > 0)
    {
        int padding = BLOCK_SIZE - bytesRead;
        for (int i = 0; i < padding; i++)
        {
            buffer[bytesRead + i] = PADDING_BYTE;
        }
        outFile.write(buffer, BLOCK_SIZE);
    }
}

// function to perform the XOR operation between the input data block and key
void xorBlock(char *block, char *key)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = block[i] ^ key[i];
    }
}

// function to swap the bytes of the XORed output based on the ASCII value of the key
void swapBytes(char *block, char *key)
{
    int start = 0;
    int end = BLOCK_SIZE - 1;
    int keyLength = strlen(key);

    while (start < end)
    {
        if ((int)key[start % keyLength] % 2 == 0)
        {
            start++;
        }
        else
        {
            swap(block[start], block[end]);
            start++;
            end--;
        }
    }
}

// function to remove the padding from the decrypted output
void removePadding(fstream &inFile, fstream &outFile)
{
    char buffer[BLOCK_SIZE];
    memset(buffer, 0, BLOCK_SIZE);
    int bytesRead;

    while ((bytesRead = inFile.readsome(buffer, BLOCK_SIZE)) > 0)
    {
        int padding = 0;
        for (int i = BLOCK_SIZE - 1; i >= 0; i--)
        {
            if (buffer[i] == PADDING_BYTE)
            {
                padding++;
            }
            else
            {
                break;
            }
        }
        outFile.write(buffer, BLOCK_SIZE - padding);
    }
}

int main(int argc, char *argv[])
{
    // check if the correct number of arguments are provided
    if (argc != 6)
    {
        cerr << "Error: incorrect number of arguments provided" << endl;
        return 1;
    }

    char mode = argv[5][0];
    char *inputFile = argv[2];
    char *outputFile = argv[3];
    char *keyFile = argv[4];
    char key[BLOCK_SIZE];

    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;
    cout << argv[4] << endl;
    cout << argv[5] << endl;

    // open the key file and read the key into memory
    fstream keyStream(keyFile, ios::in | ios::binary);
    if (!keyStream.is_open())
    {
        cerr << "Error: unable to open key file" << endl;
        return 1;
    }
    keyStream.read(key, BLOCK_SIZE);
    keyStream.close();

    // open the input and output files
    fstream inStream(inputFile, ios::in | ios::binary);
    if (!inStream.is_open())
    {
        cerr << "Error: unable to open input file" << endl;
        return 1;
    }
    fstream outStream(outputFile, ios::out | ios::binary);
    if (!outStream.is_open())
    {
        cerr << "Error: unable to open output file" << endl;
        return 1;
    }

    // perform encryption or decryption based on the mode
    if (mode == 'e')
    {
        padFile(inStream, outStream);
        inStream.close();
        inStream.open(outputFile, ios::in | ios::binary);

        char block[BLOCK_SIZE];
        memset(block, 0, BLOCK_SIZE);
        int bytesRead;
        while ((bytesRead = inStream.readsome(block, BLOCK_SIZE)) > 0)
        {
            xorBlock(block, key);
            swapBytes(block, key);
            outStream.write(block, BLOCK_SIZE);
        }
    }
    else if (mode == 'd')
    {
        char block[BLOCK_SIZE];
        memset(block, 0, BLOCK_SIZE);
        int bytesRead;
        while ((bytesRead = inStream.readsome(block, BLOCK_SIZE)) > 0)
        {
            swapBytes(block, key);
            xorBlock(block, key);
            outStream.write(block, BLOCK_SIZE);
        }
        outStream.close();
        outStream.open(outputFile, ios::in | ios::binary);
        removePadding(outStream, outStream);
    }
    else
    {
        cerr << "Error: invalid mode specified" << endl;
        return 1;
    }

    inStream.close();
    outStream.close();

    return 0;
}
