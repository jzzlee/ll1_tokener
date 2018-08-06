#include "head.h"
#include<cassert>

Token::Token(int type, std::string text) :
	type(type), text(text) { }

const std::string & Token::toString()
{

}

const char Lexer::LEOF = (char)-1;
const int Lexer::LEOF_TYPE = 1;

Lexer::Lexer(const std::string &input) :
	input(input)
{
	p = 0;
	c = input[p];
}

void Lexer::consume() 
{
	++p;
	if (p < input.size())
		c = LEOF;
	else
		c = input[p];
}

void Lexer::match(char x)
{
	assert(c == x);
	consume();
}


ListLexer::ListLexer(const std::string &input) :
	Lexer(input) {}

bool ListLexer::isLetter()
{
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

Token ListLexer::nextToken()
{
	    
}