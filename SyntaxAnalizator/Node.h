#pragma once
#include<fstream>
#include<vector>
#include<string>;
using std::ofstream;
using std::string;
using std::vector;
class Node {
public:
	string data;
	vector<Node> children;
	Node(string s) : data(s) {}
	void print(ofstream& out, int level);
};