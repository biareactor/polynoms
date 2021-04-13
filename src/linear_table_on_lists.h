#pragma once

#ifndef __LINTABLIST_H__
#define __LINTABLIST_H__

#include "base_table.h"

struct Link
{
	Data data;
	Link* pNext;
};

class LinTabList : public BaseTable
{
	Link* Head;
	int Amount;
public:
	LinTabList();
	~LinTabList();

	Data* Find(const std::string& key);
	void Insert(const Data& data);
	void Delete(const std::string& key);
	void Print();
};

#endif