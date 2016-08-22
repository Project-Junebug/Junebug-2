
/* 
 * File:   QuestionCheckbox.cpp
 * Author: Joseph
 * 
 * Created on 07 August 2016, 11:51
 */

#include "QuestionCheckbox.h"

QuestionCheckbox::QuestionCheckbox(const std::string &info, const std::vector<hashtype> &ansHash, const std::string (&labels)[4]):
    QuestionBase(info, ansHash){
    for (int i = 0; i < 4; ++i) {
        m_labels[i]=labels[i];
    }
}

const std::string* QuestionCheckbox::getLabels() const {
    return m_labels;
}