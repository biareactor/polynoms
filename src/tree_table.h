#ifndef __TABLE_TREE_H__
#define __TABLE_TREE_H__

#include "base_table.h"

using namespace std;

struct TreeLink
{
	Data d;
	int diff;
	TreeLink* pRight;
	TreeLink* pLeft;
	TreeLink* pParent;
};

class TableTree : public BaseTable
{
	TreeLink* pRoot;
	void balance(int& a, int& b, int p);
	void rotateLeft(TreeLink* a);
	void rotateRight(TreeLink* a);
	void rotateBigLeft(TreeLink* a);
	void rotateBigRight(TreeLink* a);
	void changeBalance(TreeLink* p, int a);
	void TempPrint(TreeLink* p)
	{
		if (p != nullptr)
		{
			TempPrint(p->pLeft);
			std::cout << p->d.key << ":\t" << p->d.PolyString << std::endl;
			TempPrint(p->pRight);
		}
	}
public:
	TableTree() :BaseTable()
	{
		pRoot = nullptr;
	}
	void Insert(const Data& d);
	Data* Find(const string& key);
	void Delete(const string& key);
	void Print()
	{
		std::cout << "\tPRINTING AVL TREE" << std::endl;
		TreeLink* p = pRoot;
		TempPrint(p);
		if (pRoot == nullptr)
			cout << "Empty" << endl;
	}
	void TempDelete(TreeLink* p)
	{
		if (p != nullptr)
		{
			TempDelete(p->pLeft);
			TempDelete(p->pRight);
			delete p;
		}
	}
	~TableTree()
	{
		TempDelete(pRoot);
	}
};
#endif
