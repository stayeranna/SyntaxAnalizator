#include "Node.h"
using std::to_string;

void Node::print(ofstream& out, int level)
{
	for (int i = 0; i < level; ++i)
	{
		out << "   ";
	}
	out << data << '\n';
	for (int i = 0; i < children.size(); ++i)
	{
		children[i].print(out, level + 1);
	}
}

void Node::getTr()
{
	for (int i = 0; i < children.size(); ++i)
	{
		children[i].getTr();
	}
	if (children.size() == 0)
	{
		if (data == "id_name" || data == "int_num" || data == "real_num")
		{
			tr = list;
		}
		else if (data == "INTEGER" || data == "REAL")
		{
			tr = data;
		}
	}
	else if (children.size() == 1)
	{
		tr = children[0].tr;
		if (data == "VarList")
		{
			count = 1;
		}
	}
	else
	{
		if (data == "Procedure")
		{
			tr = children[0].tr + " " + children[1].tr + " MAIN";
		}
		else if (data == "Begin")
		{
			tr = children[0].tr;
		}
		else if (data == "Descriptions")
		{
			tr = children[1].tr + " " + to_string(children[1].count) + " DESCR";
		}
		else if (data == "DescrList")
		{
			if (children[0].data == "E1")
			{
				count = 1;
				tr = children[0].tr + " " + children[1].tr + " " + to_string(children[0].count + 1) + " DECL";
			}
			else
			{
				count = children[1].count + 1;
				tr = children[0].tr + " " + children[1].tr;
			}
		}
		else if (data == "Descr")
		{
			tr = children[0].tr + " " + children[1].tr + " " + to_string(children[0].count + 1) + " DECL";
		}
		else if (data == "VarList")
		{
			count = children[1].count + 1;
			tr = children[0].tr + " " + children[1].tr;
		}
		else if (data == "Operators")
		{
			if (children[0].data == "I1")
			{
				count = 1;
				tr = children[0].tr + " " + children[1].tr + " ASSIGN";
			}
			else
			{
				count = children[1].count + 1;
				tr = children[0].tr + " " + children[1].tr;
			}
		}
		else if (data == "Op")
		{
			tr = children[0].tr + " " + children[1].tr + " ASSIGN";
		}
		else if (data == "Expr")
		{
			tr = children[0].tr;
			if (children[0].data != "K6")
			{
				tr += " " + children[1].tr + " ";
			}
			if (children[0].data == "K1")
			{
				tr += "*";
			}
			else if (children[0].data == "K2")
			{
				tr += "div";
			}
			else if (children[0].data == "K3")
			{
				tr += "mod";
			}
			else if (children[0].data == "K4")
			{
				tr += "+";
			}
			else if (children[0].data == "K5")
			{
				tr += "-";
			}
		}
		else if (data == "Term")
		{
			tr = children[0].tr;
			if (children[0].data != "K6")
			{
				tr += " " + children[1].tr + " ";
			}
			if (children[0].data == "K1")
			{
				tr += "*";
			}
			else if (children[0].data == "K2")
			{
				tr += "div";
			}
			else if (children[0].data == "K3")
			{
				tr += "mod";
			}
		}
		else if (data == "SimpleExpr")
		{
			tr = children[0].tr;
		}
		else if (data == "S1")
		{
			tr = children[0].tr + " " + children[1].tr;
		}
		else if (data == "S2")
		{
			tr = children[0].tr + " " + to_string(children[0].count) + " OPERATORS";
		}
		else if (data == "A1")
		{
			tr = children[1].tr;
		}
		else if (data == "E1")
		{
			count = children[0].count;
			tr = children[0].tr;
		}
		else if (data == "E2")
		{
			tr = children[0].tr;
		}
		else if (data == "G1")
		{
			tr = children[0].tr;
		}
		else if (data == "I1")
		{
			tr = children[0].tr;
		}
		else if (data == "I2")
		{
			tr = children[0].tr;
		}
		else if (data == "K1")
		{
			tr = children[0].tr;
		}
		else if (data == "K2")
		{
			tr = children[0].tr;
		}
		else if (data == "K3")
		{
			tr = children[0].tr;
		}
		else if (data == "K4")
		{
			tr = children[0].tr;
		}
		else if (data == "K5")
		{
			tr = children[0].tr;
		}
		else if (data == "K6")
		{
			tr = children[1].tr;
		}
	}
}

void Node::getVars(map<string, string>& vars, vector<string>& errors)
{
	if (data == "Procedure")
	{
		children[0].getVars(vars, errors);
		return;
	}
	if (data == "S1")
	{
		children[1].getVars(vars, errors);
		return;
	}
	if (data == "Descriptions")
	{
		children[1].getVars(vars, errors);
		return;
	}
	if (children[0].data == "Descr")
	{
		children[0].getVars(vars, errors);
		children[1].getVars(vars, errors);
		return;
	}
	Lexer lexer;
	string res = "";
	vector<pair<string, string>> Types;
	for (int i = 0; i < tr.size(); ++i)
	{
		if (tr[i] == ' ')
		{
			Types.push_back({ res, lexer.getType(res) });
			res = "";
		}
		else
		{
			res += tr[i];
		}
	}
	string type = "";
	for (int i = 0; i < Types.size(); ++i)
	{
		if (Types[i].second == "keyword")
		{
			if (Types[i].first == "INTEGER")
			{
				type = "int";
			}
			else
			{
				type = "real";
			}
		}
	}
	vector<string> names;
	for (int i = 0; i < Types.size(); ++i)
	{
		if (Types[i].second == "id_name")
		{
			names.push_back(Types[i].first);
		}
	}
	for (int i = 0; i < names.size(); ++i)
	{
		if (vars.find(names[i]) == vars.end())
		{
			vars[names[i]] = type;
		}
		else
		{
			errors.push_back(names[i] + ": redeclaration");
		}
	}
}

void Node::getTypes(map<string, string>& vars, vector<string>& errors)
{
	if (data == "S1")
	{
		return;
	}
	for (int i = 0; i < children.size(); ++i)
	{
		children[i].getTypes(vars, errors);
	}
	if (children.size() == 0)
	{
		if (data == "int_num")
		{
			type = "int";
		}
		else if (data == "real_num")
		{
			type = "real";
		}
		else if (data == "id_name")
		{
			if (vars.count(tr))
			{
				type = vars[tr];
			}
			else
			{
				type = "int";
				errors.push_back(tr + ": was not declared");
			}
		}
		return;
	}
	if (children.size() == 1)
	{
		type = children[0].type;
		return;
	}
	if (data == "Operators")
	{
		if (children[0].data == "I1")
		{
			if (children[0].type != children[1].type)
			{
				errors.push_back("different types: " + children[0].tr + " is " + children[0].type + ", " + children[1].tr + " is " + children[1].type);
			}
		}
	}
	else if (data == "Op")
	{
		if (children[0].type != children[1].type)
		{
			errors.push_back("different types: " + children[0].tr + " is " + children[0].type + ", " + children[1].tr + " is " + children[1].type);
		}
	}
	else if (data == "Expr")
	{
		type = children[0].type;
		if (children[0].data != "K6" && children[0].type != children[1].type)
		{
			errors.push_back("different types: " + children[0].tr + " is " + children[0].type + ", " + children[1].tr + " is " + children[1].type);
		}
		if (children[0].data == "K3")
		{
			if (children[1].type == "real")
			{
				errors.push_back("operator mod is not for real expressions, " + children[1].tr + " is real");
			}
		}
		if (children[0].data == "K2")
		{
			if (children[1].type == "real")
			{
				errors.push_back("operator div is not for real expressions, " + children[1].tr + " is real");
			}
		}
	}
	else if (data == "Term")
	{
		type = children[0].type;
		if (children[0].data != "K6" && children[0].type != children[1].type)
		{
			errors.push_back("different types: " + children[0].tr + " is " + children[0].type + ", " + children[1].tr + " is " + children[1].type);
		}
		if (children[0].data == "K3")
		{
			if (children[1].type == "real")
			{
				errors.push_back("operator mod is not for real expressions, " + children[1].tr + " is real");
			}
		}
		if (children[0].data == "K2")
		{
			if (children[1].type == "real")
			{
				errors.push_back("operator div is not for real expressions, " + children[1].tr + " is real");
			}
		}
	}
	else if (data == "I1" || data == "I2")
	{
		type = children[0].type;
	}
	else if (data == "K1")
	{
		type = children[0].type;
	}
	else if (data == "K2")
	{
		type = children[0].type;
		if (children[0].type == "real")
		{
			errors.push_back("operator div is not for real expressions, " + children[0].tr + " is real");
		}

	}
	else if (data == "K3")
	{
		type = children[0].type;
		if (children[0].type == "real")
		{
			errors.push_back("operator mod is not for real expressions, " + children[0].tr + " is real");
		}
	}
	else if (data == "K4")
	{
		type = children[0].type;
	}
	else if (data == "K5")
	{
		type = children[0].type;
	}
	else if (data == "K6")
	{
		type = children[1].type;
	}
	else if (data == "SimpleExpr")
	{
		type = children[0].type;
	}
}
