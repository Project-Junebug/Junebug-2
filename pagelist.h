#ifndef PAGELIST_H
#define PAGELIST_H

#define SPLIT "\u0011"
#define CHECKPOINT_SPLIT "\u0012"

#include <QString>
#include <QStringList>
#include <QDebug>

#include <vector>
#include <cassert>

enum class PageType : char {
    Info,
    Textbox,
    Checkbox,
    Terminator
};

struct Page {
    PageType s_type;
    QString s_text;
    unsigned int s_answer;
    QString s_prompt;
    bool s_isCheckpoint;

    /**
     * @brief Page - Struct constructor
     * @param type - Page Type
     * @param question - The text to be displayed in the question box
     * @param answer - The answer to the question to be hashed using SHA-3
     * @param prompt
     */
    Page(PageType type, QString text, unsigned int answer=0, bool isCheckpoint=false, QString prompt="Put your answer here..."){
        assert((type==PageType::Checkbox)==(prompt.contains(SPLIT)));
        s_type=type;
        s_text=text;
        s_answer=answer;
        s_prompt=prompt;
        s_isCheckpoint=isCheckpoint;
    }
    /**
     * @brief Page - Default constructor that should never be used
     */
    Page(){
        s_type=PageType::Terminator;
        s_prompt=s_text="SOMETHING'S CLEARLY WRONG WITH THIS";
        s_answer=0;
    }
};

class PageList
{
public:
    QString getSaveData() const;
    Page getDisplayData() const;
    void loadSaveData(const QString& saveData) const;
    PageList();

    //checkAnswers
    bool checkAnswer() const;
    bool checkAnswer(const QString& answer) const;
    bool checkAnswer(const std::vector<bool>& answers) const;
private:
    /**
     * @brief initPages
     * Sets the pages
     */
    void initPages();

    /**
     * @brief mM_counter
     * Holds the question counter
     */
    mutable unsigned int mM_counter = 0;

    /**
     * @brief mM_saveData
     * Holds the answers so far
     */
    mutable QString mM_saveData="";

    /**
     * @brief m_list
     * Holds the list of pages
     */
    std::vector< Page > m_list = {Page()};

    /**
     * @brief m_current
     * Holds the current Page
     */
    mutable Page m_current;
};

#endif // PAGELIST_H
