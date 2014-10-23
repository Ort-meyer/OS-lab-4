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
			m_fileSystem->Format();
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
			char* t_name = const_cast<char*>(t_inputArray[1].c_str());
			cout << "Content of file: " << endl;
			string t_contentString;
			getline(cin, t_contentString);
			char* t_content = const_cast<char*>(t_contentString.c_str());

			m_fileSystem->Create(t_name, t_content);
		}
		else if (t_inputArray[0] == "cat")
		{
			vector<string>t_path = Split(t_inputArray[1], "/");
			string t_content = m_fileSystem->Cat(t_path);
			cout << t_content << endl;
		}
		else if (t_inputArray[0] == "save")
		{
			m_fileSystem->Save(t_inputArray[1]);
		}
		else if (t_inputArray[0] == "read")
		{
			m_fileSystem->Read(t_inputArray[1]);
		}
		else if (t_inputArray[0] == "rm")
		{

		}
		else if (t_inputArray[0] == "copy")
		{
			vector<string>t_source = Split(t_inputArray[1], "/");
			vector<string>t_destination = Split(t_inputArray[2], "/");

			m_fileSystem->Copy(t_source, t_destination);
		}
		else if (t_inputArray[0] == "append")
		{

		}
		else if (t_inputArray[0] == "rename")
		{
			vector<string>t_path = Split(t_inputArray[1], "/");
			const char* t_const = t_inputArray[2].c_str();
			char* t_destination = const_cast<char*>(t_const);

			m_fileSystem->Rename(t_path, t_destination);
		}
		else if (t_inputArray[0] == "mkdir")
		{
			m_fileSystem->mkdir(t_inputArray[1].c_str());
		}
		else if (t_inputArray[0] == "cd")
		{
			vector<string>t_path = Split(t_inputArray[1], "/");
			cout << m_fileSystem->cd(t_path) << endl;
		}
		else if (t_inputArray[0] == "pwd")
		{
			cout << "Working directory: " << m_fileSystem->pwd() << endl;
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