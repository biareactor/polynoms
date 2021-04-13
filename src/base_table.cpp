#include "base_table.h"

int HashIt(std::string key)
{
	int Hash = 0;

	for (unsigned int i = 0; i < key.size(); i++)
		Hash += (int)key[i];

	Hash *= key.size();
	return Hash % 1000;
}