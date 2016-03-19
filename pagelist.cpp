#include <cassert>
#include <cmath>

#include <QMessageBox>

#include "pagelist.h"
#include "hash.h"
#include "lib.h"

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
    return mM_saveData;
}

/**
 * @brief loadSaveData
 * @param saveData - list of data to be loaded
 */
void PageList::loadSaveData(const QString& saveData) const {
    mM_saveData="";
    QStringList split=saveData.split(CHECKPOINT_SPLIT);
    std::vector< QStringList > data;
    for (int i = 0; i < split.size(); ++i) {
        data.push_back(split.at(i).split(SPLIT));
    }
    unsigned int counter = 0;
    unsigned int lastCheckpoint = 0;
    for (unsigned int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data.at(i).length(); ++j) {

            //For debug clarity
            bool isInfo = m_list.at(counter).s_type==PageType::Info;
            auto hash = HASHOAT(data.at(i).at(j).toLower().toUtf8().constData());
            auto current = m_list.at(counter);

            if(isInfo || lib::contains(current.s_answers, hash)){
                mM_saveData+=data.at(i).at(j).toLower();

                if(current.s_isCheckpoint){
                    lastCheckpoint=counter;
                    mM_saveData+=CHECKPOINT_SPLIT;
                } else {
                    mM_saveData+=SPLIT;
                }
                ++counter;
            } else {
                mM_counter=lastCheckpoint;
                mM_saveData.chop(1);
                return;
            }
        }
    }
    mM_counter=lastCheckpoint;
    mM_saveData.chop(1);
}

/**
 * @brief PageList::getDisplayData
 * @return A page only populated with only s_type, s_text and s_prompt. s_answer and s_isCheckpoint are 0 and false, respectively.
 */
Page PageList::getDisplayData() const {
    m_current = m_list.at(mM_counter);
    return Page(m_current.s_type, m_current.s_text, {0}, false, m_current.s_prompt);
}

/**
 * @brief PageList::checkAnswer
 * @return true if correct
 */
bool PageList::checkAnswer() const {
    assert(m_current.s_type==PageType::Info);
    assert(mM_counter+1<m_list.size());
    ++mM_counter;
    mM_saveData+=(m_current.s_isCheckpoint ? CHECKPOINT_SPLIT : SPLIT);
    return true;
}

bool PageList::checkAnswer(const QString& answer) const {
    assert(m_current.s_type==PageType::Textbox);
    assert(mM_counter+1<m_list.size());

    if(lib::contains(m_current.s_answers, HASHOAT(answer.toUtf8().constData()))){
        ++mM_counter;
        mM_saveData+=answer;
        mM_saveData+=(m_current.s_isCheckpoint ? CHECKPOINT_SPLIT : SPLIT);

        return true;
    }
    return false;
}

bool PageList::checkAnswer(const std::vector<bool> &answers) const{
    assert(m_current.s_type==PageType::Checkbox);
    assert(mM_counter+1<m_list.size());

    QString answer="";

    for(unsigned int i = 0; i < answers.size(); ++i) {
        answer+=QString::number(answers.at(i));
    }

    //answer is now a QString like "1011"
    if(lib::contains(m_current.s_answers, HASHOAT(answer.toUtf8().constData()))){
        ++mM_counter;
        mM_saveData+=answer;
        mM_saveData+=(m_current.s_isCheckpoint ? CHECKPOINT_SPLIT : SPLIT);

        return true;
    }
    return false;
}

#ifndef ACTUAL_QUESTIONS

void PageList::initPages(){
    m_list={
        Page(PageType::Info, "Page 0", {0}, true),
        Page(PageType::Textbox, "Question 1, a=123", {"123"_HASH}),
        Page(PageType::Textbox, "Question 2, a=123 or 1234", {"123"_HASH, "1234"_HASH}),
        Page(PageType::Textbox, "Question 3, a=123", {"123"_HASH}),
        Page(PageType::Checkbox, "Checkbox 4, a=1011", {"1011"_HASH}, true, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Checkbox, "Checkbox 5, a=0011", {"0011"_HASH}, false, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Checkbox, "Checkbox 6, a=1001", {"1001"_HASH}, false, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Checkbox, "Checkbox 7, a=0010 or 0110", {"0010"_HASH, "0110"_HASH}, false, "A" SPLIT "B" SPLIT "C" SPLIT "D"),
        Page(PageType::Textbox, "Question 8, a=123", {"123"_HASH}, true),
        Page(PageType::Textbox, "Question 9, a=123", {"123"_HASH}),
        Page(PageType::Textbox, "Question 10, a=123", {"123"_HASH}),
        Page(PageType::Info, "Page 11", {0}, true),
        Page(PageType::Terminator, "Terminator")
    };
}

#endif
