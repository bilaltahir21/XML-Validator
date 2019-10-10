#pragma once

#include "delimeter_checker.h"
#include <fstream>

bool check;//this is a check as a global variable to create a difference between the delimeter and tag checking

class XML_Data
{
public:
	XML_Data();//a default constructor
	//this is a function to print error in a proper manner
	void print_error() const;
	//a static function to check the balancing of the quotes
	static bool qoutes_balanced(string st, int k);
	//this is teh main requirement of the assignment as it is totally based in stack
	void error_check();
	~XML_Data();//a default destructor
private:
	string tag_;
	int line_number{};
};

inline XML_Data::XML_Data()//we are using the default constructor as we always have to take input from file
= default;

inline void XML_Data::print_error() const
{
	if (check)//this is a check to confirm existence of data in the class
	{
		if (!(this->tag_.empty()))
		{
			cout << "Error occured in <" << tag_ << "> at the line number " << line_number << endl;
		}
		else
		{
			cout << "No error detected\n";
		}
	}
}

inline bool XML_Data::qoutes_balanced(string st, int k)
{	//this function is checking if there are any quotes(either double or single)
	//and then it checks if they are even or odd in number
	int d_q = 0;
	int s_q = 0;
	while (st[k] != '\0')
	{
		if (st[k] == '"')
		{
			d_q++;
		}
		if (st[k] == 39)
		{
			s_q++;
		}
		k++;
	}
	return d_q % 2 == 0 && s_q % 2 == 0;
}

inline void XML_Data::error_check()
{
	stack<tag> evaluator;
	bool run = true;
	int lines = 0;
	string st;
	ifstream fin;
	/////////////////////////////////
	fin.open("data.txt");
	while (!fin.eof())
	{
		lines++;
		getline(fin, st);
	}
	fin.close();
	/*this section is just checking the total numbers of lines*/
	st.clear();
	delimeter_checker d;
	/////////////////////////////////
	int j = 0;
	string holder;
	/*Now, we're just picking the lines from the file and checking them one by one for errors*/
	fin.open("data.txt");
	while (!fin.eof() && run)
	{
		getline(fin, st);
		check = d.is_balanced(st, j); //this is the condition if there is proper data in teh string
		if (check)
		{
			for (int k = 0; k < st.size(); k++)
			{
				holder.clear(); //clearing the string so that nothing converts itself to
				//junk as we always have to push the data back

				/*
				 *this is the condition for the closing tag and it is placed at the top
				 * due to its uniqueness of the tag otherwise the starting tag is always
				 * executed no matter what should be done
				 */
				if (st[k] == '<' && st[k + 1] == '/') //check for the ending tag
				{
					k = k + 2;
					while (st[k] != '>')
					{
						holder.push_back(st[k]);
						k++;
					}
					tag check;
					evaluator.pop(check);

					if (!(check.tag_ == holder)) //checking if the popped tag matches the
					{							 //pushed tag
						this->tag_ = check.tag_;
						this->line_number = check.line_number;
						run = false;
						break;
					}

					holder.clear();
				}
				//Handling the condition of prolog(header)
				//in which we check for the question marks
				//at the start and at the end
				if (st[k] == '<' && st[k + 1] == '?')
				{
					bool prolo = false;
					for (int l = 0; l < st.size(); l++)
					{
						prolo = XML_Data::qoutes_balanced(st, 0);
						if (!prolo)
						{
							break;
						}
						if (st[l] == '?' && st[l + 1] == '>')
						{
							prolo = true;
							break;
						}
						else
						{
							prolo = false;
						}
					}
					if (!prolo) //this check is mendatory because the check is altered everytime in the loop
					{
						//due to structure of the loop
						const string prol = "?prolog?";
						tag_ = prol;
						line_number = j + 1;
						run = false;
					}
				}
				/*
				 *Handling the condition of the comment in which there is an exclamation mark
				 * at the start of the tag and only two hyphens before the closing bracket
				 */
				else if (st[k] == '<' && st[k + 1] == '!' && st[k + 2] == '-' && st[k + 3] == '-')
				{
					bool comm = false;
					for (int l = 0; l < st.size(); l++)
					{
						if (st[l] == '-' && st[l + 1] == '-' && st[l + 2] == '>')
						{
							comm = true;
						}
						else
						{
							comm = false;
						}
						if (!comm) //this check is mendatory because the check is altered everytime in the loop
						{
							//due to structure of the loop
							const string comm = "!--comment--";
							this->tag_ = comm;
							this->line_number = j + 1;
							run = false;
						}
					}
				}
				/*
				 * These are the conditions to check if there is an opening tag
				 * and it also handles the attributes of the starting tag if they
				 * exist. It also checks the quotation marks (either single or double)
				 * if they exist in the section of attributes in the starting tag
				 */
				else if (st[k] == '<')
				{
					k++;
					bool attrib = true;
					while (st[k] != '>')
					{
						if (st[k] == ' ')
						{
							attrib = XML_Data::qoutes_balanced(st, k);
							//it is a static function to check the quotation marks
							while (st[k] != '>')
							{
								k++;
							}
							k++;
							break;
						}
						holder.push_back(st[k]);
						k++;
					}

					tag t;
					t.tag_ = holder;
					t.line_number = j + 1;
					evaluator.push(t);

					if (!attrib)//it is mendatory for handling the attributes of the starting tag
					{
						run = false;
						this->line_number = j + 1;
						this->tag_ = holder;
					}
				}
			}
		}
		else
		{
			break;
		}
		j++;
	}
}

inline XML_Data::~XML_Data()
= default;
