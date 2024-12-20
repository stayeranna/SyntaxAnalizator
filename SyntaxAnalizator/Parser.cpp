#include "Parser.h"

string Parser::get_term(Token& a)
{
	if (a.type == "int_num" || a.type == "real_num" || a.type == "id_name")
	{
		return a.type;
	}
	return a.lexem;
}
Parser::Parser(vector<Token>& a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		Str.push_back(get_term(a[i]));
	}
}

vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>> Parser::getTable()
{
	int n = Str.size();
	vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>> A(n + 1, vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>(n));
	for (int i = 0; i < n; ++i)
	{
		for (auto j : RulesTerms[Terms[Str[i]]])
		{
			A[1][i][j] = { {Terms[Str[i]], {0, i}}, {-1, {-1, -1}} };
		}
	}
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 0; j <= n - i; ++j)
		{
			for (int k = i - 1; k >= 1; --k)
			{
				for (auto t1 : A[k][j])
				{
					for (auto t2 : A[i - k][j + k])
					{
						if (RulesNeterms.count({ t1.first, t2.first }))
						{
							for (auto p : RulesNeterms[{t1.first, t2.first}])
							{
								A[i][j][p] = { {t1.first, {k, j}}, {t2.first, {i - k, j + k}} };
							}
						}
					}
				}
			}
		}
	}
	return A;
}

pair<bool, pair<int, string>> Parser::detected()
{
	int n = Str.size();
	vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>> A = getTable();
	for (auto i : A[n][0])
	{
		if (i.first == 0)
		{
			pair<int, string> p;
			return { true, p };
		}
	}
	vector<string> proc = { "Begin", "Descriptions", "Operators", "End" };
	vector<int> prNum = { 1, 4, 9, 2 };
	int num = 0;
	int u = 0;
	while (num < n && u < 4)
	{
		bool f = true;
		for (int j = n - num; j >= 1 && f; --j)
		{
			for (auto el : A[j][num])
			{
				if (el.first == prNum[u] && f)
				{
					f = false;
					++u;
					num += j;
				}
			}
		}
		if (f)
		{
			return { false, {num, proc[u]} };
		}
	}
	if (u == 4)
	{
		return { false, {num, "endline"} };
	}
	return { false, {num, proc[u]} };
}

void Parser::getChildren(Node& node, pair<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>> p, vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>>& A)
{
	if (p.second.second.first == -1)
	{
		node.children.push_back(Node(trTerms[p.second.first.first]));
		return;
	}
	pair<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>> p1 = *A[p.second.first.second.first][p.second.first.second.second].find(p.second.first.first);
	Node c(trNeterms[p.second.first.first]);
	getChildren(c, p1, A);
	node.children.push_back(c);
	p1 = *A[p.second.second.second.first][p.second.second.second.second].find(p.second.second.first);
	Node d(trNeterms[p.second.second.first]);
	getChildren(d, p1, A);
	node.children.push_back(d);
}

Node Parser::makeTree()
{
	vector<vector<map<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>>>> A = getTable();
	int n = Str.size();
	pair<int, pair<pair<int, pair<int, int>>, pair<int, pair<int, int>>>> p = *A[n][0].find(0);
	Node root(trNeterms[p.first]);
	getChildren(root, p, A);
	return root;
}
