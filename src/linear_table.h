//#pragma once

#ifndef __LINE_TABLE_H__
#define __LINE_TABLE_H__

#include "base_table.h"

class LineTable : public BaseTable
{
	Data* dat;
	int size;
	int capacity;
  static const size_t STEP_SIZE = 1000;
	void repacking();
public:
	LineTable() : BaseTable()
	{
		capacity = STEP_SIZE;
		size = 0;
		dat = new Data[capacity];
	}
	void Delete(const string& key);
	void Insert(const Data& d);
	Data* Find(const string& key);
	void Print();
	~LineTable();
};
#endif
