#include "Kjell.h"
#include <iostream>
#include <vector>
#include <sstream>
#include<iterator>

Kjell::Kjell(FileSystem* p_fileSystem)
{
	m_fileSystem = p_fileSystem;
}


Kjell::~Kjell()
{
}


void Kjell::Start()
{
	bool t_running = true;

	string t_input;
	vector<string> t_inputArray;
	while (t_running)
	{
		cout << "enter command: ";
		getline(cin, t_input);
		t_inputArray = Split(t_input, " ");
		
		//major ifs
		if (t_inputArray[0] == "quit")
		{
			break;
		}
		else if (t_inputArray[0] == "format")
		{
			//m_fileSystem->Format();
			cout << "it's all gone. Box still there tho" << endl;
		}
		else if (t_inputArray[0] == "ls")
		{

		}
		else if (t_inputArray[0] == "create")
		{

		}
		else if (t_inputArray[0] == "cat")
		{

		}
		else if (t_inputArray[0] == "save")
		{

		}
		else if (t_inputArray[0] == "read")
		{

		}
		else if (t_inputArray[0] == "rm")
		{

		}
		else if (t_inputArray[0] == "copy")
		{

		}
		else if (t_inputArray[0] == "append")
		{

		}
		else if (t_inputArray[0] == "rename")
		{

		}
		else if (t_inputArray[0] == "mkdir")
		{

		}
		else if (t_inputArray[0] == "cd")
		{

		}
		else if (t_inputArray[0] == "pwd")
		{

		}
		else if (t_inputArray[0] == "help")
		{

		}



		
	}
}

vector<string> Kjell::Split(string p_string, string p_target)
{
	string t_stringCopy = p_string;
	vector<string> t_returnWords;
	string t_token;
	size_t t_position = 0;
	while ((t_position = t_stringCopy.find(p_target)) != std::string::npos)
	{
		t_token = t_stringCopy.substr(0, t_position);
		t_returnWords.push_back(t_token);
		t_stringCopy.erase(0, t_position + p_target.length());
	}
	t_returnWords.push_back(t_stringCopy);

	return t_returnWords;
}