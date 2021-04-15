#ifndef __HASHTABLIN_H__
#define __HASHTABLIN_H__

#include "base_table.h"

class HashTabLin : public BaseTable
{
    static const size_t SIZE = 1000;
    static const size_t STEP = 7;
    Data* Tab[SIZE];
public:
    HashTabLin()
    {
        for (int i = 0; i < SIZE; i++)
            Tab[i] = nullptr;
    }
    ~HashTabLin();

    Data* Find(const std::string& key);
    void Insert(const Data& data);
    void Delete(const std::string& key);
    void Print();
};

#endif