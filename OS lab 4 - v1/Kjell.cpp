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
	m_fileSystem->CreateRootFolder("root");
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
			vector<string> t_contents =	m_fileSystem->ls();
			for (int i = 0; i < t_contents.size(); i++)
			{
				cout << t_contents[i] << endl;
			}
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
			m_fileSystem->mkdir(t_inputArray[1].c_str());
		}
		else if (t_inputArray[0] == "cd")
		{
			//remove 
			vector<string>t_path = Split(t_inputArray[1], "/");
			//	t_inputArray;
			//t_path.erase(t_path.begin());
			//t_path.shrink_to_fit();

			cout << m_fileSystem->cd(t_path) << endl;
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