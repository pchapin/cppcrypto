/*! \file   BlockCipher.cpp
 *  \brief  A class hierarchy for doing block encryption.
 *  \author Peter Chapin <chapinp@proton.me>
 */

module cppCrypto;

import <cstring>;
import <string>;

using namespace std;

// Methods of BlowfishCipher
// ------------------------

BlowfishCipher::BlowfishCipher( const octet_type *key_material, int key_size )
{
    throw NotImplemented( "BlowfishCipher::BlowfishCipher" );
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
