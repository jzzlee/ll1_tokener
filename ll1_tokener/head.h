#pragma once
#include <string>
#include <vector>
#include <ostream>


class Token {
public:
	Token() = default;
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
	virtual ~Lexer();

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


class Parser {
public:
	Parser(Lexer &input);
	virtual ~Parser();
	virtual void element() = 0;
	virtual void elements() = 0;
	virtual void list() = 0;
	virtual void match(int x) = 0;
	virtual void consume() = 0;

protected:
	Lexer &input;
	Token lookahead;
};


class ListParser : public Parser {
public:
	ListParser(Lexer &input);

	void element() override;
	void elements() override;
	void list() override;
	void match(int x) override;
	void consume() override;
};