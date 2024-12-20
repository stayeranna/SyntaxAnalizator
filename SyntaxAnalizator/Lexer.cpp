#include "Lexer.h"

int Lexer::getState(const string& s) const
{
	int pos = 0;
	int currentState = 0;
	while (pos < s.size())
	{
		int ind = 0;
		while (ind < alphabet.size() && s[pos] != alphabet[ind])
		{
			++ind;
		}
		if (ind == alphabet.size())
		{
			return -1;
		}
		if (transitFunction[currentState][ind] == -1)
		{
			return -1;
		}
		currentState = transitFunction[currentState][ind];
		++pos;
	}
	if (isFinal[currentState])
	{
		return currentState;
	}
	return -1;
}

string Lexer::getType(const string& s) const
{
	int state = getState(s);
	if (state == -1)
	{
		return "error";
	}
	if (state == 49 || state == 41 || state == 33 || state == 45 || state == 36 || state == 52)
	{
		return "keyword";
	}
	if (state == 12 || state == 13 || state == 19)
	{
		return "separator";
	}
	if (state == 35 || state == 37 || state == 29 || state == 14 || state == 15 || state == 16 || state == 17 || state == 18)
	{
		return "operator";
	}
	if (state == 10 || state == 11)
	{
		return "int_num";
	}
	if (state == 39)
	{
		return "real_num";
	}
	return "id_name";
}

string Lexer::getLexem(ifstream& in)
{
	string res = "";
	char c = in.get();
	while (c != EOF && c != '\n' && c != ' ' && c != '\0')
	{
		res += c;
		c = in.get();
	}
	return res;
}

