
#pragma once

#include "FileSystem.h"
#include <vector>
#include <string>

using namespace std;
class Kjell
{
public:
	Kjell(FileSystem* p_fileSystem);
	~Kjell();

	//member methods
	void Start();


private:
	//member methods
	void PrintHelp();
	string* Split(string p_string, char p_target);
	char* ReadBlock();
	string ReadLine();
	void DumpArray(string p_stringArray[]);




	//member variables
	FileSystem* m_fileSystem;


};

