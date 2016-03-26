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
    mM_saveData.truncate(mM_saveData.lastIndexOf(CHECKPOINT_SPLIT)+1);
    return mM_saveData;
}

/**
 * @brief loadSaveData
 * @param saveData - list of data to be loaded
 */
void PageList::loadSaveData(const QString& saveData) const {
    //TODO 2.sav - we only got to test question? but we have the answer.
    mM_saveData="";
    QStringList data;
    {
        QStringList split=saveData.split(CHECKPOINT_SPLIT);

        for (QString i: split) {
            for(QString j: i.split(SPLIT)){
                data.append(j);
            }
        }
    }
    PageList list;
    unsigned int checkpoint = 0;
    for (int i = 0; i < data.size(); ++i) {
        Page current = list.getDisplayData();
        if(current.s_isCheckpoint)
            checkpoint=i;
        std::vector<bool> answer;
        if(data.at(i)=="" && current.s_type!=PageType::Info){
            break;
        }
        switch(current.s_type){
        case(PageType::Info):
            if(!list.checkAnswer())
                loadError();
            break;
        case(PageType::Textbox):
            if(!list.checkAnswer(data.at(i)))
                loadError();
            break;
        case(PageType::Checkbox):
            for(QString j: data.at(i)){
                answer.push_back(j.toInt());
            }
            if(!list.checkAnswer(answer))
                loadError();
            break;
        default:
            break;
        }
    }

    mM_counter=checkpoint;
    mM_saveData=list.getSaveData();
    mM_saveData.chop(1);
}

/**
 * @brief PageList::getDisplayData
 * @return A page only populated with only s_type, s_text, s_isCheckpoint, and s_prompt. s_answer is {0}
 */
Page PageList::getDisplayData() const {
    if(mM_counter==34||mM_counter==29){
        qDebug()<<mM_counter;
        qDebug()<<"";
    }
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
    mM_saveData+=(m_current.s_isCheckpoint ? CHECKPOINT_SPLIT : SPLIT);
    return true;
}

bool PageList::checkAnswer(const QString& answer) const {
    assert(m_current.s_type==PageType::Textbox);
    assert(mM_counter+1<m_list.size());

    unsigned int hash = HASHOAT(answer.toUtf8().constData());

    if(lib::contains(m_current.s_answers, hash)){
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
    assert(answers.size()==4);

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

void PageList::loadError() const {
    QMessageBox::critical(0, "Load Error", "I'm sorry, something's wrong with your save. If you've tried to modify it,"
                                           "put it back how it was.");
    exit(-1);
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
