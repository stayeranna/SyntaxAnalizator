#include"Hash.h"
#include"Lexer.h"
#include"Parser.h"
#include"Node.h"
using std::ofstream;
int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	Hash table;
	Lexer lexer;
	vector<Token> ter;
	string s = lexer.getLexem(in);
	while (s != "")
	{
		string type = lexer.getType(s);
		if (type == "error")
		{
			out << "Lex error: " << s << '\n';
			in.close();
			out.close();
			return 0;
		}
		else
		{
			table.insert(Token(type, s));
		}
		ter.push_back(Token(type, s));
		s = lexer.getLexem(in);
	}
	Parser parser(ter);
	pair<bool, pair<int, string>> result = parser.detected();
	if (result.first == false)
	{
		out << "Syntax error:\n";
		if (result.second.second == "endline")
		{
			out << "position " << result.second.first << " extra words\n";
			in.close();
			out.close();
			return 0;
		}
		out << "position " << result.second.first << '\n' << "expected words to desribe " << result.second.second << '\n';
		in.close();
		out.close();
		return 0;
	}
	Node root = parser.makeTree();
	root.print(out, 0);
	in.close();
	out.close();
}