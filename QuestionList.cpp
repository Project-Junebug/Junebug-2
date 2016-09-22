#include <iostream>
#include <fstream>
#include <cassert>
#include <iterator>

#include <QDebug>

#include "QuestionList.h"
#include "QuestionCheckbox.h"
#include "QuestionInfo.h"
#include "lib.h"
#include "hash.h"

#define DC1 "\u0012"
#define DC2 "\u0013"

QuestionList::QuestionList(){
    lib::getQuestions(&m_list);
}

QuestionType QuestionList::getType() const {
    return std::get<1>(m_list[m_counter]);
}

std::string QuestionList::getText() const {
    QuestionBase* a= std::get<0>(m_list[m_counter]);
    return a->getText();
}

const std::string* QuestionList::getLabels() const{
    if(getType()!=QuestionType::CHECKBOX){
        return nullptr;
    }
    return static_cast<QuestionCheckbox*>(std::get<0>(m_list[m_counter]))->getLabels();

}

bool QuestionList::testAnswer(const std::string& answer) {
    bool isCorrect = false;
    switch(getType()){
    case QuestionType::BASE:
        isCorrect = static_cast<QuestionBase*>(std::get<0>(m_list[m_counter]))->testAnswer(answer);
        break;
    case QuestionType::CHECKBOX:
        isCorrect = static_cast<QuestionCheckbox*>(std::get<0>(m_list[m_counter]))->testAnswer(answer);
        break;
    case QuestionType::INFO:
        isCorrect = static_cast<QuestionInfo*>(std::get<0>(m_list[m_counter]))->testAnswer(answer);
        break;
    case QuestionType::TERMINATOR:
        isCorrect=false;
        break;
    }
    if(isCorrect){
        m_saveData.push_back(answer);
    }
    return isCorrect;
}

void QuestionList::advance() {
    m_counter++;
}

bool QuestionList::isCurrentCheckpoint() const {
    bool isCheckpoint = false;
    QuestionType type=getType();
    switch(type){
    case QuestionType::BASE:
    case QuestionType::TERMINATOR:
        isCheckpoint = static_cast<QuestionBase*>(std::get<0>(m_list[m_counter]))->isCheckpoint();
        break;
    case QuestionType::CHECKBOX:
        isCheckpoint = static_cast<QuestionCheckbox*>(std::get<0>(m_list[m_counter]))->isCheckpoint();
        break;
    case QuestionType::INFO:
        isCheckpoint = static_cast<QuestionInfo*>(std::get<0>(m_list[m_counter]))->isCheckpoint();
        break;
    }
    return isCheckpoint;
}

std::string QuestionList::getSaveData() const{
    std::string writeData="";
    for(unsigned int i = 0; i < m_saveData.size(); i++) {
        writeData+=m_saveData[i];
        writeData+=(i<m_saveData.size()-1)?DC1:"";
    }
    writeData=std::to_string(HASH(writeData.c_str()))+DC2+writeData;
    return lib::xorEncode(writeData);
}

void QuestionList::loadSaveData(const std::string& saveData){
    std::string checksum="";
    std::string answers="";
    {
        std::vector<std::string> temp={};
        temp=lib::split(lib::xorEncode(saveData), DC2);
        checksum=temp[0];
        answers=temp[1];
    }
    std::vector<std::string> newData={};
    newData=lib::split(answers, DC1);
    if(newData.size()>1 && newData.at(2)==""){
        newData.erase(newData.begin());
    }
    int lastCheckpoint=0;
    {
        QuestionList testList = QuestionList();
        for (unsigned int i = 0; i < newData.size(); i++) {
            if (!testList.testAnswer(newData[i])) {
                return;
            }
            if(testList.isCurrentCheckpoint()){
                lastCheckpoint=i;
            }
            testList.advance();
        }
        bool boolArray[3]={false};
        boolArray[0]=testList.getType()==QuestionType::INFO;
        boolArray[1]=boolArray[0]?testList.testAnswer(""):false;
        boolArray[2]=testList.isCurrentCheckpoint();
        if(boolArray[0]&&boolArray[1]&&boolArray[2]){
            testList.advance();
            ++lastCheckpoint;
        }
    }
    newData.resize(lastCheckpoint);
    m_saveData=newData;
    m_counter=lastCheckpoint;
}

void QuestionList::saveTo(const std::string& path) const {
    lib::writeFile(path, getSaveData());
}

void QuestionList::loadFrom(const std::string& path) {
    std::string readData="";
    lib::readFile(path, readData);
    loadSaveData(readData);
}
