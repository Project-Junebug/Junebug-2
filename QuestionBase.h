#ifndef QUESTIONBASE_H
#define QUESTIONBASE_H

#include <string>
#include <vector>

typedef unsigned int hashtype;

enum class QuestionType : char {
    BASE,
    INFO,
    CHECKBOX,
    TERMINATOR
};

class QuestionBase
{
public:
    QuestionBase(const std::string &info, const std::vector<hashtype> &anshash, bool isCheckpoint=false);
    QuestionBase(const std::string& info, const hashtype& anshash, bool isCheckpoint=false);
    std::string getText() const;
    QuestionBase* setCheckpoint(bool Checkpoint);
    bool isCheckpoint() const;
    bool testAnswer(const std::string &answer) const;

protected:
    std::string m_info;
    std::vector<hashtype> m_ansHash;
    bool m_isCheckpoint;
};

typedef std::vector<std::tuple<QuestionBase*, QuestionType> > listtype;

#endif // QUESTIONBASE_H
