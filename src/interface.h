//#pragma once

#ifndef __INTERFACR_H__
#define __INTERFACE_H__

#include "linear_table.h"
#include "tree_table.h"
#include "hash_table_linear.h"
#include "hash_table_on_lists.h"
#include "ordered_line_table.h"
#include "linear_table_on_lists.h"
#include <conio.h>
#include "postfix.h"

class Interface
{
	BaseTable* Base;
	int inputControl(string left_board, string right_board, void (*print)(const string&), const string& str);
	void exceptionHandling(int code);
	string controlKey(const string& key);
	string controlPolynom(const string& str);
	void tableSelection();
	void Add();
	void Print();
	void Search();
	void changePolynom(Data* d);
	void countPolynom(Data* d);
	void Integral(Data* d, int code);
	void Calculate();
	void calPol();
	void calPolPoint();
	void Delete();
	bool isCorrect(string str);
public:
	Interface()
	{
		Base = nullptr;
	}
	void Menu();
};

void printTableList(const string& str);
void printMenuList(const string& str);
void printPolynomOperation(const string& str);
void printExit(const string& str);
void printCalculate(const string& str);
void keyRules();
#endif