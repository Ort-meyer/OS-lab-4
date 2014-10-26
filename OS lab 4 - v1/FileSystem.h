#pragma once
#include "MemoryBlock.h"
#include <string>
#include <vector>
#include <fstream>




using namespace std;
class FileSystem
{
public:
	FileSystem(MemoryBlock* p_memoryBlock);
	~FileSystem();

	
	//member methods
	string Format();													//done
	vector<string> ls();												//doneish
	vector<string> ls(short p_block);									//done
	string Create(char* p_name, char* p_contents);						//done
	string Cat(vector<string> p_path);									//done
	string Save(string p_path);											//done
	string Read(string p_path);
	string Save1(string p_path);
	string Read1(string p_path);
	string rm(string p_path[]);
	string Copy(vector<string> p_path, vector<string> p_destination);	//done
	string Append(vector<string> p_path, char* p_newContent);
	string Rename(vector<string> p_source, char* p_destination);		//done
	string mkdir(const char* p_name);									//doneish
	string cd(vector<string> p_path);									//done
	string pwd();														//done

	string CreateRootFolder(char* p_name);							//done


	char GetType();

private:
	//member methods
	void DumpArray(string p_path[]);
	short Traverse(vector<string> p_path);
	void AddToFolder(int p_folderNumber, short p_added);
	//member variables
	MemoryBlock* m_memoryBlock;

	short m_currentBlock; //the current folder the file system is in

	short m_blockCounter; //index for next avaliable block
	vector<int> m_freeblocks; //list of avaliable bloocks (when blocks are removed their indices are put in this list)



};

