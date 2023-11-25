#
# Makefile for the cppCrypto project.
#

CXX=g++
CXXFLAGS=-c -std=c++23 -fmodules-ts -Wall
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

$(EXECUTABLE):	$(OBJECTS) cppCrypto.o
	$(CXX) $(OBJECTS) cppCrypto.o $(LINKFLAGS) -o $@


# File Dependencies
###################

# First, if any standard library header units are used it is necessary to compile them using
# commands such as:
#
#     g++ -std=c++23 -fmodules-ts -x c++-system-header cstring
#
# This program is using C++ 2023's `import std` to access the standard library. So it is *not*
# necessary to compile standard library header units (simply #including the standard library
# headers produces spurious errors with clang about duplicate declarations, for some reason).

# g++ wants module interface files to use a .cppm extension. However, .ixx is normal for
# Microsoft. Selecting a language of "c++" (with the -x option) forces g++ to do the right thing
# here.
#
# Another oddity is that the file cppCrypto.o is generated as a side effect of this target. This
# complicates make running in parallel since it currently doesn't realize that cppCrypto.o is
# actually going to be made here (there is no target that mentions it).
gcm.cache/cppCrypto.gcm:	cppCrypto.ixx
	$(CXX) $(CXXFLAGS) -x c++ cppCrypto.ixx

BlockCipher.o:	BlockCipher.cpp gcm.cache/cppCrypto.gcm

CBCCipher.o:	CBCCipher.cpp gcm.cache/cppCrypto.gcm

main.o:	main.cpp gcm.cache/cppCrypto.gcm


# Additional Rules
##################
clean:
	rm -rf gcm.cache *.o $(EXECUTABLE) *~
