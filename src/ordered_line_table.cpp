#include "ordered_line_table.h"

ordered_line_table::~ordered_line_table()
{
	for (int i = 0; i < 1000; i++)
		if (Tab[i] != nullptr)
			delete Tab[i];
}
Data* ordered_line_table::Find(const string& key)
{
	int midd, left = 0, right = size - 1;
	while (left <= right)
	{
		midd = (left + right) / 2;
		if (Compare(Tab[midd]->key, key) == 0)
			return Tab[midd];
		if (Compare(Tab[midd]->key, key) < 0) //если таб раньше key
			left = midd + 1;
		if (Compare(Tab[midd]->key, key) > 0)
			right = midd - 1;
	}
	return nullptr;
	//throw 2;
}
void ordered_line_table::Insert(const Data& data)
{
	if (Find(data.key) != nullptr)
		throw 3;
	string h = "";
	if (Tab[0] != nullptr)
		h = Tab[0]->key;
	int j = 0;
	while (j < size && (Compare(h, data.key) < 0))
	{
		j++;
		if (Tab[j] != nullptr)
			h = Tab[j]->key;
		else
			h = "";
	}
	if (Tab[j] == nullptr)
	{
		Tab[j] = new Data;
		Tab[j]->key = data.key;
		Tab[j]->Poly = data.Poly;
		Tab[j]->PolyString = data.PolyString;
	}
	else
	{
		Tab[size] = new Data;
		for (int i = size; i > j; i--) // при значении < Tab[n-1]
			Tab[i] = Tab[i - 1];
		Tab[j] = new Data;
		Tab[j]->key = data.key;
		Tab[j]->Poly = data.Poly;
		Tab[j]->PolyString = data.PolyString;
	}
	size++;
	return;
}
void ordered_line_table::Delete(const string& key) //
{
	if (Find(key) == nullptr)
		throw 2;
	int midd, left = 0, right = size - 1;
	while (left <= right)
	{
		midd = (left + right) / 2;
		if (Compare(Tab[midd]->key, key) == 0)
		{
			delete Tab[midd];
			for (int i = midd; i < size; i++)
				Tab[i] = Tab[i + 1];
			size--;
			return;
		}
		if (Compare(Tab[midd]->key, key) < 0) //если таб раньше key
			left = midd + 1;
		if (Compare(Tab[midd]->key, key) > 0)
			right = midd - 1;
	}
}
void ordered_line_table::Print()
{
	int k = 0;
	string h;
	std::cout << "\t PRINT ORDERED LINEAR TABLE" << std::endl;
	for (int i = 0; i < size; i++)
	{
		cout << Tab[i]->key << ":\t" << Tab[i]->Poly;
		k++;
	}
	if (k == 0)
		cout << "Empty" << endl;
}
int ordered_line_table::Compare(string k1, string k2) //-, если k1 раньше k2, +, если k2 раньше k1, 0 если равны
{
	string alf = "abcdefghijklmnopqrstuvwxyz";
	//string ALF = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned int i = 0;
	int check1 = 0, check2 = 0;
	while (i < k1.length() && i < k2.length())
	{
		if (k1[i] == k2[i])
			i++;
		else
		{
			for (unsigned int k = 0; k < alf.length(); k++)
			{
				if (k1[i] == alf[k] )//|| k1[i] == ALF[k])
				{
					check1 = k + 1;
					break;
				}
				if (k2[i] == alf[k] )//|| k2[i] == ALF[k])
				{
					check2 = k + 1;
					break;
				}
			}
			if (check1 > 0) //раньше встретилась первая строка
				return -1;
			if (check2 > 0)
				return 1;
		}
	}
	if (i == k1.length())
		if (i == k2.length())
			return 0;
		else
			return -1;
	else
		return 1;
}