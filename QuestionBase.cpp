#include "QuestionBase.h"
#include "lib.h"
#include "hash.h"

#include <cassert>

QuestionBase::QuestionBase(const std::string &info, const std::vector<hashtype> &ansHash, bool isCheckpoint){
    assert(ansHash.size()>0);
    m_info = info;
    m_ansHash = ansHash;
    m_isCheckpoint=isCheckpoint;
}
QuestionBase::QuestionBase(const std::string& info, const hashtype& anshash, bool isCheckpoint){
    m_info=info;
    m_ansHash={anshash};
    m_isCheckpoint=isCheckpoint;
}

bool QuestionBase::testAnswer(const std::string &answer) const{
    return lib::find(HASH(lib::toLower(answer).c_str()), m_ansHash)>-1;
}

std::string QuestionBase::getText() const {
    return m_info;
}

QuestionBase* QuestionBase::setCheckpoint(bool isCheckpoint) {
    m_isCheckpoint = isCheckpoint;
    return this;
}

bool QuestionBase::isCheckpoint() const {
    return m_isCheckpoint;
}

