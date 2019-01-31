// Simple Calculator Interpreter

#include <iostream>
#include <string>
#include "calc1.h"

using namespace std;

// Interpreter class constructor
Interpreter::Interpreter(string input)
{
	text = input;
	pos = 0;
	current_char = text[pos];
	current_token = get_next_token();
}

// Advance the 'pos' pointer and 
// set the 'current_char' variable
void Interpreter::advance()
{
	pos++;
	if (pos > text.length() - 1)
	{
		current_char = '\0';
	}
	else
	{
		current_char = text[pos];
	}
}

void Interpreter::skip_whitespace()
{
	while (current_char != '\0' && isspace(current_char))
	{
		cout << "Skipping..." << endl;
		advance();
	}
}

// Return a (multidigit) integer from this.text at this.pos
// as a string
string Interpreter::integer()
{
	string result = "";
	while (current_char != '\0' && isdigit(current_char))
	{
		result += current_char;
		advance();
	}
	return result;
}

// Lexical Analyzer
// Responsible for breaking a sentence apart
// into tokens. One token at a time.
Token *Interpreter::get_next_token()
{
	while (current_char != '\0')
	{
		if (isspace(current_char))
		{
			cout << "Noticed whitespace" << endl;
			skip_whitespace();
			continue;
		}
		if (isdigit(current_char))
		{
			Token *int_token = new Token;
			int_token->type = INTEGER;
			int_token->value = integer();
			return int_token;
		}
		if (current_char == '+')
		{
			advance();
			Token *plus_token = new Token;
			plus_token->type = PLUS;
			plus_token->value = "+";
			return plus_token;
		}
		if (current_char == '-')
		{
			advance();
			Token *minus_token = new Token;
			minus_token->type = MINUS;
			minus_token->value = "-";
			return minus_token;
		}
		throw "Error parsing input.";
	}
	Token *EOF_token = new Token;
	EOF_token->type = EoF;
	EOF_token->value = "";
	return EOF_token;
}

// Compare the current token type with the passed token
// type and if they match then "eat" the current token
// and assign the next token to the self.current_token,
// otherwise raise an exception
void Interpreter::eat(TokenType token_type)
{
	if (current_token->type == token_type)
	{
		current_token = get_next_token();
	}
	else
	{
		throw "Error parsing input.";
	}
}

int Interpreter::expr()
{
	Token *left = current_token;
	eat(INTEGER);

	Token *op = current_token;
	switch (op->type)
	{
		case PLUS: 
			eat(PLUS);
			break;
		case MINUS: 
			eat(MINUS);
			break;
		default: 
			throw "Error parsing input.";
			break;
	}

	Token *right = current_token;
	eat(INTEGER);

	int result;
	switch (op->type)
	{
		case PLUS:
			result = stoi(left->value) + stoi(right->value);
			delete left;
			delete right;
			delete op;
			break;
		case MINUS: 
			result = stoi(left->value) - stoi(right->value);
			delete left;
			delete right;
			delete op;
			break;
		default: 
			throw "Something really bad happened.";
			break;
	}
	return result;
}






