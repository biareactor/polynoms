#include "list.h"

template<typename T>
List<T>::List() : Head(nullptr), Amount(0)
{
}

template<typename T>
List<T>::List(const List<T>& listOut)
{
	Amount = 0;
	Head = nullptr;

	if (listOut.Head != nullptr)
	{
		Node<T>* p = listOut.Head;

		push_back(p->inner);

		while (p->pNext != nullptr)
		{
			p = p->pNext;
			push_back(p->inner);
		}
	}
}

template<typename T>
List<T>::~List()
{
	if (Head != nullptr)
	{
		while (Head->pNext != nullptr)
		{
			Node<T>* p = Head;
			Head = Head->pNext;
			delete p;
			Amount--;
		}

		Node<T>* p = Head;
		delete p;

		Amount--;

		if (Amount != 0) throw std::exception("smth goes wrong");
	}
}

template<typename T>
void List<T>::push_back(const T& val)
{
	if (Head == nullptr)
	{
		Head = new Node<T>;
		Head->inner = val;
		Amount++;
	}
	else
	{
		Node<T>* p = Head;

		while (p->pNext != nullptr)
			p = p->pNext;

		p->pNext = new Node<T>;
		p->pNext->inner = val;

		Amount++;
	}
}

template<typename T>
void List<T>::pop_front()
{
	if (Head != nullptr)
	{
		Node<T>* p = Head;
		if (Head->pNext != nullptr)
			Head = Head->pNext;
		else
			Head = nullptr;
		delete p;
		Amount--;
	}
	else
		throw std::exception("void");
}

template<typename T>
T& List<T>::operator[](const int ind)
{
	if ((ind < 0) || (ind > Amount - 1))
		throw std::exception("Wrong ind");

	int i = 0;
	Node<T>* p = Head;

	if (ind == 0)
		return p->inner;

	while ((p->pNext != nullptr) && (i != ind))
	{
		p = p->pNext;
		i++;
	}

	return p->inner;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& listOut)
{
	if (this != &listOut)
	{
		// удаляем нынешний список
		while (Head != nullptr)
		{
			pop_front();
		}

		// берём голову копируемого списка
		Node<T>* p = listOut.Head;

		if (p != nullptr)
		{
			push_back(p->inner);

			while (p->pNext != nullptr)
			{
				p = p->pNext;
				push_back(p->inner);
			}
		}
	}

	return *this;
}

template<typename T>
bool List<T>::operator==(const List<T>& listOut) const
{
	if (Amount != listOut.Amount)
		return false;

	if ((Head != nullptr) && (listOut.Head != nullptr))
	{
		Node<T>* p1 = Head;
		Node<T>* p2 = listOut.Head;

		if (p1->inner != p2->inner)
			return false;

		while ((p1->pNext != nullptr) && (p2->pNext != nullptr))
		{
			p1 = p1->pNext;
			p2 = p2->pNext;
			if (p1->inner != p2->inner)
				return false;
		}
		return true;
	}
	return true;
}

template<typename T>
bool List<T>::operator!=(const List<T>& listOut) const
{
	return !(*this == listOut);
}

template<typename T>
Node<T>* List<T>::DelELem(Node<T>* p)
{
	if (p == Head)
	{
		if (p->pNext != nullptr)
		{
			Head = p->pNext;
			delete p;
			Amount--;
			return Head;
		}
		else
		{
			delete p;
			Amount--;
			return nullptr;
		}
	}

	Node<T>* cur = Head;

	while (cur->pNext != p)
		cur = cur->pNext;

	if (p->pNext != nullptr)
	{
		cur->pNext = p->pNext;
		delete p;
		Amount--;
		return cur;
	}
	else
	{
		cur->pNext = nullptr;
		delete p;
		Amount--;
		return cur;
	}
}

template<typename T>
void List<T>::Sort()
{
	if (Head == nullptr) return;						// у пустого списка нечего сортировать
	if (Head->pNext == nullptr) return;					// у списка из одного элемента нечего сортировать

	for (int i = 1; i < Amount; i++)
	{
		Node<T>* Current = FindElem(i);
		int j = i - 1;

		while ((j > -1) && (Current->inner < this->operator[](j)))
		{
			Node<T>* tmp, * p, * pp, * pr;

			if (j > 0)
			{
				p = FindElem(j);
				pr = FindElem(j - 1);
				pp = Current;

				pr->pNext = pp;
				tmp = pp->pNext;
				pp->pNext = p;
				p->pNext = tmp;

				j--;
			}
			else
			{
				p = FindElem(j);
				pp = Current;

				tmp = pp->pNext;
				pp->pNext = p;
				p->pNext = tmp;

				j--;
			}
		}

		if (Current->inner < Head->inner)
			Head = Current;
	}
}