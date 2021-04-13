#include "hash_table_on_lists.h"

hash_table_on_lists::~hash_table_on_lists()
{
	for (int i = 0; i < 1000; i++)
	{
		while (Tab[i] != nullptr)
		{
			link_t* p = Tab[i];
			Tab[i] = p->pNext;
			delete p;
		}
	}
}
Data* hash_table_on_lists::Find(const string& key)
{
	int hash = HashIt(key);

	if (Tab[hash] == nullptr)
		return nullptr;
	else
	{
		link_t* p = Tab[hash];

		while (p != nullptr)
		{
			if (p->data.key == key)
				return &p->data;
			p = p->pNext;
		}
	}
	return nullptr;
}
void hash_table_on_lists::Insert(const Data& data)
{
	if (Find(data.key) != nullptr)
		throw 3;
	int hash = HashIt(data.key);
	link_t* p = new link_t;
	p->pNext = nullptr;
	p->data = data;
	if (Tab[hash] == nullptr)
	{
		Tab[hash] = p;
		return;
	}
	else
	{
		link_t* pp = Tab[hash];
		while (pp->pNext != nullptr)
			pp = pp->pNext;
		pp->pNext = p;
		
		return;
	}
}
void hash_table_on_lists::Delete(const string& key)
{
	if (Find(key) == nullptr)
		throw 2;

	int hash = HashIt(key);
	link_t* p = Tab[hash];
	
	link_t* pp = p;
	if (p->data.key == key)//первый
	{
		pp = p->pNext;
		delete p;
		Tab[hash] = pp;
		p = pp;

		return;
	}
	p = p->pNext;
	while (p->data.key != key)
	{
		if (p->data.key == key)
		{
			while (pp->pNext != p)
				pp = pp->pNext;
			pp->pNext = p->pNext;
			delete p;
			p = pp;

			return;
		}
		p = p->pNext;
	}
}
void hash_table_on_lists::Print()
{
	int k = 0;
	link_t* p;
	std::cout << "\tPRINTING HASH TABLE" << std::endl;
	for (int i = 0; i < 1000; i++)
	{
		p = Tab[i];
		while (p != nullptr)
		{
			cout << p->data.key << ":\t" << p->data.Poly;
			p = p->pNext;
			k++;
		}
	}
	if (k == 0)
		cout << "Empty" << endl;
}
