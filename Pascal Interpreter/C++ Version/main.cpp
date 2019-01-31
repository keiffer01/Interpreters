#include <iostream>
#include <string>
#include "calc1.h"

using namespace std;

int main()
{
	while (true)
	{
		string text;
		cout << "calc> ";
		cin >> text;
		if (text == "\n")
			break;
		Interpreter *interpreter = new Interpreter(text);
		int result = interpreter->expr();
		delete interpreter;
		cout << result << endl;
	}
	return 0;
}