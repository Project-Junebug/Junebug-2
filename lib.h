#ifndef LIB_H
#define LIB_H

#include <vector>
#include <algorithm>

namespace lib {

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

}

#endif // LIB_H
