#include "Kjell.h"
#include <iostream>


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
	string* t_inputArray;
	while (t_running)
	{

		cout << "enter command: ";
		cin >> t_input;
		t_inputArray = Split(t_input, ' ');
		
	}
}

