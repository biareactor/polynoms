//#pragma once

#ifndef __HASH_TABLE_ON_LIST_H__
#define __HASH_TABLE_ON_LIST_H__

//#include <string>
//#include <iostream>
#include "base_table.h"

using namespace std;
struct link_t
{
	Data data;
	link_t* pNext;
};

class hash_table_on_lists : public BaseTable
{
	link_t* Tab[1000];

public:
	hash_table_on_lists()
	{
		for (int i = 0; i < 1000; i++)
			Tab[i] = nullptr;

	}
	~hash_table_on_lists();
	Data* Find(const string& key);
	void Insert(const Data& data);
	void Delete(const string& key); // 
	void Print();
};

#endif