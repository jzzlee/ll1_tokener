#pragma once
#include <string>

class Token;

class Lexer {
public:
	Lexer(const std::string &input);
	void consume();
	void match(char x);
	virtual Token nextToken();
	virtual const std::string &getTokenName(int tokenType);

protected:
	std::string input;
	int p;
	char c;

	static const char LEOF = (char)-1;
	static const int LEOF_TYPE = 1;
};


class Token {
public:
	Token(int type, std::string text);
	const std::string &toString();

private:
	int type;
	std::string text;
};

class ListLexer : public Lexer
{
public:
	ListLexer(const std::string &input);
	bool isLetter();
};