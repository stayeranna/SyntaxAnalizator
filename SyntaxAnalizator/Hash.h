#pragma once
#include"Token.h"
#include<fstream>
using std::ofstream;
class Hash {
public:
	const int n = 1e5 + 3;
	Token* table = nullptr;
	Hash();
	void insert(const Token& t);
	~Hash();
	void print(ofstream& out);
};