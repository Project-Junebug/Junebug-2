#ifndef LIB_H
#define LIB_H

#include <vector>
#include <algorithm>
/*
namespace lib {

template<typename T> //Extra typename is for allocator, apparently
bool my_contains(const std::vector<T, std::allocator<T> >& list, const T& item){
    return std::find(list.begin(), list.end(), item) != list.end();
}
}*/
bool my_contains(std::vector<unsigned int, std::allocator<unsigned int> > const& list, unsigned int const& item){
    return std::find(list.begin(), list.end(), item) != list.end();
}




#endif // LIB_H
