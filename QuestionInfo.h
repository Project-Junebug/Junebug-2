#ifndef QUESTIONINFO_H
#define QUESTIONINFO_H

#include "QuestionBase.h"

class QuestionInfo : public QuestionBase
{
public:
    QuestionInfo(const std::string &info);
    bool testAnswer(const std::string& answer);
    QuestionInfo* setCheckpoint(bool isCheckpoint);
};

#endif /* QUESTIONINFO_H */

