#pragma once
#include <Windows.h>
#include <string>

#ifdef CALCULATOR_EXPORTS
#define CALCULATOR_API __declspec(dllexport)
#else
#define CALCULATOR_API __declspec(dllimport)
#endif
 
 
extern "C"{
	CALCULATOR_API void calculator_init();
	CALCULATOR_API double get_total();
	CALCULATOR_API void calculate(const char* input);
	CALCULATOR_API std::string get_expression();
	
}