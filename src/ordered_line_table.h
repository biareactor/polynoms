//#pragma once

#ifndef __ORDERED_LINE_TABLE_H__
#define __ORDERED_LINE_TABLE_H__

//#include <string>
//#include <iostream>
#include "base_table.h"

using namespace std;

class ordered_line_table : public BaseTable
{
  static const size_t SIZE = 1000;
	Data* Tab[SIZE];
	int size;
public:
	ordered_line_table() :BaseTable() 
	{
		for (int i = 0; i < SIZE; i++)
			Tab[i] = nullptr;
		size = 0;
	}
	~ordered_line_table();
	Data* Find(const string& key);
	void Insert(const Data& data);
	void Delete(const string& key); // 
	void Print();
	int Compare(string k1, string k2);
};

#endif