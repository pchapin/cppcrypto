cppCrypto
=========

This project is a cryptographic library in C++2020. Although it is intended to be a useful
library on its own terms, the real point of this project is to serve as a C++2020 demonstration.
In particular, it uses C++2020 modules throughout (or it will, at least).

This project's primary purpose is to be educational. It is not an industrial strength
implementation of the algorithms provided.

Currently the project is only known to compile with g++ 11.3 (as ships with Ubuntu 22.04). Since
modules are a relatively new feature, it may or may not work properly with other compilers. For
example, building this program is known to cause g++ 12.2 (as ships with Ubuntu 23.04) to crash.

The primary module interface file is currently named with a .ixx extension in deference to
Microsoft's Visual Studio and VSCode tools.

Peter Chapin  
chapinp@proton.me  
