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
	CreateRootFolder("root");
	return "system formatted. New root Created";
}

vector<string> FileSystem::ls()
{
	//read size
	int t_numContent = m_memoryBlock->ReadSize(m_currentBlock);
	//read data
	short* t_contentBlocks = m_memoryBlock->ReadFolderData(m_currentBlock);

	//get stuff in folder
	vector<string> t_contentNames;
	for (int i = 0; i < t_numContent; i++)
	{
		char* t_currentBlockName = m_memoryBlock->ReadName(t_contentBlocks[i]);
		string t_string;
		t_contentNames.push_back(t_string.assign(t_currentBlockName));
	}
	return t_contentNames;
}
string FileSystem::Create(char* p_name, char* p_contents)
{
	//create file

	m_memoryBlock->WriteType(m_blockCounter, '0');
	m_memoryBlock->WriteName(m_blockCounter, p_name);
	m_memoryBlock->WriteNextBlock(m_blockCounter, -1);
	m_memoryBlock->WriteSize(m_blockCounter, sizeof(p_contents));
	m_memoryBlock->WriteParentBlock(m_blockCounter, m_currentBlock);
	m_memoryBlock->WriteData(m_blockCounter, p_contents);

	//add to folder
	AddToFolder(m_currentBlock, m_blockCounter);

	m_blockCounter++;

	return "File created";
}

string FileSystem::Cat(vector<string> p_path)
{
	//write content in file
	//traverse path

	short t_blockToRead = Traverse(p_path);

	//if target is folder, do nothing
	if (m_memoryBlock->ReadType(t_blockToRead) == 1) 
		return "Target is a folder\n";

	//file found, read content
	string t_return;
	t_return.assign(m_memoryBlock->ReadData(t_blockToRead));

	return t_return;

}

string FileSystem::Save(string p_path)
{
	//save system on file
	ofstream t_file;
	t_file.open(p_path); //ios::binary for optimization?
	for (int i = 0; i < 250; i++)
	{
		if (m_memoryBlock->ReadType(i) != -1)
		{

			char* t_name = m_memoryBlock->ReadName(i);
			//figure out how many chars in name (silly fix since it stops reading at an empty byte)
			char t_data[512];
			string t_nameString = t_name;

			int t_nameLength = t_nameString.length();
			//write data
			//t_file << m_memoryBlock;
			t_file << m_memoryBlock->ReadType(i);
			t_file << t_nameLength;
			t_file << t_name;
			t_file << m_memoryBlock->ReadNextBlock(i);
			t_file << m_memoryBlock->ReadSize(i);
			t_file << m_memoryBlock->ReadParentBlock(i);
			t_file << m_memoryBlock->ReadData(i);
			t_file << endl;
		}
	}
	t_file.close();
	return "system saved\n";
}
string FileSystem::Read(string p_path)
{
	//read system from file
	Format();
	m_memoryBlock = new MemoryBlock;
	string t_line;
	ifstream t_file(p_path);
	int i = 0;
	if (t_file.is_open())
	{
		while (getline(t_file, t_line))
		{
			if (!t_line.empty())
			{
				//get all data in one big char array
				char* t_data = new char;
				strcpy(t_data, t_line.c_str());
				int t_nameSize;
				memcpy(&t_nameSize, t_data + 1, 4);

				char t_name[20];
				memcpy(t_name, t_data + 2, 20);

				short* t_next = new short;
				memcpy(t_next, t_data + NEXTOFFSET, 2);

				int* t_size = new int;
				memcpy(t_size, t_data + SIZEOFFSET, 4);

				short* t_parent = new short;
				memcpy(t_parent, t_data + PARENTOFFSET, 2);

				char* t_blockData = new char;
				memcpy(t_blockData, t_blockData + DATAOFFSET, REMAINING);

				m_memoryBlock->WriteType(i, t_data[0]);
				m_memoryBlock->WriteName(i, t_name);
				m_memoryBlock->WriteNextBlock(i, *t_next);
				m_memoryBlock->WriteSize(i, *t_size);
				m_memoryBlock->WriteParentBlock(i, *t_parent);
				m_memoryBlock->WriteData(i, t_blockData);
				
				i++;
			}
		}
	}
	return "system read\n";
}
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

string FileSystem::Rename(vector<string> p_source, char* p_destination)
{
	//rename file
	short t_block = Traverse(p_source);
	m_memoryBlock->WriteName(t_block, p_destination);

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
	AddToFolder(t_parent, m_blockCounter);


	m_blockCounter++;

	string derp;
	return derp;
}

string FileSystem::cd(vector<string> p_path)
{
	m_currentBlock = Traverse(p_path);
	return "directory changed";
}
string FileSystem::pwd()
{
	return m_memoryBlock->ReadName(m_currentBlock);
}

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

//string FileSystem::pwd()
//{
//	//write name of folder
//}


void FileSystem::AddToFolder(int p_folderNumber, short p_added)
{
	//Check if block is full
	int t_parentSize = m_memoryBlock->ReadSize(p_folderNumber);
	if (t_parentSize <= REMAINING - 1)//there' space left
	{
		//add the folder
		m_memoryBlock->WriteFolderData(p_folderNumber, &p_added);
		//update the size
		t_parentSize++;
		m_memoryBlock->WriteSize(p_folderNumber, t_parentSize);
	}
	else
	{
		//write to new block
	}
}



