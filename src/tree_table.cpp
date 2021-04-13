#include "tree_table.h"

//Если p = 1 - левый малый поворот
//Если p = -1 - правый малый поворот
void TableTree::balance(int& a, int& b, int p)
{
	if (b * p >= 0)
	{
		a = a + p;
		b = b + p;
	}
	else
	{
		a = a - b + p;
		b = a + b + p;
	}
}

void TableTree::rotateLeft(TreeLink* a)
{
	TreeLink* b = a->pRight;
	b->pParent = a->pParent;
	if (a->pParent != nullptr)
	{
		if (a->pParent->pLeft == a)
			a->pParent->pLeft = b;
		else
			a->pParent->pRight = b;
	}
	else pRoot = b;
	a->pRight = b->pLeft;
	a->pParent = b;
	b->pLeft = a;
	if (a->pRight != nullptr)
		a->pRight->pParent = a;
	balance(a->diff, b->diff, 1);
}

void TableTree::rotateRight(TreeLink* a)
{
	TreeLink* b = a->pLeft;
	b->pParent = a->pParent;
	if (a->pParent != nullptr)
	{
		if (a->pParent->pLeft == a)
			a->pParent->pLeft = b;
		else
			a->pParent->pRight = b;
	}
	else pRoot = b;
	a->pLeft = b->pRight;
	a->pParent = b;
	b->pRight = a;
	if (a->pLeft != nullptr)
		a->pLeft->pParent = a;
	balance(a->diff, b->diff, -1);
}

void TableTree::rotateBigLeft(TreeLink* a)
{
	rotateRight(a->pRight);
	rotateLeft(a);
}

void TableTree::rotateBigRight(TreeLink* a)
{
	rotateLeft(a->pLeft);
	rotateRight(a);
}

// а = 0 - для изменения балансов при вставке
// а = 1 - для изменения балансов при удалении
void TableTree::changeBalance(TreeLink* p, int a)
{
	while (p->pParent != nullptr)
	{
		if (p->pParent->pLeft == p)
			p->pParent->diff = p->pParent->diff + 1 - 2 * a;
		if (p->pParent->pRight == p)
			p->pParent->diff = p->pParent->diff - 1 + 2 * a;
		if (p->pParent->diff == -2)
		{
			p = p->pParent->pRight;
			if (p->diff <= 0)
			{
				rotateLeft(p->pParent);
				p = p->pLeft;
			}
			else
			{
				rotateBigLeft(p->pParent);
			}
		}
		if (p->pParent->diff == 2)
		{
			p = p->pParent->pLeft;
			if (p->diff >= 0)
			{
				rotateRight(p->pParent);
				p = p->pRight;
			}
			else
			{
				rotateBigRight(p->pParent);
			}
		}
		if ((p->pParent->diff == a) || (p->pParent->diff == (-1) * a))
			break;
		p = p->pParent;
	}
}

void TableTree::Insert(const Data& _d)
{
	TreeLink* p = pRoot;
	TreeLink* pp = nullptr;
	int flag = 0;
	while (p != nullptr)
	{
		if (p->d.key == _d.key)
			throw 3;
		pp = p;
		if (p->d.key < _d.key)
		{
			p = p->pLeft;
			flag = -1;
		}
		else
		{
			p = p->pRight;
			flag = 1;
		}
	}
	p = new TreeLink;
	if (p == nullptr)
		throw 5;
	p->pRight = nullptr;
	p->pLeft = nullptr;
	if (flag == -1)
		pp->pLeft = p;
	if (flag == 1)
		pp->pRight = p;
	p->pParent = pp;
	p->d = _d;
	p->diff = 0;
	if (pRoot == nullptr)
	{
		pRoot = p;
	}
	changeBalance(p, 0);
}

void TableTree::Delete(const string& key)
{
	if (pRoot == nullptr)
		throw 1;
	TreeLink* p = pRoot;
	TreeLink* pp;
	int flag = 0;
	while (p != nullptr)
	{
		if (p->d.key == key)
			break;
		if (p->d.key < key)
		{
			p = p->pLeft;
			flag = -1;
		}
		else
		{
			p = p->pRight;
			flag = 1;
		}
	}
	if (p != nullptr)
	{
		pp = p;
		if (p->pRight == nullptr)
		{
			if (p->pLeft != nullptr)
			{
				pp = p->pLeft;
				flag = -1;
			}
			Data temp = p->d;
			p->d = pp->d;
			pp->d = temp;
		}
		else
		{
			pp = p->pRight;
			flag = 1;
			while (pp->pLeft != nullptr)
			{
				pp = pp->pLeft;
				flag = -1;
			}
			Data temp = p->d;
			p->d = pp->d;
			pp->d = temp;
			if (pp->pRight != nullptr)
			{
				p = pp;
				pp = pp->pRight;
				flag = 1;
				Data temp = p->d;
				p->d = pp->d;
				pp->d = temp;
			}
		}
		p = pp->pParent;
		delete pp;
		if (flag == 0)
		{
			pRoot = nullptr;
		}
		else
		{
			if (flag == -1)
			{
				p->pLeft = nullptr;
				p->diff--;
				if (p->pRight != nullptr)
				{
					p->diff--;
					p = p->pRight;
				}
			}
			else
			{
				p->pRight = nullptr;
				p->diff++;
				if (p->pLeft != nullptr)
				{
					p->diff++;
					p = p->pLeft;
				}
			}
			changeBalance(p, 1);
		}

	}
	else
		throw 2;
}

Data* TableTree::Find(const string& key)
{
	TreeLink* p = pRoot;
	while (p != nullptr)
	{
		if (p->d.key == key)
		{
			return &(p->d);
		}
		if (p->d.key < key)
		{
			p = p->pLeft;
		}
		else
		{
			p = p->pRight;
		}
	}
	return nullptr;
}