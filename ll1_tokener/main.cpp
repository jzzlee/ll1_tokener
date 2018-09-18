#include "head.h"
#include <iostream>
#include <cstdio>


int main()
{
	std::string s;
	std::cout << "enter a line of code:";
	std::getline(std::cin, s);


	auto lexer = ListLexer(s);
	//auto t = lexer.nextToken();
	//while (t.getType() != ListLexer::LEOF_TYPE)
	//{
	//	const std::string &s = t.toString();
	//	std::cout << s << std::endl;
	//	t = lexer.nextToken();
	//}
	//std::cout << t.toString() << std::endl;

	auto parser = ListParser(lexer);
	parser.list();

	system("pause");

	return 0;
}
