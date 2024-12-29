#pragma once
#include"Lexer.h"
#include"Token.h"
#include"Node.h"
#include<map>
#include<set>
using std::set;
using std::map;
using std::pair;
class Parser {
	map<string, int> Terms = { {"INTEGER", 0}, {"REAL", 1}, {"VAR", 2}, {"begin", 3}, {"end", 4}, {"procedure", 5}, {";", 6}, {":", 7}, {",", 8}, {"div", 9}, {"mod", 10}, {":=", 11}, {"+", 12}, {"-", 13}, {"*", 14}, {"(", 15}, {")", 16}, {"int_num", 17}, {"real_num", 18}, {"id_name", 19} };
	map<string, int> Neterms = { {"Procedure", 0}, {"Begin", 1}, {"End", 2}, {"ProcedureName", 3}, {"Descriptions", 4}, {"DescrList", 5}, {"Descr", 6}, {"VarList", 7}, {"Type", 8}, {"Operators", 9}, {"Op", 10}, {"Expr", 11}, {"Term", 12}, {"SimpleExpr", 13}, {"Id", 14}, {"Const", 15}, {"S1", 16}, {"S2", 17}, {"A1", 18}, {"A2", 19}, {"E1", 20}, {"E2", 21}, {"G1", 22}, {"I1", 23}, {"I2", 24}, {"K1", 25}, {"K2", 26}, {"K3", 27}, {"K4", 28}, {"K5", 29}, {"K6", 30}, {"Tprocedure", 31}, {"TVAR", 32}, {"T:", 33}, {"T:=", 34}, {"T*", 35}, {"Tdiv", 36}, {"Tmod", 37}, {"T+", 38}, {"T-", 39}, {"T(", 40}, {"T)", 41}, {"T;", 42}, {"Tbegin", 43}, {"T,", 44} };
	vector<set<int>> RulesTerms = { {8}, {8}, {32}, {43}, {2}, {31}, {42}, {33}, {44}, {36}, {37}, {34}, {38}, {39}, {35}, {40}, {41}, {11, 12, 13, 15}, {11, 12, 13, 15}, {3, 7, 11, 12, 13, 14} };
	map<pair<int, int>, set<int>> RulesNeterms = { { { 1, 4 }, { 16 } }, { { 6, 5 }, { 5 } }, { { 7, 33 }, { 20 } }, { { 8, 42 }, { 21 } }, { { 9, 2 }, { 17 } }, { { 10, 9 }, { 9 } }, { { 11, 42 }, { 24 } }, { { 12, 38 }, { 28 } }, { { 12, 39 }, { 29 } }, { { 13, 35 }, { 25 } }, { { 13, 36 }, { 26 } }, { { 13, 37 }, { 27 } }, { { 14, 34 }, { 23 } }, { { 14, 44 }, { 22 } }, { { 16, 17 }, { 0 } }, { { 18, 19 }, { 1 } }, { { 20, 21 }, { 5, 6 } }, { { 22, 7 }, { 7 } }, { { 23, 24 }, { 9, 10 } }, { { 25, 12 }, { 11, 12 } }, { { 26, 12 }, { 11, 12 } }, { { 27, 12 }, { 11, 12 } }, { { 28, 11 }, { 11 } }, { { 29, 11 }, { 11 } }, { { 30, 41 }, { 11, 12, 13 } }, { { 31, 3 }, { 18 } }, { { 32, 5 }, { 4 } }, { { 40, 11 }, { 30 } }, { { 42, 43 }, { 19 } } };
	vector<string> trTerms = { "INTEGER", "REAL", "VAR", "begin", "end", "procedure", ";", ":", ",", "div", "mod", ":=", "+", "-", "*", "(", ")", "int_num", "real_num", "id_name" };
	vector<string> trNeterms = { "Procedure", "Begin", "End", "ProcedureName", "Descriptions", "DescrList", "Descr", "VarList", "Type", "Operators", "Op", "Expr", "Term", "SimpleExpr", "Id", "Const", "S1", "S2", "A1", "A2", "E1", "E2", "G1", "I1", "I2", "K1", "K2", "K3", "K4", "K5", "K6", "Tprocedure", "TVAR", "T:", "T:=", "T*", "Tdiv", "Tmod", "T+", "T-", "T(", "T)", "T;", "Tbegin", "T," };
	vector<string> Str;
	string get_term(Token& a);
	vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>> getTable();
	void getChildren(Node& node, pair<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>> p, vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>>& A, vector<Token>& ter, int& number);
public:
	Parser(vector<Token>& a);
	pair<bool, pair<int, string>> detected();
	Node makeTree(vector<Token>& ter);
};