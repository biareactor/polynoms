#include "linear_table.h"

void LineTable::repacking()
{
	capacity += 1000;
	Data* temp = new Data[capacity];
	if (temp == nullptr)
		throw 5;
	for (int i = 0; i < size; i++)
		temp[i] = dat[i];
	delete[] dat;
	dat = temp;
}

void LineTable::Delete(const string& key)
{
	if (size == 0)
		throw 1;
	Data* d = Find(key);
	if (d != nullptr)
	{
		Data temp = dat[size - 1];
		dat[size - 1] = *d;
		*d = temp;
		size--;
	}
	else 
		throw 2;
}

void LineTable::Insert(const Data& d)
{
	if (size == capacity)
	{
		repacking();
		//add something
	}
	if (Find(d.key) == nullptr)
	{
		dat[size] = d;
		size++;
	}
	else
		throw 3;
}

Data* LineTable::Find(const string& key)
{
	for (int i = 0; i < size; i++)
	{
		if (dat[i].key == key)
			return &dat[i];
	}
	return nullptr;
}

void LineTable::Print()
{
	std::cout << "\tPRINTING LINE TABLE (MASSIV)" << std::endl;
	for (int i = 0; i < size; i++)
		cout << dat[i].key << ":\t" <<dat[i].PolyString <<endl;
	if (size == 0)
		cout << "Empty" <<endl;
}

LineTable::~LineTable()
{
	delete[] dat;
}

