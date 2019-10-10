#pragma once
#include "stack.h"
#include <iostream>
#include <string>

using namespace std;

class delimeter_checker
{
public:
	bool is_Valid(char* inpu, const int line_n) const;
	void print_Error(char* input, int error_place, const int error_type, const int line_) const;

	bool is_balanced(std::string input, int n) const;

	int no_error = 0;
	int matching_error = 1;
	int missing_right_delimeter_error = 2;
	int missing_left_delimeter_error = 3;
};

//the function to check the balance of delimeters




inline bool delimeter_checker::is_Valid(char* inpu, const int line_n) const
{
	std::string input(inpu);
	stack<char> stac_;
	//get characters
	for (int i = 0; input.length() > i; i++)
	{
		char ch = input[i];
		switch (ch)
		{
			//checking for the opening symbols
		case '<':

			stac_.push(ch);
			break;

			//checking for the closing symbols

		case '>':

			if (!(stac_.isEmpty()))
			{
				char c_x;
				stac_.pop(c_x); //now check for each case
				if ((ch != '}' || c_x == '{') && (ch != ']' || c_x == '[') && (ch != ')' || c_x == '(') && (ch != '>' ||
					c_x == '<') && (c_x == '?' && ch != '?'))
				{
					print_Error(inpu, i, matching_error, line_n);
					return false;
				}
			}
			else
			{
				//when the stack gets empty prematurely
				print_Error(inpu, i, missing_left_delimeter_error, line_n);
				return false;
			}
			break;

		default: //no actions on characters other than brackets
			break;
		} //switching conditions ending
	} //end of the 'char*' array containing data

	if (!(stac_.isEmpty()))
	{
		print_Error(inpu, input.length(), missing_right_delimeter_error, line_n);
		return false;
	}

	print_Error(inpu, 0, no_error, line_n);
	return true;
} //end of the function is_Valid(char* input)

//function named print_Error() to print the correct error which is returning the
//type of error in the given string
//it will just return the defined number(in the private section of the class) of the error
inline void delimeter_checker::print_Error(char* input, const int error_place, int error_type, const int line_) const
{
	//checking if there isn't any error
	if (error_type == no_error)
	{
		//displaying the error in a proper way
	}

	//if error exists
	switch (error_type)
	{
	case 1:
		std::cout << "\nPaired delimeters don't match at line number " << line_ << "\n";
		//displaying the error in a proper way
		std::cout << input << std::endl;
		for (int i = 0; i < error_place; i++)
		{
			std::cout << " ";
		}
		std::cout << "^" << std::endl;
		break;
	case 2:
		std::cout << "\nMissing right delimeter at line number " << line_ << "\n";
		//displaying the error in a proper way
		std::cout << input << std::endl;
		for (int i = 0; i < error_place; i++)
		{
			std::cout << " ";
		}
		std::cout << "^" << std::endl;
		break;
	case 3:
		std::cout << "\nMissing left delimeter at line number " << line_ << "\n";
		//displaying the error in a proper way
		std::cout << input << std::endl;
		for (int i = 0; i < error_place; i++)
		{
			std::cout << " ";
		}
		std::cout << "^" << std::endl;
		break;
	default:
		break;
	}
}

inline bool delimeter_checker::is_balanced(string input, const int n) const
{
	char* ch = new char[input.size()];
	int i = 0;
	for (; i < input.size(); i++)
	{
		ch[i] = input[i];
	}
	ch[i] = '\0';
	delimeter_checker dc;
	return (dc.is_Valid(ch, n));
}

class tag//it a class to facilitate the displaying of the lines number in the error
{
public:
	string tag_;
	int line_number{};
};