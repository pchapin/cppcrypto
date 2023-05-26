#
# Makefile for the cppCrypto project.
#

CXX=clang++
CXXFLAGS=-std=c++20 -Wall -c -O
LINK=clang++
LINKFLAGS=
SOURCES=BlockCipher.cpp \
	CBCCipher.cpp \
	main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all:	main

# Rule for converting C++ source files into object files.
%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Rule for converting interface files into precompiled module files.
%.pcm:	%.ixx
	$(CXX)  -std=c++20 -x c++ $< --precompile -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

BlockCipher.o:	BlockCipher.cpp cppCrypto.pcm
	clang++ -std=c++20 -Wall -c -O BlockCipher.cpp -fmodule-file=cppCrypto=cppCrypto.pcm -o BlockCipher.o

CBCCipher.o:	CBCCipher.cpp cppCrypto.pcm 

main.o:	main.cpp cppCrypto.pcm
# Additional Rules
##################
clean:
	rm -f *.bc *.o $(EXECUTABLE) *.s *.ll *~
