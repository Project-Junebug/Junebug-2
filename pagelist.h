#ifndef PAGELIST_H
#define PAGELIST_H

#define SAVE_SPLIT "\u0011"
#define SAVE_FREQUENCY 5

#include <QString>

struct Page {
    enum class PageType : char {
        Info,
        Question,
        Terminator
    };
    PageType s_type;
    QString s_text;
    QString s_answer;

    QString s_prompt;

    /**
     * @brief Page - Struct constructor
     * @param type - Page Type
     * @param question - The text to be displayed in the question box
     * @param answer - The answer to the question to be hashed using SHA-3
     * @param prompt
     */
    Page(PageType type, QString text, QString answer="", QString prompt="Put your answer here..."){
        s_type=type;
        s_text=text;
        s_answer=answer;
        s_prompt=prompt;
    }
    /**
     * @brief Page - Default constructor that should never be used
     */
    Page(){
        s_type=PageType::Terminator;
        s_prompt=s_answer=s_text="SOMETHING'S CLEARLY WRONG WITH THIS";

    }

};

class PageList
{
public:
    Page getNextPage() const;
    QString getSaveData() const;
private:
    void initPages();

    unsigned mutable int mM_counter = 0;
    std::vector< Page > m_list;

};

#endif // PAGELIST_H
