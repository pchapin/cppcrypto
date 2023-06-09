/*! \file   cppCrypto.ixx
 *  \brief  The primary module interface unit for the cppCrypto module.
 *  \author Peter Chapin <spicacality@kelseymountain.org>
 *
 * The .ixx extension is required(?) by Visual Studio. For clang and g++ it is necessary to
 * explicitly inform the compiler that this file is C++ with the -x c++ command line option.
 * That is handled by the Makefile.
 */

module;

#include <memory>
#include <stdexcept>
#include <string>

// This is the module declaration.
export module cppCrypto;

export namespace cppCrypto_0_0_0 {

    class BlockCipher {
    public:
        //! A class to throw when an unimplemented method is called.
        class NotImplemented : public std::logic_error {
        public:
            NotImplemented( const std::string &message );
        };

        //! A type for representing raw data.
        typedef unsigned char octet_type;

        //! A virtual destructor to ensure that objects of a subtype are properly cleaned up.
        virtual ~BlockCipher( );

        //! Returns the number of octets in a block.
        virtual std::size_t block_size( ) const = 0;

        //! Encrypts the given block.
        /*!
         * This method assumes block points at a region of memory that is at least one block
         * size in length. It replaces the first block_size( ) bytes of that memory with the
         * encrypted version of the data originally stored there.
         */
        virtual void encrypt( octet_type *block ) = 0;

        //! Decrypts the given block.
        /*!
         * This method assumes block points at a region of memory that is at least one block
         * size in length. It replaces the first block_size( ) bytes of that memory with the
         * decrypted version of the data originally stored there (assumed to be encrypted).
         */
        virtual void decrypt( octet_type *block ) = 0;
    };


    class BlowfishCipher : public BlockCipher {
    public:
        BlowfishCipher( const octet_type *key_material, int key_size );

        virtual std::size_t block_size( ) const override;
        virtual void encrypt( octet_type *block ) override;
        virtual void decrypt( octet_type *block ) override;
    private:
        // ...
    };


    class CastCipher : public BlockCipher {
    public:
        virtual std::size_t block_size( ) const override;
        virtual void encrypt( octet_type *block ) override;
        virtual void decrypt( octet_type *block ) override;
    private:
        // ...
    };


    class DESCipher : public BlockCipher {
    public:
        virtual std::size_t block_size( ) const override;
        virtual void encrypt( octet_type *block ) override;
        virtual void decrypt( octet_type *block ) override;
    private:
        // ...
    };


    class AESCipher : public BlockCipher {
    public:
        virtual std::size_t block_size( ) const override;
        virtual void encrypt( octet_type *block ) override;
        virtual void decrypt( octet_type *block ) override;
    private:
        // ...
    };


    class CBCCipher : public BlockCipher {
    public:
        CBCCipher( const octet_type *iv, BlockCipher &cipher );

        // For now, prohibit copying. This can be reviewed later.
        CBCCipher( const CBCCipher & ) = delete;
        CBCCipher &operator=( const CBCCipher & ) = delete;

        virtual std::size_t block_size( ) const override;
        virtual void encrypt( octet_type *block ) override;
        virtual void decrypt( octet_type *block ) override;
        
    private:
        std::unique_ptr<octet_type[]> old_ciphertext;
        BlockCipher &underlying;
    };


    // Implementations of Inline Methods
    // ---------------------------------

    inline BlockCipher::NotImplemented::NotImplemented( const std::string &message ) :
        std::logic_error( message )
    { }


    inline BlockCipher::~BlockCipher( )
    { }

}
