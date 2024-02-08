# Define compiler
CXX=g++

# Compiler flags
CXXFLAGS=-Wall -std=c++17

# Define the source file and the output file
SRC=main.cpp
OUT=main

# The first rule is the one executed when no parameters are fed into the Makefile
all: $(OUT)

# Rule for making the actual target
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

# Clean the build directory
clean:
	rm -f $(OUT)
