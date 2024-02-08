
#include <iostream>

#ifndef PROGRAMMING_ASSIGNMENT_1_CIPHER_H
#define PROGRAMMING_ASSIGNMENT_1_CIPHER_H

int valueOfChar(unsigned char i);
void swapBytes(unsigned char &a, unsigned char &b);
char *keyGen(const std::string &inputStr, const char *key);
void BlockCiphered(char msg[], char key[], const char *mode, const char *outFile);
void StreamCiphered(char msg[], char key[], const char *mode, const char *outFile);

#endif
