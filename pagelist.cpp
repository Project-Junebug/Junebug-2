#include "pagelist.h"
#include <cassert>

Page PageList::getNextPage() const {
    ++mM_counter;
    assert(mM_counter<m_list.size());
    return m_list.at(mM_counter-1);
}

QString PageList::getSaveData() const {
    QString data="";
    for(unsigned int i=0; i<(mM_counter-(mM_counter%SAVE_FREQUENCY)); ++i) {
        data+=m_list.at(i).s_answer;
        if(i!=mM_counter) data+=SAVE_SPLIT;
    }
    return data;
}
