/*! \file   BlockCipher.cpp
 *  \brief  A class hierarchy for doing block encryption.
 *  \author Peter Chapin <chapinp@proton.me>
 */

module;

#include <iostream>  // Needed only for debugging messages (below).
#include <string>

module cppCrypto;

using namespace std;

namespace cppCrypto_0_0_0 {

    // Methods of BlowfishCipher
    // ------------------------

    BlowfishCipher::BlowfishCipher( const octet_type *key_material, int key_size )
    {
        // g++ 11.3 crashes with a segmentation fault when 'throw_me' is constructed.
        // I believe this might be a problem with the compiler mis-compiling the module.
        // Note that NotImplemented is a nested class with an inline constructor.
        cout << "About to construct an exception!" << endl;
        NotImplemented throw_me{ "BlowfishCipher::BlowfishCipher" };
    
        cout << "About to throw an exception!" << endl;
        throw throw_me;
    }


    size_t BlowfishCipher::block_size( ) const
    {
        return 8;  // Always 64 bits.
    }


    void BlowfishCipher::encrypt( octet_type *block )
    {
        throw NotImplemented( "BlowfishCipher::encrypt" );
    }


    void BlowfishCipher::decrypt( octet_type *block )
    {
        throw NotImplemented( "BlowfishCipher::encrypt" );
    }


    // Methods of CastCipher
    // ------------------------

    size_t CastCipher::block_size( ) const
    {
        return 8;  // Always 64 bits.
    }


    void CastCipher::encrypt( octet_type *block )
    {
        throw NotImplemented( "CastCipher::encrypt" );
    }


    void CastCipher::decrypt( octet_type *block )
    {
        throw NotImplemented( "CastCipher::decrypt" );
    }


    // Methods of DESCipher
    // --------------------
    
    size_t DESCipher::block_size( ) const
    {
        return 8;   // Always 64 bits.
    }

    void DESCipher::encrypt( octet_type *block )
    {
        throw NotImplemented( "DESCipher::encrypt" );
    }


    void DESCipher::decrypt( octet_type *block )
    {
        throw NotImplemented( "DESCipher::decrypt" );
    }


    // Methods of AESCipher
    // --------------------

    size_t AESCipher::block_size( ) const
    {
        return 16;   // Always 128 bits.
    }

    void AESCipher::encrypt( octet_type *block )
    {
        throw NotImplemented( "AESCipher::encrypt" );
    }


    void AESCipher::decrypt( octet_type *block )
    {
        throw NotImplemented( "AESCipher::decrypt" );
    }

}
