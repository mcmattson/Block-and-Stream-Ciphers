// Stream cipher
// 1.	You will XOR your input stream with the following data
// o	The key is (in ASCII, again) "COMPUTER76543210".
// o	Bit 0 from the input file will be XORed with Bit 0 from the key
// o	Bit 1 from the input file will be XORed with Bit 1 from the key
// o	...
// o	Bit n-1 from the input file will be XORed with Bit n-1 from the key
// 2.	If you reach the end of the key, start over from the beginning.
// 3.	Note on the number of the bits. Since this is a stream, bit 0 is the first bit to arrive, bit 1 is the second bit and so forth. That means the leftmost bit of the first byte is bit 0. Same with the key.
// 4.	Encryption and decryption will be performed with the same module that you design for the Stream Cipher. In other words, you do not have have to design separate modules for encryption and decryption in the Stream Encryption Mode.
