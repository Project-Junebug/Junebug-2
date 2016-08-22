#ifndef HASH_H
#define HASH_H

#include <cctype>
#include <string>

#define DEFAULT_SIZE 1009

//Below is shamelessly stolen from https://bcaptain.wordpress.com/2013/10/18/constexpr-hash-function-in-c/

constexpr unsigned int oat_part_one( const std::size_t& h, const char c ) {
    return ( h + static_cast<unsigned int>( c ) );
}

constexpr unsigned int oat_part_two( const std::size_t& h ) {
    return ( h << 10 );
}

constexpr unsigned int oat_part_three( const std::size_t& h ) {
    return ( h >> 6 );
}

constexpr unsigned int oat_part_four( const std::size_t& h ) {
    return ( h << 3 );
}

constexpr unsigned int oat_part_five( const std::size_t& h ) {
    return ( h >> 11 );
}

constexpr unsigned int oat_part_six( const std::size_t& h ) {
    return ( h << 15 );
}

constexpr std::size_t string_length( const char* str, std::size_t index = 0 ) {
    return ( str == nullptr || str[index] == '\0' ) ? 0 : 1 + string_length( str, index+1 );
}
/**
 * @brief HASHOAT
 * @param str - String to be hashed
 * @param size - No clue, don't use
 * @param idx - No clue, don't use
 * @param h - No clue, don't use
 * @return Hash of str
 */
constexpr unsigned int HASHOAT( const char* str, const std::size_t size=DEFAULT_SIZE, const std::size_t idx=0, const std::size_t h=0 ) {
    return (
        ( idx == string_length( str ) ) ? (
            (
                (
                    ( h + oat_part_four( h ) ) ^
                    oat_part_five( h + oat_part_four( h ) )
                ) +
                oat_part_six(
                    ( h + oat_part_four( h ) ) ^
                    oat_part_five( h + oat_part_four( h ) )
                )
            ) % size
        ) : (
            HASHOAT( str, size, idx+1,
                (
                    oat_part_one( h, str[idx] ) +
                    oat_part_two( h + static_cast< unsigned int>( str[idx] ) )
                ) ^
                oat_part_three( oat_part_one( h, str[idx] ) +
                            oat_part_two( oat_part_one( h, str[idx] ) )
                )
            )
        )
    );
}

/**
 * @brief operator "" _HASH
 * @param str - C-style string to be hashed
 * @param length - length of the string
 * @return the hash of a string
 */
constexpr unsigned int operator ""_HASH(char const* str, unsigned int length){
    return HASHOAT(str, length*0+DEFAULT_SIZE); //To stop "unused parameter" warnings
}

#endif /* HASH_H */

