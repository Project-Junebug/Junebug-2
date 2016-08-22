#include "hash.h"
#include "lib.h"
#include "QuestionBase.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

#define MAX_FILE_SIZE 1024

namespace lib{

hashtype HASH(std::string str){
    return HASHOAT(str.c_str(), DEFAULT_SIZE);
}


int find(const hashtype& object, const std::vector<hashtype, std::allocator<hashtype> >& vector){
    for (unsigned int i = 0; i < vector.size(); i++) {
    if(vector[i]==object){
        return i;
    }
    }
    return -1;

}
std::string toLower(const std::string& string){
    std::string data = string.data();
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}

void writeFile(const std::string& path, const std::string& output){
    std::ofstream outf(path.c_str(), std::ios::binary);
    outf << output << std::flush;
    outf.close();
}

void readFile(const std::string& path, std::string& output){
    std::ifstream inf(path.c_str(), std::ios::binary);
    if(!inf){
        std::cout << "File open failed.";
    }
    std::vector<char> buffer((
                std::istreambuf_iterator<char>(inf)),
                (std::istreambuf_iterator<char>()));
    output.append(buffer.begin(), buffer.end());
}

std::vector<std::string> split(const std::string& s, const char* c) {
   using std::string;
   string::size_type i = 0;
   string::size_type j = s.find(c);
   std::vector<string> v;

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
   return v;
}

#define KEY "K4{*M^W?V<7uLj5"
std::string xorEncode(const std::string& toEncrypt) {
    std::string output = toEncrypt;
    for (unsigned int i = 0; i < toEncrypt.size(); i++){
        output[i] = toEncrypt[i] ^ KEY[i % (sizeof(KEY) / sizeof(char))];
    }
    return output;
}
#undef KEY

}
