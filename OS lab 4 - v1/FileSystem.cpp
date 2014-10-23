#include "FileSystem.h"

FileSystem::FileSystem(MemoryBlock* p_memoryBlock)
{
	m_memoryBlock = p_memoryBlock;
	m_blockCounter = 0;
	m_currentBlock = -1;
}


FileSystem::~FileSystem()
{

}


string FileSystem::Format()
{
	delete m_memoryBlock;
	m_memoryBlock = new MemoryBlock();
	string derp;
	return derp;
}

vector<string> FileSystem::ls()
{

	vector<string> t_contentNames;
	//get the data
	char* t_data = m_memoryBlock->ReadBlock(m_currentBlock);

	//read size
	int t_numContent = m_memoryBlock->ReadSize(m_currentBlock);
	//memcpy(&t_numContent, t_data + SIZEOFFSET, 4);
	// t_contentBlocks = new short;
	 short* t_contentBlocks = m_memoryBlock->ReadFolderData(m_currentBlock);

	//memcpy(t_contentBlocks, t_data + DATAOFFSET, t_numContent * 2); //t_numContent*2 since each short is two bytes

	//vector<string> t_contentNames;
	for (int i = 0; i < t_numContent; i++)
	{
		//char* t_currentData = m_memoryBlock->ReadBlock(t_contentBlocks[i]);
		//char* t_currentBlockName = new char;
		//memcpy(t_currentBlockName, t_currentData + NAMEOFFSET, 20);
		char* t_currentBlockName = m_memoryBlock->ReadName(t_contentBlocks[i]);
		string t_string;
		t_contentNames.push_back(t_string.assign(t_currentBlockName));
	}
	return t_contentNames;
}
string FileSystem::Create(char* p_name, char* p_contents)
{
	//create file

	/*char t_type = '0';
	short t_nextBlock = -1;
	int t_size = 0;
	short t_partent = m_currentBlock;
	char* t_data;*/

	//memcpy(t_data, &t_type, sizeof(short));
	//memcpy(t_data + NAMEOFFSET, &p_name, sizeof(p_name));
	
	m_memoryBlock->WriteType(m_blockCounter, '0');
	m_memoryBlock->WriteName(m_blockCounter, p_name);
	m_memoryBlock->WriteNextBlock(m_blockCounter, -1);
	m_memoryBlock->WriteSize(m_blockCounter, sizeof(p_contents));
	m_memoryBlock->WriteParentBlock(m_blockCounter, m_currentBlock);
	m_memoryBlock->WriteData(m_blockCounter, p_contents);

	//m_memoryBlock->AddContent(m_currentBlock, m_blockCounter);

	m_blockCounter++;

	return "File created";
}

string FileSystem::Cat(vector<string> p_path)
{
	//write content in file
	//traverse path

	short t_blockToRead = Traverse(p_path);
	
	//if target is folder, do nothing
	if (m_memoryBlock->ReadType(t_blockToRead)) return "Target is a folder";

	//file found, read content
	string t_return;
	t_return.assign(m_memoryBlock->ReadData(t_blockToRead));

	return t_return;

}

//string FileSystem::Save(string p_path[])
//{
//	//save system on file
//}
//string FileSystem::Read(string p_path[])
//{
//	//read system from file
//}
//string FileSystem::rm(string p_path[])
//{
//	//remove file
//}

string FileSystem::Copy(vector<string> p_path, vector<string> p_destination)
{
	//copy file

	return "File copied";
}

//string FileSystem::Append(string p_source[], string p_destination[])
//{
//	//append file
//}

string FileSystem::Rename(vector<string> p_source, string p_destination)
{
	//rename file
	short t_block = Traverse(p_source);
	
	return "File renamed";
}

string FileSystem::mkdir(const char* p_name)
{
	//data that will be written
	char t_data[512];

	//information that will be written
	char t_type = '1';
	short t_next = -1;
	int t_size = 0;
	short t_parent = m_currentBlock;
	short t_blocks[241]; //(int)(483/sizeof(short)) = 241. That many shorts


	memcpy(t_data, &t_type, 1);
	memcpy(t_data + NAMEOFFSET, p_name, 20);
	memcpy(t_data + NEXTOFFSET, &t_next, 2);
	memcpy(t_data + SIZEOFFSET, &t_size, 4);
	memcpy(t_data + PARENTOFFSET, &t_parent, 2); 
	memcpy(t_data + DATAOFFSET, &t_blocks, 483); //483 = 512 - above bytes.

	m_memoryBlock->WriteBlock(m_blockCounter, t_data);

	//FOLDER IS CREATED. NOW WE ASSIGN IT TO CURRENT BLOCK

	//read parent data
	//char* t_parentData = m_memoryBlock->ReadBlock(t_parent);
	//int t_parentSize = 0;
	//memcpy(&t_parentSize, t_parentData + SIZEOFFSET, 4);

	int t_parentSize = m_memoryBlock->ReadSize(t_parent);

	//add the folder
	//memcpy(t_parentData + DATAOFFSET + t_parentSize * 2, &m_blockCounter, 2);
	m_memoryBlock->WriteFolderData(t_parent, &m_blockCounter);

	//add to parent size (since it now has another folder)
	t_parentSize++; //another folder is added
	m_memoryBlock->WriteSize(t_parent, t_parentSize);
	//memcpy(t_parentData + SIZEOFFSET, &t_parentSize, 2);

	//m_memoryBlock->WriteBlock(t_parent, t_parentData);

	m_blockCounter++;
	string derp;
	return derp;
}

string FileSystem::cd(vector<string> p_path)
{
	m_currentBlock = Traverse(p_path);
	return "directory changed";
}
//string FileSystem::pwd()
//{
//	//write name of folder
//}

string FileSystem::CreateRootFolder(char p_name[20])
{
	//data that will be written
	char t_data[512];

	//information that will be written
	char t_type = '1';
	short t_next = -1;
	int t_size = 0;
	short t_blocks[241]; //(int)(483/sizeof(short)) = 241. That many shorts


	memcpy(t_data, &t_type, 1);
	memcpy(t_data + NAMEOFFSET, p_name, 20);
	memcpy(t_data + NEXTOFFSET, &t_next, 2);
	memcpy(t_data + SIZEOFFSET, &t_size, 4);
	memcpy(t_data + PARENTOFFSET, &t_next, 2); //next works since root doesn't have a parent
	memcpy(t_data + DATAOFFSET, &t_blocks, 483); //483 = 512 - above bytes.

	m_memoryBlock->WriteBlock(m_blockCounter, t_data);
	m_blockCounter++;
	m_currentBlock = 0;

	string derp;
	return derp;
}

short FileSystem::Traverse(vector<string> p_path)
{
	short t_targetBlock;

	int t_pathLength = p_path.size();
	int t_currentPathSegment = 0;
	//keep searching 'till path is empty
	while (t_currentPathSegment < t_pathLength)
	{
		//get all subfolder names
		vector<string>t_currentContent = ls();
		//get subfolder indices
		char* t_currentData = m_memoryBlock->ReadBlock(m_currentBlock);
		short* t_currentContentIndices = new short;
		memcpy(t_currentContentIndices, t_currentData + DATAOFFSET, t_currentContent.size() * 2);

		bool t_folderFound = false;

		if (p_path[t_currentPathSegment] == "..")
		{
			short* t_currentParent = new short;
			memcpy(t_currentParent, t_currentData + PARENTOFFSET, 2);
			if (*t_currentParent == -1)
			{
				return -1;
			}
			else
			{
				t_targetBlock = *t_currentParent;
				return t_targetBlock;
			}
		}

		//compare subfolder names to path
		for (int i = 0; i < t_currentContent.size(); i++)
		{
			//check if path is found
			if (p_path[t_currentPathSegment] == t_currentContent[i])
			{
				t_targetBlock = t_currentContentIndices[i];
				t_currentPathSegment++;
				t_folderFound = true;
				break;
			}
		}
		if (!t_folderFound)
		{
			return -1;
		}
	}

	return t_targetBlock;
}