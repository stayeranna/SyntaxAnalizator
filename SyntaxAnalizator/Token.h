#pragma once
#include<string>
using std::string;
class Token {
public:
	string type;
	string lexem;
	Token() = default;
	Token(const string& type, const string& lexem) : type(type), lexem(lexem) {}
	int getHash() const;
};
bool operator==(const Token& a, const Token& b);