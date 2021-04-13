#ifndef __HASHTABLIN_H__
#define __HASHTABLIN_H__

#include "base_table.h"

class HashTabLin : public BaseTable
{
    Data* Tab[1000];
public:
    HashTabLin()
    {
        for (int i = 0; i < 1000; i++)
            Tab[i] = nullptr;
    }
    ~HashTabLin();

    Data* Find(const std::string& key);
    void Insert(const Data& data);
    void Delete(const std::string& key);
    void Print();
};

#endif