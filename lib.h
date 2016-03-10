#ifndef LIB_H
#define LIB_H

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

constexpr unsigned int HASHOAT( const char* str, const std::size_t size, const std::size_t idx, const std::size_t h ) {
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
constexpr unsigned int operator"" _HASH(char const* str, unsigned int length){
    return HASHOAT(str, length, 41233, 40009);
}

#endif // LIB_H
