#include "QuestionInfo.h"

QuestionInfo::QuestionInfo(const std::string& info):
    QuestionBase(info, {0}){
}

bool QuestionInfo::testAnswer(const std::string& answer) {
    return true;
}

QuestionInfo* QuestionInfo::setCheckpoint(bool isCheckpoint) {
    m_isCheckpoint=isCheckpoint;
    return this;
}
