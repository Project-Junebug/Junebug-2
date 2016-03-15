#include <cassert>
#include <cmath>

#include <QMessageBox>

#include "pagelist.h"
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
            if(!((isInfo || hash==current.s_answer)||(data.size()-1==i && j==data.at(i).length()-1))){
                int i=1;
            }

            if(isInfo || hash==current.s_answer){
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
    return Page(m_current.s_type, m_current.s_text, 0, false, m_current.s_prompt);
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

    if(HASHOAT(answer.toUtf8().constData())==m_current.s_answer){
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
    if(HASHOAT(answer.toUtf8().constData())==m_current.s_answer){
        ++mM_counter;
        mM_saveData+=answer;
        mM_saveData+=(m_current.s_isCheckpoint ? CHECKPOINT_SPLIT : SPLIT);

        return true;
    }
    return false;
}
