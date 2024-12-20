#include"token.h"
bool operator==(const Token& a, const Token& b)
{
	if (a.type == b.type && a.lexem == b.lexem)
	{
		return true;
	}
	return false;
}

int Token::getHash() const
{
	int p = 18931;
	int mod = 1e5 + 3;
	long long val = 0;
	long long st = p;
	for (size_t i = 0; i < type.size(); ++i)
	{
		val += st * type[i] % mod;
		val %= mod;
		st *= p;
		st %= mod;
	}
	for (size_t i = 0; i < lexem.size(); ++i)
	{
		val += st * lexem[i] % mod;
		val %= mod;
		st *= p;
		st %= mod;
	}
	return val;
}
