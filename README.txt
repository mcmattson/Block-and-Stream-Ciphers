================ Programming Assignment 1 ===============
This assignment introduces students to the concepts of block ciphers and stream ciphers. Block 
ciphers encrypt data in fixed-size blocks of n bits, while stream ciphers encrypt data one bit 
at a time. The program reads an input file, applies the described algorithms, and outputs a file.

==================== Requirements ========================
The program requires five arguments in the specified order and performs appropriate error checks
for each.

The first argument determines the cipher type: 'B' for a block cipher or 'S' for a stream cipher. 
The program ends with an error message if any value other than 'B' or 'S' is entered.

The second argument is the input file name. The program terminates with an error if the file is 
not found.

The third argument is the output file name.

The fourth argument is the keyfile, which contains the symmetric key in ASCII ("COMPUTER76543210"). 
For Block Encryption Mode, the key size is 128 bits (16 bytes). Any length is acceptable for Stream 
Encryption Mode. The program reads the keyfile and encrypts the input file's plaintext. The keyfile 
does not include a newline character at the end.

The fifth argument is the operation mode, 'E' for encryption or 'D' for decryption. While the same 
module can be used for stream ciphers in both modes, block ciphers require different treatments as 
detailed in the algorithm descriptions.

The program processes the input file as data, including end-of-line characters, and assumes the file 
is in multiples of 8 bits. The output file is generated based on the arguments. For block mode, the 
output should be in 128-bit blocks, padding incomplete blocks with 0X81 bytes. In stream mode, the 
output should maintain 8-bit multiples. An empty input file results in an empty output file.

==================== Block cipher ========================
Encryption is a three-step process: padding (if necessary), encrypting (using XOR), and swapping. 
Blocks less than 128 bits are padded with 0X81 bytes to reach 128 bits. The algorithm XORs the data 
block with the key bit by bit, then swaps bytes of the XORed output based on the ASCII values of the 
key's bytes. Decryption reverses these steps, including padding removal.

==================== Stream cipher ========================
The input stream is XORed with the key "COMPUTER76543210", bit by bit. If the end of the key is 
reached, it starts over from the beginning. The design for the Stream Cipher module applies to both 
encryption and decryption without needing separate modules.

==================== Installation ========================
To install, unpack the package into the intended directory. In a LINUX terminal, navigate to the 
directory and build the program by typing "make". This prepares the program for use according to the 
requirements.

==================== Configuration ========================
No further configuration is needed beyond program building.