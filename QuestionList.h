#ifndef QUESTIONLIST_H
#define QUESTIONLIST_H

#include <vector>
#include <string>

#include "QuestionBase.h"

class QuestionList
{
public:
    QuestionList();
    QuestionType getType() const;
    std::string getText() const;
    const std::string* getLabels() const;

    bool isCurrentCheckpoint() const;
    bool testAnswer(const std::string &answer);

    void saveTo(const std::string& path) const;
    void loadFrom(const std::string& path);

    std::string getSaveData() const;
    void loadSaveData(const std::string& saveData);

    void advance();
private:

    listtype m_list={};
    std::vector<std::string> m_saveData;
    unsigned int m_counter = 0;
};

#endif /* QUESTIONLIST_H */

