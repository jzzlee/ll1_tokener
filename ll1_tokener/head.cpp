#include "head.h"
#include <cassert>
#include <iostream>


Token::Token(int type, const std::string &text) :
	type(type), text(text) { }

std::string Token::toString() const
{
	std::string tname = ListLexer::getTokenName(type);
	auto s = std::string("<'" + text + "', " + tname + ">");
	return s;
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
		c = input[p];
	else
		c = LEOF;
}

void Lexer::match(char x)
{
	assert(c == x);
	consume();
}

Lexer::~Lexer() { }


const int ListLexer::NAME = 2;
const int ListLexer::COMMA = 3;
const int ListLexer::LBRACK = 4;
const int ListLexer::RBRACK = 5;
const std::vector<std::string> ListLexer::tokenNames = { "n/a", "<EOF>", "NAME", "COMMA", "LBRACK", "RBRACK" };

ListLexer::ListLexer(const std::string &input) :
	Lexer(input) {}

const std::string &ListLexer::getTokenName(int tokenType)
{
	if (tokenType < LEOF || tokenType >= (int)tokenNames.size())
	{
		std::cout << "invalid tokenType: " << tokenType << std::endl;
		return tokenNames[0];
	}
	else
		return tokenNames[tokenType];
}

bool ListLexer::isLetter()
{
	return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

void ListLexer::WS()
{
	while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
		consume();
}

Token ListLexer::Name()
{
	std::string s;
	do {
		s += c;
		consume();
	} while (isLetter());

	return Token(NAME, s);
}

Token ListLexer::nextToken()
{
	while (c != LEOF)
	{
		switch (c)
		{
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			WS();
			continue;
		case ',':
			consume();
			return Token(COMMA, ",");
		case '[':
			consume();
			return Token(LBRACK, "[");
		case ']':
			consume();
			return Token(RBRACK, "]");
		default:
			if (isLetter())
				return Name();
			else
				std::cout << "invalid character: " << c << std::endl;
		}
	}
	return Token(LEOF_TYPE, "<EOF>");
}

Parser::Parser(Lexer &input):
	input(input) {
}

Parser::~Parser() { }

ListParser::ListParser(Lexer &input):
	Parser(input) {
	consume(); 
}

void ListParser::element()
{
	if (lookahead.getType() == ListLexer::NAME)
	{
		match(ListLexer::NAME);
	}
	else if (lookahead.getType() == ListLexer::LBRACK)
	{
		list();
	}
	else
	{
		std::cout << "ListParser get noknown element: " << lookahead.toString() << std::endl;
	}
}

void ListParser::elements()
{
	element();
	while (lookahead.getType() == ListLexer::COMMA) {
		match(ListLexer::COMMA);
		if (lookahead.getType() == ListLexer::NAME)
			element();
		else
			break;
	}
}

void ListParser::list()
{
	match(ListLexer::LBRACK);
	elements();
	match(ListLexer::RBRACK);
}

void ListParser::match(int x)
{
	if (lookahead.getType() == x)
	{
		consume();
	}
	else
	{
		std::cout << "ListParser cannot match " << lookahead.getType() << " with type " << x << std::endl;
	}
}

void ListParser::consume()
{
	lookahead = input.nextToken();
	std::cout << lookahead.toString() << std::endl;
}

