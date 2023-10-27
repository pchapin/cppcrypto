/*! \file   CBCCipher.cpp
 *  \brief  A class that wraps a block cipher in CBC mode.
 *  \author Peter Chapin <spicacality@kelseymountain.org>
 */

module cppCrypto;

import <cstring>;
import <memory>;

using namespace std;

namespace cppCrypto_0_0_0 {

    CBCCipher::CBCCipher( const octet_type *iv, BlockCipher &cipher ) :
            old_ciphertext( new octet_type[cipher.block_size( )] ),
            underlying( cipher ) {
        memcpy( old_ciphertext.get( ), iv, underlying.block_size( ));
    }


    size_t CBCCipher::block_size( ) const {
        return underlying.block_size( );
    }


    void CBCCipher::encrypt( octet_type *block ) {
        // XOR the old ciphertext into the plaintext.
        for( size_t i = 0; i < underlying.block_size( ); ++i ) {
            block[i] ^= old_ciphertext.get( )[i];
        }

        // Use the underlying encryption engine to encrypt what we've got in place.
        underlying.encrypt( block );

        // Save the ciphertext for next time.
        memcpy( old_ciphertext.get( ), block, underlying.block_size( ));
    }


    void CBCCipher::decrypt( octet_type *block ) {
        // Save the ciphertext aside for later.
        unique_ptr < octet_type[] > temp{ new octet_type[underlying.block_size( )] };
        memcpy( temp.get( ), block, underlying.block_size( ));

        // Use the underlying decryption engine to decrypt what we've got in place.
        underlying.decrypt( block );

        // XOR the old cipher text into the plaintext
        for( size_t i = 0; i < underlying.block_size( ); ++i ) {
            block[i] ^= old_ciphertext.get( )[i];
        }

        // Copy the saved ciphertext for next time.
        memcpy( old_ciphertext.get( ), temp.get( ), underlying.block_size( ));
    }

}
