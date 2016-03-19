#ifndef HASH_H
#define HASH_H

#include <vector>
#include <algorithm>

#define DEFAULT_SIZE 1009

namespace lib {


//Below is shamelessly stolen from https://bcaptain.wordpress.com/2013/10/18/constexpr-hash-function-in-c/

/**
 * @brief contains
 * @param T - Type contained within list
 * @param A - The allocator for list
 * @param item - the item to detect within list
 * @return Does the vector contain item
 */
template<typename T, typename A>
bool contains(const std::vector<T, A>& list, const T& item){
    return std::find(list.begin(), list.end(), item) != list.end();
}
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
constexpr unsigned int operator"" _HASH(char const* str, unsigned int length){
    return HASHOAT(str, length*0+DEFAULT_SIZE); //To stop "unused parameter" warnings
}

#endif // HASH_H
