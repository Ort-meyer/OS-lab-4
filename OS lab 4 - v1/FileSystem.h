#pragma once
#include "MemoryBlock.h"
#include <string>
#include <vector>


#define NAMEOFFSET 1
#define NEXTOFFSET 21
#define SIZEOFFSET 23
#define PARENTOFFSET 27
#define DATAOFFSET 29

using namespace std;
class FileSystem
{
public:
	FileSystem(MemoryBlock* p_memoryBlock);
	~FileSystem();


	//member methods
	string Format();
	vector<string> ls();												//doneish
	string Create(string p_path[], char p_contents[]);
	string Cat(string p_path[]);
	string Save(string p_path[]);
	string Read(string p_path[]);
	string rm(string p_path[]);
	string Copy(string p_source[], string p_destination[]);
	string Append(string p_source[], string p_destination[]);
	string Rename(string p_source[], string p_destination[]);
	string mkdir(const char* p_name);							//doneish
	string cd(vector<string> p_path);
	string pwd();

	string CreateRootFolder(char p_name[20]);					//done


private:
	//member methods
	void DumpArray(string p_path[]);
	//member variables
	MemoryBlock* m_memoryBlock;

	short m_currentBlock; //the current folder the file system is in

	int m_blockCounter; //index for next avaliable block
	vector<int> m_freeblocks; //list of avaliable bloocks (when blocks are removed their indices are put in this list)

};

