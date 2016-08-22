/* 
 * File:   QuestionCheckbox.h
 * Author: Joseph
 *
 * Created on 07 August 2016, 11:51
 */

#ifndef QUESTIONCHECKBOX_H
#define QUESTIONCHECKBOX_H

#include "QuestionBase.h"

class QuestionCheckbox : public QuestionBase
{
public:
    QuestionCheckbox(const std::string &info, const std::vector<hashtype> &ansHash, const std::string (&labels)[4]);
    
    const std::string* getLabels() const;
    
protected:
    std::string m_labels[4];
    
};

#endif /* QUESTIONCHECKBOX_H */

