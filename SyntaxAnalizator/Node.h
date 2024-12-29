#pragma once
#include<fstream>
#include<vector>
#include<string>;
#include<map>
#include"Lexer.h"
using std::ofstream;
using std::string;
using std::vector;
using std::map;
using std::pair;
class Node {
public:
	string data;
	string type = "";
	int count = 0;
	string tr = "";
	string list;
	vector<Node> children;
	Node(string s) : data(s) {}
	void print(ofstream& out, int level);
	void getTr();
	void getVars(map<string, string>& vars, vector<string>& errors);
	void getTypes(map<string, string>& vars, vector<string>& errors);
};