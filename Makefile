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

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

# First, it is necessary to compile the library header units using commands such as:
#
# clang++ -std=c++20 -x c++-system-header --precompile cstring -o cstring.pcm
#
# I could no doubt get 'make' to do this, but I just did it manually for now. The clang documentation
# says this will be streamlined in the future. It is furtermore necessary to explicitly load the header
# units when compiling code that depends on them. This is also supposed to work better in the future.

# Clang wants module interface files to use a .cppm extension. However, .ixx is normal for Microsoft.
# Selecting a language of "c++-module" (with the -x option) forces clang to do the right thing here.
cppCrypto.pcm:	cppCrypto.ixx
	clang++ -std=c++20 -Wall -x c++-module cppCrypto.ixx \
		-fmodule-file=memory.pcm    \
		-fmodule-file=stdexcept.pcm \
		--precompile -o cppCrypto.pcm

BlockCipher.o:	BlockCipher.cpp cppCrypto.pcm
	clang++ -std=c++20 -Wall -c -O BlockCipher.cpp \
		-fmodule-file=cstring.pcm \
		-fmodule-file=string.pcm \
		-fmodule-file=cppCrypto.pcm \
		-o BlockCipher.o

CBCCipher.o:	CBCCipher.cpp cppCrypto.pcm
	clang++ -std=c++20 -Wall -c -O CBCCipher.cpp \
		-fmodule-file=cstring.pcm \
		-fmodule-file=memory.pcm \
		-fmodule-file=cppCrypto.pcm \
		-o CBCCipher.o

main.o:	main.cpp cppCrypto.pcm
	clang++ -std=c++20 -Wall -c -O main.cpp \
		-fmodule-file=cppCrypto.pcm \
		-o main.o

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(EXECUTABLE) *.s *.ll *~
