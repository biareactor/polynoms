//#pragma once

#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>

template<typename T>
class Node
{
public:
	T inner;
	Node* pNext;

	Node() : pNext(nullptr)
	{
	}

	~Node()
	{
		if (pNext) pNext = nullptr;
	}
};

template<typename T>
class List
{
	Node<T>* Head;
	int Amount;
public:
	List();
	List(const List<T>& listOut);
	~List();

	void push_back(const T& val);
	void pop_front();

	T& operator[](const int ind);
	int GetAmount() { return Amount; }
	void SetAmount(const int& nA) { Amount = nA; }
	Node<T>* GetHead() { return Head; }

	// возвращает адрес элемента по индексу
	Node<T>* FindElem(const int& ind)
	{
		if ((ind < 0) || (ind > Amount - 1))
			throw std::exception("Wrong ind");

		int i = 0;
		Node<T>* p = Head;

		if (p != nullptr)
		{
			if (ind == 0)
				return p;

			while ((p->pNext != nullptr) && (i != ind))
			{
				p = p->pNext;
				i++;
			}
		}
		return p;
	}

	List<T>& operator=(const List<T>& listOut);
	bool operator==(const List<T>& listOut) const;
	bool operator!=(const List<T>& listOut) const;
	Node<T>* DelELem(Node<T>* p);

	void Sort();
};

#endif