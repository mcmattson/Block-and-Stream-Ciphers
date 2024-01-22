// Requirements
// This program should be written in C or C++.
// Your submittal should include a Makefile.
// Your program will take 5 arguments in the order defined below. Your program should ensure there are 5 arguments, and that each argument is error-checked appropriately.
// The first argument is either a 'B' or a 'S'.
// B means you will use your block cipher function
// S means you will use your stream cipher function.
// Your program should terminate if other than a 'B' or an 'S' is entered with an appropriate error message.
// The second argument is the input file name.
// Your program should terminate with an appropriate error message if the file does not exist.
// The third argument is the output file name.
// The fourth argument is the keyfile
// The keyfile contains the symmetric key in ASCII format ("COMPUTER76543210"). The keysize for Block Encryption Mode would be 128 bits (16 bytes) and can be of any length for Stream Encryption Mode. Your program will read in the contents of the keyfile and use it to encrypt the plaintext provided in the input file. The keyfile will not contain a terminating "\n"(newline) character.
// The fifth argument is the 'mode of operation' which can be either 'E' for encryption or 'D' for decryption.
// Altough the same 'E' or 'D' module can be used for Stream Ciphers, the same does not apply for Block Ciphers as will be explained below in the 'Description of the algorithms' section. In the 'E' mode you would encrypt a plaintext using a key and produce a ciphertext. We can then evaluate your encrypted output against the output produced by our own program with the same key. Similarly, in the 'D' mode your program is expected to decrypt an already encrypted text, with the same symmetric key, and produce expected plaintext results.
// Your program will read in the input file.
// End of line characters are data just like any other character.
// You may assume the file is in multiples of 8 bits.
// Your file will write the output file based on the arguments.
// Your file should be in 128-bit blocks in block mode.
// This means you must pad blocks that are not 128 bits in length.
// Each padding byte should be 0X81. Because the input file will be a multiple of 8 bits or 1 byte, padding (if required) can also be done in multiples of 8 bits or 1 byte. For the purpose of this project you will be using the byte value 0X81 in hex or 129 in decimal. Becasue, the input file is in ASCII and the padding value (0X81) falls outside the ASCII (0-127) range, it allows us distinguish padding bytes from plaintext bytes.
// Your file should be in 8-bit multiples in stream mode.
// Your file will be read in by a program that isn't yours to test.
// If the input file is empty, the output file should be empty.