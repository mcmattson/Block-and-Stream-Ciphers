#include <iostream>
#include <cstring>
#include <cmath>
#include "Cipher.h"

using namespace std;

int valueOfChar(unsigned char c)
{
    int i = c;
    return i;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Generates Key the length needed for input str
char *keyGen(const string &inputStr, const char *key)
{
    int inputStrlen = inputStr.size();
    int keyWordlen = strlen(key);

    if (keyWordlen == 0)
    {
        printf("can not divid by zero\n");
        return (nullptr);
    }

    // Define New Array
    char *newKeyArray = new char[inputStrlen + 1];

    // If input msg is longer-repeat the keyword
    for (int i = 0, j = 0; i < inputStrlen; ++i, ++j)
    {
        if (j == keyWordlen)
        {
            j = 0;
        }
        newKeyArray[i] = key[j];
    }

    newKeyArray[inputStrlen] = '\0';
    return newKeyArray;
}
