#pragma once
#include "MemoryBlock.h"
#include <string>

using namespace std;
class FileSystem
{
public:
	FileSystem(MemoryBlock* p_memoryBlock);
	~FileSystem();


	//member methods
	string Format();
	string ls(string p_path[]);
	string Create(string p_path[], char p_contents[]);
	string Cat(string p_path[]);
	string Save(string p_path[]);
	string Read(string p_path[]);
	string rm(string p_path[]);
	string Copy(string p_source[], string p_destination[]);
	string Append(string p_source[], string p_destination[]);
	string Rename(string p_source[], string p_destination[]);
	string mkdir(string p_path[]);
	string cd(string p_path[]);
	string pwd();



private:
	//member methods
	void DumpArray(string p_path[]);
	//member variables
	MemoryBlock* m_memoryBlock;

};

