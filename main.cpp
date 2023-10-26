/*! \file   main.cpp
 *  \brief  A demonstration program to illustrate the BlockCipher hierarchy.
 *  \author Peter Chapin <spicacality@kelseymountain.org>
 */

import <cstdlib>;
import <cstring>;
import <iostream>;
import <fstream>;
import <memory>;

import cppCrypto;

using namespace std;
using namespace cppCrypto_0_0_0;

enum class Direction { Encrypt, Decrypt };

void cipher_file(
    const string &in_text,
    const string &out_text,
    BlockCipher  &cipher,
    Direction     cipher_direction )
{
    ifstream input( in_text, ios::binary );
    if( !input ) {
        cerr << "Unable to open " << in_text << " for input!" << endl;
        return;
    }

    ofstream output( out_text, ios::binary );
    if( !output ) {
        cerr << "Unable to open " << out_text << " for writing!" << endl;
        return;
    }

    // Create a C style array dynamically with the required block size.
    size_t size = cipher.block_size( );
    unique_ptr<BlockCipher::octet_type[]> buffer( new BlockCipher::octet_type[size] );
    BlockCipher::octet_type *p = buffer.get( );

    // Keep reading the input until we get to the end-of-file.
    while( input ) {
        // Note that the read() and write() methods expect type char* which is a poor choice for
        // representing binary data. Unfortunately converting from unsigned char* to char* needs
        // the heavy handed reinterpret_cast.
        input.read( reinterpret_cast<char*>( p ), size );
        if( input.gcount( ) == 0 ) break;

        if( cipher_direction == Direction::Encrypt )
            cipher.encrypt( p );
        else
            cipher.decrypt( p );

        output.write( reinterpret_cast<char*>( p ), size );
    }
}


int Main( int argc, char *argv[] )
{
    Direction desired_direction;

    // Are there sufficient command line arguments?
    if( argc != 5 ) {
        cerr << "Usage: " << argv[0] << " [-e|-d] passphrase input-file output-file" << endl;
        return EXIT_FAILURE;
    }

    // Are we encrypting or decrypting today?
    if( strcmp( argv[1], "-e" ) == 0 )
        desired_direction = Direction::Encrypt;
    else if( strcmp( argv[1], "-d" ) == 0 )
        desired_direction = Direction::Decrypt;
    else {
        cerr << "Error! One of -e or -d is required." << endl;
        return EXIT_FAILURE;
    }

    // Check the passphrase length.
    // TODO: Consult the cipher engine about key requirements.
    // TODO: Hash the passphrase or do some similar preprocessing.
    const char *passphrase = argv[2];
    size_t passphrase_length = strlen( passphrase );
    if( passphrase_length < 4 ) {
        cerr << "Error! Passphrase is too short. At least four characters are required." << endl;
        return EXIT_FAILURE;
    }
    // Round the length down to a multiple of 32 bits.
    size_t adjusted_length = 4 * (passphrase_length/4);
    if( adjusted_length != passphrase_length ) {
        cerr << "Warning! Last "
             << passphrase_length - adjusted_length
             << " characters of passphrase not considered." << endl;
    }
    if( adjusted_length > 56 ) {
        cerr << "Warning! Passphrase is too long. Only 56 characters used." << endl;
    }

    // Set up the engine.
    BlowfishCipher blowfish_engine( reinterpret_cast<const BlockCipher::octet_type *>( passphrase ),
                                    adjusted_length );
    const BlockCipher::octet_type iv[] = { 0, 1, 2, 3, 4, 5, 6, 7 };  // Arbitrary and fixed for now.
    CBCCipher cipher_engine( iv, blowfish_engine );

    // Encrypt/Decrypt the file.
    cipher_file( argv[3], argv[4], cipher_engine, desired_direction );
    
    return EXIT_SUCCESS;
}


int main( int argc, char *argv[] )
{
    try {
        return Main( argc, argv );
    }
    catch( const BlockCipher::NotImplemented &ex ) {
        cerr << "Unhandled BlockCipher::NotImplemented exception: " << ex.what( ) << endl;
    }
    catch( ... ) {
        cerr << "Unhandled exception!" << endl;
    }
    return EXIT_FAILURE;
}
