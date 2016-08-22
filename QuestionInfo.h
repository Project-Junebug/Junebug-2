
/*
 * File:   QuestionInfo.h
 * Author: Joseph
 *
 * Created on 07 August 2016, 11:56
 */

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

