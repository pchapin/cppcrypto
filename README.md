cppCrypto
=========

This project is a cryptographic library in C++2020. Although it is intended to be a useful
library on its own terms, the real point of this project is to serve as a C++2020 demonstration.
In particular, it uses C++2020 modules throughout (or it will, at least). This project's primary
purpose is to be educational.

Currently, the project is only known to compile and execute properly using Microsoft's Visual C++
(via the Visual Studio solution/project files). It will compile with g++ 11.3 as ships with
Ubuntu 22.04, but the resulting executable does not work. Furthermore, building this program is
known to cause g++ 12.2 (as ships with Ubuntu 23.04) and g++ 13.1 to crash. I have not explored
the use of clang++ with this code.

The primary module interface file is currently named with a .ixx extension in deference to
Microsoft's Visual Studio and VSCode tools. Note that the VSCode configuration here assumes
Cygwin and suffers from at least the same set of problems as g++ on Ubuntu. In fact, VSCode
can't locate the module information in this configuration and produces many spurious
Intellisense errors.

Peter Chapin  
spicacality@kelseymountain.org  
