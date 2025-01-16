#include "pch.h"
#include <utility>
#include <limits.h>
#include "Calculator.h"
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cctype> 
#include <stack>

double total;
std::string expression;
bool lastCharIsOperation = false;
bool decimalInLastNum = false;

double evaluateExpression(const std::string& expr);
int precedence(char op);
void performOperation(std::stack<double>& numbers, char op);

void AttachConsole() {
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	//test
}

void calculator_init() {
	total = 0.0;
}

void processCharacter(char input) {
	//test
	//this is a test
	if (std::isdigit(input) || input == '.') { 
		// Handle digits and decimal point 
		if (input == '.' && decimalInLastNum == true) { 
			// Ignore additional decimal points if one already exists in the current number 
			return; 
		}
		else if (input == '.') {
			decimalInLastNum = true;
		}
		expression += input; 
		lastCharIsOperation = false; 
	} else if (input == '+' || input == '-' || input == '*' || input == '/' || input == '=') { 
		// Handle operations 
		if (!lastCharIsOperation) { 
			expression += input; 
			lastCharIsOperation = true; 
			decimalInLastNum = false;
		} if (input == '=') { 
			// Evaluate the expression 
			total = evaluateExpression(expression); 
			std::cout << "Result: " << total << std::endl; 
			expression = std::to_string(total); 
		} 
	} else if (input == 'C') {
		expression = "";
		total = 0.0;
	} else if (input == '<') {
		expression.pop_back();
	}
}

void calculate(const char* input) { 
	while (*input != '\0') { 
		processCharacter(*input); 
		++input; 
	} 
}

double evaluateExpression(const std::string& expr) { 
	// Simple evaluation logic (expand as needed) 
	std::stack<double> numbers; 
	std::stack<char> operations; 

	for (size_t i = 0; i < expr.size(); ++i) { 
		if (std::isdigit(expr[i]) || expr[i] == '.') {
			std::string num = ""; 
			while (i < expr.size() && (std::isdigit(expr[i]) || expr[i] == '.')) { 
				num += expr[i++]; 
			} 
		--i; 
		numbers.push(std::stod(num)); 
		} 
		else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') { 
			while (!operations.empty() && precedence(operations.top()) >= precedence(expr[i])) { 
				performOperation(numbers, operations.top()); 
				operations.pop(); 
			} 
			operations.push(expr[i]); 
		} 
	} while (!operations.empty()) { 
		performOperation(numbers, operations.top()); 
		operations.pop(); 
	} return numbers.top(); 
} 
int precedence(char op) { 
	if (op == '+' || op == '-') return 1; 
	if (op == '*' || op == '/') return 2; 
	return 0; 
} 
void performOperation(std::stack<double>& numbers, char op) { 
	double b = numbers.top(); 
	numbers.pop(); 
	double a = numbers.top(); 
	numbers.pop(); 
	double result = 0.0; 
	switch (op) { 
		case '+': result = a + b; break; 
		case '-': result = a - b; break; 
		case '*': result = a * b; break; 
		case '/': result = a / b; break; 
	} 
	numbers.push(result); 
}


double get_total() {
	return total;
}

const char * get_expression() {
	static std::string temp; 
	temp = expression;
	return temp.c_str();
}