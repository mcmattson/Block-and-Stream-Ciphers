# the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS  = -g -Wall

  # The build target
main: main.o
	$(CC) $(CFLAGS) -o main main.o CipherSupport.o BlockCipher.o StreamCipher.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp Cipher.h CipherSupport.cpp BlockCipher.cpp StreamCipher.cpp