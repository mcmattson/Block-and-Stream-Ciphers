================ Programming Assignment 1 ===============
This project aims to introduce the concepts of block ciphers and stream ciphers. Block ciphers encrypt 
data in fixed-size blocks of n bits, while stream ciphers encrypt data one bit at a time. The program 
reads an input file, applies specified algorithms, and produces an output file.

==================== Requirements ========================
The program requires five arguments in the specified order, with validation checks for each argument 
to ensure correctness.

The first argument specifies the cipher type: 'B' for block cipher or 'S' for stream cipher. The 
program terminates with an error message if any other value is provided.

The second argument is the name of the input file. The program exits with an error if the file cannot 
be found.

The third argument is the name of the output file. If not found, program will create a new file.

The fourth argument is the keyfile, containing the symmetric key in ASCII format (e.g., "COMPUTER76543210"). 
For Block Encryption Mode, the key size is 128 bits (16 bytes), while any length is acceptable for Stream 
Encryption Mode. The program uses this key for encryption, assuming no newline character at the end of the 
key. The program exits with an error if the file cannot be found.

The fifth argument indicates the mode of operation: 'E' for encryption or 'D' for decryption. Different 
modules may be needed for each mode, especially for block ciphers, as described in the algorithms section.

The program processes the input file, treating end-of-line characters as regular data, and assumes the 
file is in multiples of 8 bits. Output files are generated based on the mode, with block mode requiring 
128-bit blocks and padding for blocks under this length using 0X81 bytes. Stream mode maintains 8-bit 
multiples without specific padding requirements. An empty input file results in an empty output file.

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
To install, unpack the Matthew_Mattson_PA1.tar.gz package into the intended directory. Build the program 
in a LINUX terminal within that directory by typing "make". This prepares the program for execution according 
to the provided requirements. A pre-determined input file (EX. input.txt) and key file (keyfile.txt) will need 
to be created before the program is executed or the program will fail to execute.

==================== Configuration ========================
No further configuration is needed after installation.