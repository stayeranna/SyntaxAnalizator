#include "Hash.h"

Hash::Hash()
{
	table = new Token[n];
}

void Hash::insert(const Token& t)
{
	int ind = t.getHash();
	while (table[ind].type != "" && (table[ind].type != t.type || table[ind].lexem != t.lexem))
	{
		++ind;
		if (ind == n)
		{
			ind = 0;
		}
	}
	if (table[ind].type == "")
	{
		table[ind] = t;
	}
}

Hash::~Hash()
{
	delete[] table;
}

void Hash::print(ofstream& out)
{
	for (int i = 0; i < n; ++i)
	{
		if (table[i].type != "")
		{
			out << table[i].type << " | " << table[i].lexem << " | " << i << '\n';
		}
	}
}
