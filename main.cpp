/*! \file   main.cpp
 *  \brief  A demonstration program to illustrate the BlockCipher hierarchy.
 *  \author Peter Chapin <spicacality@kelseymountain.org>
 */

//import <cstdlib>;
//import <cstring>;
//import <iostream>;
//import <fstream>;
//import <memory>;

import std;
import cppCrypto;

namespace cppCrypto = cppCrypto_0_0_0;

enum class Direction {
    Encrypt, Decrypt
};

void cipher_file(
        const std::string &in_text,
        const std::string &out_text,
        cppCrypto::BlockCipher &cipher,
        Direction cipher_direction )
{
    std::ifstream input( in_text, std::ios::binary );
    if( !input ) {
        std::cerr << "Unable to open " << in_text << " for input!" << std::endl;
        return;
    }

    std::ofstream output( out_text, std::ios::binary );
    if( !output ) {
        std::cerr << "Unable to open " << out_text << " for writing!" << std::endl;
        return;
    }

    // Create a C style array dynamically with the required block size.
    size_t size = cipher.block_size( );
    auto buffer = std::make_unique<cppCrypto::BlockCipher::octet_type[]>( size );
    cppCrypto::BlockCipher::octet_type *p = buffer.get( );

    // Keep reading the input until we get to the end-of-file.
    while( input ) {
        // Note that the read() and write() methods expect type char* which is a poor choice for
        // representing binary data. Unfortunately, converting from unsigned char* to char* needs
        // the heavy-handed reinterpret_cast.
        input.read( reinterpret_cast<char *>( p ), size );
        if( input.gcount( ) == 0 ) break;

        if( cipher_direction == Direction::Encrypt )
            cipher.encrypt( p );
        else
            cipher.decrypt( p );

        output.write( reinterpret_cast<char *>( p ), size );
    }
}


int Main( int argc, char *argv[] )
{
    Direction desired_direction;

    // Are there sufficient command line arguments?
    if( argc != 5 ) {
        std::cerr << "Usage: " << argv[0] << " [-e|-d] passphrase input-file output-file" << std::endl;
        return 1;
    }

    // Are we encrypting or decrypting today?
    if( std::strcmp( argv[1], "-e" ) == 0 )
        desired_direction = Direction::Encrypt;
    else if( std::strcmp( argv[1], "-d" ) == 0 )
        desired_direction = Direction::Decrypt;
    else {
        std::cerr << "Error! One of -e or -d is required." << std::endl;
        return 1;
    }

    // Check the passphrase length.
    // TODO: Consult the cipher engine about key requirements.
    // TODO: Hash the passphrase or do some similar preprocessing.
    const char *passphrase = argv[2];
    size_t passphrase_length = std::strlen( passphrase );
    if( passphrase_length < 4 ) {
        std::cerr << "Error! Passphrase is too short. At least four characters are required." << std::endl;
        return 1;
    }
    // Round the length down to a multiple of 32 bits.
    size_t adjusted_length = 4 * ( passphrase_length / 4 );
    if( adjusted_length != passphrase_length ) {
        std::cerr << "Warning! Last "
                  << passphrase_length - adjusted_length
                  << " characters of passphrase not considered." << std::endl;
    }
    if( adjusted_length > 56 ) {
        std::cerr << "Warning! Passphrase is too long. Only 56 characters used." << std::endl;
    }

    // Set up the engine.
    cppCrypto::BlowfishCipher blowfish_engine(
        reinterpret_cast<const cppCrypto::BlockCipher::octet_type *>( passphrase ), adjusted_length );
    const cppCrypto::BlockCipher::octet_type iv[] = { 0, 1, 2, 3, 4, 5, 6, 7 };  // Arbitrary and fixed for now.
    cppCrypto::CBCCipher cipher_engine( iv, blowfish_engine );

    // Encrypt/Decrypt the file.
    cipher_file( argv[3], argv[4], cipher_engine, desired_direction );

    return 0;
}


int main( int argc, char *argv[] )
{
    try {
        return Main( argc, argv );
    }
    catch( const cppCrypto::BlockCipher::NotImplemented &ex ) {
        std::cerr << "Unhandled BlockCipher::NotImplemented exception: " << ex.what( ) << std::endl;
    }
    catch( ... ) {
        std::cerr << "Unhandled exception!" << std::endl;
    }
    return 1;
}
