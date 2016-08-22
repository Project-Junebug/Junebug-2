#ifndef LIB_H
#define LIB_H

#include <string>
#include <vector>
#include <memory>

#include "QuestionBase.h"

namespace lib{
hashtype HASH(std::string str);

int find(const hashtype& object, const std::vector<hashtype, std::allocator<hashtype> >& vector);

void getQuestions(listtype* list);

std::string toLower(const std::string& string);

void writeFile(const std::string& path, const std::string& output);
void readFile(const std::string& path, std::string& output);

std::vector<std::string> split(const std::string& s, const char* c);

std::string xorEncode(const std::string& toEncrypt);
constexpr const char* xorEncode(const char* string, size_t strlen);
}

#endif /* LIB_H */

