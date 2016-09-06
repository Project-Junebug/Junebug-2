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

