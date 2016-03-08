#ifndef PAGELIST_H
#define PAGELIST_H

#define SAVE_SPLIT "\u0011"

#include <QString>

enum class PageType : char {
    Info,
    Question,
    Terminator
};

struct Page {
    PageType s_type;
    QString s_question;
    QString s_answer;

    QString s_prompt;

    /**
     * @brief Page - Struct constructor
     * @param type - Page Type
     * @param question - The text to be displayed in the question box
     * @param answer - The answer to the question to be hashed using SHA-3
     * @param prompt
     */
    Page(PageType type, QString question, QString answer="", QString prompt="Put your answer here..."){
        s_type=type;
        s_question=question;
        s_answer=answer;
        s_prompt=prompt;
    }
    Page(){
        s_type=PageType::Terminator;
        s_prompt=s_answer=s_question="SOMETHING'S CLEARLY WRONG WITH THIS";

    }

};

class PageList
{
public:
    PageList();

    Page getNextQuestion() const;
    QString getSaveData() const;
private:
    unsigned mutable int mM_counter = 0;
    std::vector< Page > m_list;

};

#endif // PAGELIST_H
