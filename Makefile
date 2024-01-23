# the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS  = -g -Wall

# The build target
main: main.o CipherSupport.o BlockCipher.o StreamCipher.o
	$(CC) $(CFLAGS) -o main main.o CipherSupport.o BlockCipher.o StreamCipher.o

# To compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Dependencies
main.o: main.cpp Cipher.h
CipherSupport.o: CipherSupport.cpp Cipher.h
BlockCipher.o: BlockCipher.cpp Cipher.h
StreamCipher.o: StreamCipher.cpp Cipher.h

# Clean up
clean:
	rm -f main *.o CipherSupport.o BlockCipher.o StreamCipher.o