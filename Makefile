#
# Makefile for the cppCrypto project.
#

CXX=g++
CXXFLAGS=-c -std=c++20 -fmodules-ts -Wall -O
LINK=g++
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

# First, if any header units are used it is necessary to compile them using commands such as:
#
#     g++ -std=c++20 -fmodules-ts -x c++-system-header cstring 
#
# I could no doubt get 'make' to do this, but I do it manually for now.


# g++ wants module interface files to use a .cppm extension. However, .ixx is normal for Microsoft.
# Selecting a language of "c++" (with the -x option) forces g++ to do the right thing here.
gcm.cache/cppCrypto.gcm:	cppCrypto.ixx
	$(CXX) $(CXXFLAGS) -x c++ cppCrypto.ixx

BlockCipher.o:	BlockCipher.cpp gcm.cache/cppCrypto.gcm
	$(CXX) $(CXXFLAGS) BlockCipher.cpp

CBCCipher.o:	CBCCipher.cpp gcm.cache/cppCrypto.gcm
	$(CXX) $(CXXFLAGS) CBCCipher.cpp

main.o:	main.cpp gcm.cache/cppCrypto.gcm
	$(CXX) $(CXXFLAGS) main.cpp


# Additional Rules
##################
clean:
	rm -rf gcm.cache *.o $(EXECUTABLE) *~
