#include <cassert>
#include <cmath>

#include <QMessageBox>

#include "pagelist.h"
#include "hash.h"
#include "lib.h"

#ifdef ACTUAL_QUESTIONS
#include "initquestions.ignore.h"
#endif

/**
 * @brief PageList::PageList
 * Ctor for PageList
 */
PageList::PageList(){
    initPages();
    m_current=m_list.at(mM_counter);
}

/**
 * @brief PageList::getSaveData
 * @return The list of data to be written to save file
 */
QString PageList::getSaveData() const {
    QString ret="";

    for (unsigned int i = 0; i < mM_saveData.size(); ++i) {
        ret+=mM_saveData.at(i);
        ret+=SPLIT;
    }

    return ret;
}

/**
 * @brief loadSaveData
 * @param saveData - list of data to be loaded
 */
void PageList::loadSaveData(const QString& saveData) const {
    mM_saveData=saveData.split(SPLIT).toVector().toStdVector();

    std::vector<unsigned int> hashData;
    std::vector<Page> pages;


    for(unsigned int i = 0; i < mM_saveData.size(); ++i) {
        hashData.push_back(HASHOAT(mM_saveData.at(i).toUtf8().constData()));
        pages.push_back(m_list.at(i));
    }
    for(mM_counter = 0; mM_counter < hashData.size(); ++mM_counter) {

        if(!lib::contains(pages.at(mM_counter).s_answers, hashData.at(mM_counter))){
            break;
        }
    }

}

/**
 * @brief PageList::getDisplayData
 * @return A page only populated with only s_type, s_text, s_isCheckpoint, and s_prompt. s_answer is {0}
 */
Page PageList::getDisplayData() const {
    assert(mM_counter<m_list.size());
    m_current = m_list.at(mM_counter);
    return Page(m_current.s_type, QString::number(m_numbers.at(mM_counter))+") "+m_current.s_text,{0},
                m_current.s_isCheckpoint, m_current.s_prompt);
}

/**
 * @brief PageList::checkAnswer
 * @return true if correct
 */
bool PageList::checkAnswer() const {
    assert(m_current.s_type==PageType::Info);
    assert(mM_counter+1<m_list.size());
    ++mM_counter;
    mM_saveData.push_back("");
    return true;
}

bool PageList::checkAnswer(const QString& answer) const {
    assert(m_current.s_type==PageType::Textbox);
    assert(mM_counter+1<m_list.size());

    unsigned int hash = HASHOAT(answer.toUtf8().constData());

    if(lib::contains(m_current.s_answers, hash)){
        ++mM_counter;
        mM_saveData.push_back(answer);
        return true;
    }
    return false;
}

bool PageList::checkAnswer(const std::vector<bool> &answers) const{
    assert(m_current.s_type==PageType::Checkbox);
    assert(mM_counter+1<m_list.size());
    assert(answers.size()==4);

    QString answer="";

    for(unsigned int i = 0; i < answers.size(); ++i) {
        answer+=QString::number(answers.at(i));
    }

    //answer is now a QString like "1011"
    if(lib::contains(m_current.s_answers, HASHOAT(answer.toUtf8().constData()))){
        ++mM_counter;
        mM_saveData.push_back(answer);
        return true;
    }
    return false;
}

#ifndef ACTUAL_QUESTIONS

void PageList::initPages(){
    m_numbers = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};

    m_list = {
        Page(PageType::Info, "Page 0", {0}, true),
        Page(PageType::Textbox, "Question 1, a=123", {"123"_HASH}),
        Page(PageType::Textbox, "Question 2, a=123 or 1234", {"123"_HASH, "1234"_HASH}),
        Page(PageType::Textbox, "Question 3, a=123", {"123"_HASH}),
        Page(PageType::Checkbox, "Checkbox 4, a=1011", {"1011"_HASH}, true, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Checkbox, "Checkbox 5, a=0011", {"0011"_HASH}, false, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Checkbox, "Checkbox 6, a=1001", {"1001"_HASH}, false, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Checkbox, "Checkbox 7, a=0010 or 0110", {"0010"_HASH, "0110"_HASH}, false, "A" SPLIT "B" SPLIT
                                                                                                  "C" SPLIT "D"),
        Page(PageType::Textbox, "Question 8, a=123", {"123"_HASH}, true),
        Page(PageType::Textbox, "Question 9, a=123", {"123"_HASH}),
        Page(PageType::Textbox, "Question 10, a=123", {"123"_HASH}),
        Page(PageType::Info, "Page 11", {0}, true),
        Page(PageType::Terminator, "Terminator")
    };
}

#endif
