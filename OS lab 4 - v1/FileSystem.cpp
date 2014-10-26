#include "FileSystem.h"
#include <iostream>
#include <stdio.h>

FileSystem::FileSystem(MemoryBlock* p_memoryBlock)
{
	m_memoryBlock = p_memoryBlock;
	m_blockCounter = 0;
	m_currentBlock = -1;
	CreateRootFolder("root");
}


FileSystem::~FileSystem()
{

}


string FileSystem::Format()
{
	delete m_memoryBlock;
	m_memoryBlock = new MemoryBlock();
	m_blockCounter = 0;
	m_currentBlock = -1;
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

vector<string> FileSystem::ls(short p_block)
{
	//read size
	int t_numContent = m_memoryBlock->ReadSize(p_block);
	//read data
	short* t_contentBlocks = m_memoryBlock->ReadFolderData(p_block);

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
	m_memoryBlock->WriteSize(m_blockCounter, strlen(p_contents));
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


	//for (int i = 0; i < 250; i++)
	//{
	//	//if (m_memoryBlock->ReadType(i) != -2) //is initialized
	//	{

	//		//char* t_name = m_memoryBlock->ReadName(i);
	//		////figure out how many chars in name (silly fix since it stops reading at an empty byte)
	//		////cast name length
	//		//string t_nameString = t_name;
	//		//int t_nameLength = t_nameString.length();
	//		//char* t_cNameLength = new char;
	//		//memcpy(t_cNameLength, &t_nameLength, 4);
	//		////cast next block
	//		//char* t_cNextBlock= new char;
	//		//short t_nextBlock = m_memoryBlock->ReadNextBlock(i);
	//		//memcpy(t_cNextBlock, &t_nextBlock, 2);
	//		////cast size
	//		//char* t_cSize = new char;
	//		//int t_size = m_memoryBlock->ReadSize(i);
	//		//memcpy(t_cSize, &t_size, 4);
	//		////cast parent block
	//		//char* t_cParentBlock = new char;
	//		//short t_parentBlock = m_memoryBlock->ReadParentBlock(i);
	//		//memcpy(t_cParentBlock, &t_parentBlock, 2);





	//		////write data
	//		////t_file << m_memoryBlock;
	//		//t_file << m_memoryBlock->ReadType(i);
	//		//t_file << t_cNameLength;
	//		//t_file << t_name;
	//		//t_file << t_cNextBlock;
	//		//t_file << t_cSize;
	//		//t_file << t_cParentBlock;
	//		//t_file << m_memoryBlock->ReadData(i);
	//		//t_file << endl;


	//		//SECOND VERSION
	//		char* t_data = m_memoryBlock->ReadBlock(i);
	//		t_file << t_data << "\n";



	//		//char* t_name = m_memoryBlock->ReadName(i);
	//		//string t_nameString = t_name;
	//		//int t_nameLength = t_nameString.length();

	//		//t_file << m_memoryBlock->ReadType(i);
	//		//t_file << t_nameLength;
	//		//t_file << t_name;
	//		//t_file << m_memoryBlock->ReadNextBlock(i);
	//		//t_file << m_memoryBlock->ReadSize(i);
	//		//t_file << m_memoryBlock->ReadParentBlock(i);
	//		//t_file << m_memoryBlock->ReadData(i);
	//		//t_file << endl;

	//		
	//		

	//	}
	//}
	////t_file.close();


	//THIS SHOULD WORK (might be problem in folders' data)
	for (int i = 0; i < 250; i++)
	{
		char t_type = m_memoryBlock->ReadType(i);
		t_file << t_type;
		int t_size = strlen(m_memoryBlock->ReadName(i));

		for (int k = 1; k < t_size+1; k++)
			t_file << m_memoryBlock->GetContent(i, k);		//reads every character in name 

		for (int j = t_size; j < 20; j++)
			t_file << "?";

				
		t_file << m_memoryBlock->ReadNextBlock(i);
		t_file << m_memoryBlock->ReadSize(i);
		t_file << m_memoryBlock->ReadParentBlock(i);
		short t_data;
		if (t_type == '1'){
			t_data = *(m_memoryBlock->ReadFolderData(i));
			t_file << t_data << endl;
		}

		else
		{
			t_file << m_memoryBlock->ReadData(i) << endl;
		}

	}

	return "system saved\n";
}
string FileSystem::Read(string p_path)
{
	//read system from file
	//Format();
	//m_memoryBlock = new MemoryBlock;
	//string t_line;
	//ifstream t_file(p_path);
	//int i = 0;
	//if (t_file.is_open())
	//{
	//	while (getline(t_file, t_line))
	//	{
	//		if (!t_line.empty())
	//		{
	//			////get all data in one big char array
	//			//char* t_data = new char;
	//			//strcpy(t_data, t_line.c_str());
	//			//int t_nameSize;
	//			//memcpy(&t_nameSize, t_data + 1, 4);

	//			//char t_name[20];
	//			//memcpy(t_name, t_data + 5, 20);

	//			//short* t_next = new short;
	//			//memcpy(t_next, t_data + NEXTOFFSET+4, 2);

	//			//int* t_size = new int;
	//			//memcpy(t_size, t_data + SIZEOFFSET+4, 4);

	//			//short* t_parent = new short;
	//			//memcpy(t_parent, t_data + PARENTOFFSET+4, 2);

	//			//char* t_blockData = new char;
	//			//memcpy(t_blockData, t_blockData + DATAOFFSET+4, REMAINING);

	//			//m_memoryBlock->WriteType(i, t_data[0]);
	//			//m_memoryBlock->WriteName(i, t_name);
	//			//m_memoryBlock->WriteNextBlock(i, *t_next);
	//			//m_memoryBlock->WriteSize(i, *t_size);
	//			//m_memoryBlock->WriteParentBlock(i, *t_parent);
	//			//m_memoryBlock->WriteData(i, t_blockData);
	//			//


	//			if (i > 511)
	//			{
	//				int derp;
	//				derp = 1;
	//			}
	//			//SECOND VERSION
	//			char t_data[512];
	//			strcpy(t_data, t_line.c_str());
	//			m_memoryBlock->WriteBlock(i, t_data);
	//			
	//			i++;

	//			//char* t_data = new char;
	//			//strcpy(t_data, t_line.c_str());
	//			//int t_nameLength = t_line[1];
	//			//char t_name[20];
	//			//memcpy(t_name, t_data + 2, 20);

	//			//m_memoryBlock->WriteType(i, t_line[0]);
	//			//m_memoryBlock->WriteName(i, t_name);
	//			//m_memoryBlock->WriteNextBlock(i, );
	//			//m_memoryBlock->WriteSize(i, *t_size);
	//			//m_memoryBlock->WriteParentBlock(i, *t_parent);
	//			//m_memoryBlock->WriteData(i, t_blockData);

	//			//THIRD VERSION

	//		}
	//	}
	//}

	Format();
	int i = 0;
	//for (int i = 0; i < 250; i++)
	//{
		int readBytes = 0;
		ifstream t_file(p_path);
		if (!t_file.is_open())
			return "could not open file";

		string t_line;
		getline(t_file, t_line);

		char t_type = t_line.at(readBytes++);
		char t_name[20];
		for (int j = 1; j < 21; j++)		//reads following 20 bytes
		{
			char t_current = t_line.at(readBytes++);
			if (t_current != '?')
				memcpy(t_name + j, &t_current, 1);		//if not ? add to name
		}

		char t_read[1];									
		const char* t_next;
		memcpy(t_read, &t_line.at(readBytes++), 1);

		if (t_read[0] == '-')									//if first char = -, then nextBloxk =-1
		{
			t_next = "-1";
			readBytes++;									//skips the next char, which is always "1"
		}
		else
		{
			t_next = &t_read[0];								//else it is as read
		}
		short t_nextBlock = (short)atol(t_next);					//cast char* to short

		int t_size = t_line.at(readBytes++);

		const char* t_parent;
		memcpy(t_read, &t_line.at(readBytes++), 1);

		if (t_read[0] == '-')									//if first char = -, then nextBloxk =-1
		{
			t_parent = "-1";
			readBytes++;
		}
		else
			t_parent = &t_read[0];
		short t_parentBlock = (short)atol(t_parent);

		char t_readData[482];
		char* t_data = "4";
		//int t_writtenBytes = 0;
		//for (int j = readBytes; j < readBytes + t_size; j++)
		//{
		//	char t_readChar = t_line.at(j);
		//	memcpy(t_readData + t_writtenBytes, &t_readChar, 1);
		//	//t_data[t_writtenBytes] = t_readData[t_writtenBytes];
		//	t_writtenBytes++;
		//}

		m_memoryBlock->WriteType(i, t_type);
		m_memoryBlock->WriteName(i, t_name);
		m_memoryBlock->WriteNextBlock(i, t_nextBlock);
		m_memoryBlock->WriteSize(i, t_size);
		m_memoryBlock->WriteParentBlock(i, t_parentBlock);
		m_memoryBlock->WriteData(i, t_data);

		if (t_parentBlock != -1)
			AddToFolder(t_parentBlock, i);
	//}
	return "system read\n";
}


//string FileSystem::rm(string p_path[])
//{
//	//remove file
//}

string FileSystem::Copy(vector<string> p_path, vector<string> p_destination)
{
	//copy file
	short t_sourceFile = Traverse(p_path);
	short t_destinationFolder = Traverse(p_destination);

	char* t_data = m_memoryBlock->ReadBlock(t_sourceFile);
	m_memoryBlock->WriteBlock(m_blockCounter, t_data);
	m_memoryBlock->WriteParentBlock(m_blockCounter, t_destinationFolder);
	AddToFolder(t_destinationFolder, m_blockCounter);

	m_blockCounter++;

	return "File copied";
}

string FileSystem::Append(vector<string> p_path, char* p_newContent)
{
	//append file
	short t_block = Traverse(p_path);

	char* t_data = m_memoryBlock->ReadData(t_block);
	memcpy(t_data + strlen(t_data), &p_newContent, strlen(p_newContent));

	m_memoryBlock->WriteData(t_block, t_data);

	return "Succeded";
}

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

	//cout << GetType();

	//information that will be written
	char t_type = '1';
	short t_next = -1;
	int t_size = 0;
	short t_parent = m_currentBlock;
	short t_blocks = 0;
	//short t_blocks[241]; //(int)(483/sizeof(short)) = 241. That many shorts
	//cout << GetType();

	memcpy(t_data, &t_type, 1);
	memcpy(t_data + NAMEOFFSET, p_name, 20);
	memcpy(t_data + NEXTOFFSET, &t_next, 2);
	memcpy(t_data + SIZEOFFSET, &t_size, 4);
	memcpy(t_data + PARENTOFFSET, &t_parent, 2);
	//cout << GetType();
	m_memoryBlock->WriteBlock(m_blockCounter, t_data);
	short t_folderData = 0;
	m_memoryBlock->WriteFolderData(m_blockCounter, &t_folderData);
	//cout << GetType();
	//FOLDER IS CREATED. NOW WE ASSIGN IT TO CURRENT BLOCK
	AddToFolder(t_parent, m_blockCounter);
	//cout << GetType() << endl;

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

string FileSystem::CreateRootFolder(char* p_name)
{
	//data that will be written
	char t_data[512];

	//information that will be written
	char t_type = '1';
	short t_next = -1;
	int t_size = 0;
	short t_blocks = 0;


	memcpy(t_data, &t_type, 1);
	memcpy(t_data + NAMEOFFSET, p_name, 20);
	memcpy(t_data + NEXTOFFSET, &t_next, 2);
	memcpy(t_data + SIZEOFFSET, &t_size, 4);
	memcpy(t_data + PARENTOFFSET, &t_next, 2); //next works since root doesn't have a parent
	memcpy(t_data + DATAOFFSET, &t_blocks, 1); 

	m_memoryBlock->WriteBlock(m_blockCounter, t_data);
	m_blockCounter++;
	m_currentBlock = 0;

	string derp;
	return derp;
}

short FileSystem::Traverse(vector<string> p_path)
{
	short t_targetBlock = m_currentBlock;

	int t_pathLength = p_path.size();
	int t_currentPathSegment = 0;
	//keep searching 'till path is empty
	while (t_currentPathSegment < t_pathLength)
	{
		//get all subfolder names
		vector<string>t_currentContent = ls(t_targetBlock);
		//get subfolder indices
		char* t_currentData = m_memoryBlock->ReadBlock(t_targetBlock);
		short* t_currentContentIndices = new short;
		memcpy(t_currentContentIndices, t_currentData + DATAOFFSET, t_currentContent.size() * 2);

		bool t_folderFound = false;

		if (p_path[t_currentPathSegment] == "..")
		{
			short t_currentParent = m_memoryBlock->ReadParentBlock(t_targetBlock);
			//memcpy(t_currentParent, t_currentData + PARENTOFFSET, 2);
			if (t_currentParent == -1)
			{
				return -1;
			}
			else
			{
				t_targetBlock = t_currentParent;
				t_currentPathSegment++;
				t_folderFound = true;
			}
		}
		else
		{
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
		}

		if (!t_folderFound)
		{
			return -1;
		}
	}
	return t_targetBlock;
}

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

char FileSystem::GetType()
{
	return m_memoryBlock->ReadType(1);
}