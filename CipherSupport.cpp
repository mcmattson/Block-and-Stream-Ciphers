#include <iostream>
#include <cstring>
#include <cmath>
#include "Cipher.h"

using namespace std;

int valueOfChar(unsigned char c) {
    int i = c;
    return i;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Generates Key the length needed for input str
char *keyGen(const string &inputStr, const char *key) {
    int inputStrlen = inputStr.size();
    int keyWordlen = sizeof(key);

    // calculate length of input string
    double NEWkeyWordlen = inputStrlen - keyWordlen;
    NEWkeyWordlen = NEWkeyWordlen / (float) keyWordlen;
    NEWkeyWordlen = round(NEWkeyWordlen);

    //Define New Array
    char *newKeyArray = new char[inputStrlen + inputStrlen];
    strcpy(newKeyArray, key);

    //If input msg is longer-repeat the keyword
    for (int i = 0; i < NEWkeyWordlen; i++) {
        strcat(newKeyArray, key);
    }
    return newKeyArray;
}
