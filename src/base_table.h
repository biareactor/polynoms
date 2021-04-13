//#pragma once

#ifndef __BASE_TABLE_H__
#define __BASE_TABLE_H__

#include <vector>

#include "polynom.h"

struct Data
{
	std::string key;
	std::string PolyString;
	Polynom Poly;
};

class BaseTable
{
public:
	virtual Data* Find(const std::string& key) = 0;
	virtual void Insert(const Data& data) = 0;
	virtual void Delete(const std::string& key) = 0;
	virtual void Print() = 0;
	virtual ~BaseTable(){}
};

int HashIt(std::string key);

#endif