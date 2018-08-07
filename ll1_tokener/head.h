#pragma once
#include <string>
#include <vector>


class Token {
public:
	Token(int type, const std::string &text);
	std::string toString() const;
	int getType() const { return type; }
	const std::string &getText() const { return text; }

private:
	int type;
	std::string text;
};


class Lexer {
public:
	Lexer(const std::string &input);
	void consume();
	void match(char x);
	virtual Token nextToken() = 0;

protected:
	std::string input;
	unsigned p;
	char c;

public:
	static const char LEOF;
	static const int LEOF_TYPE;
};


class ListLexer : public Lexer
{
public:
	ListLexer(const std::string &input);
	bool isLetter();
	void WS();
	Token Name();
	Token nextToken();
	static const std::string &getTokenName(int tokenType);

	static const int NAME;
	static const int COMMA;
	static const int LBRACK;
	static const int RBRACK;
	static const std::vector<std::string> tokenNames;
};