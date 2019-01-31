#ifndef CALC1_H
#define CALC1_H

#include <string>

enum TokenType
{
	INTEGER, PLUS, MINUS, EoF
};

typedef struct Token Token;
struct Token
{
	TokenType type;
	std::string value;
};

class Interpreter
{
	private:
		Token *current_token;
		std::string text;
		char current_char;
		size_t pos;
		void advance();
		void skip_whitespace();
		std::string integer();
		Token *get_next_token();
		void eat(TokenType token_type);
	public:
		Interpreter(std::string text);
		int expr();
};

#endif