#include "MemoryBlock.h"


MemoryBlock::MemoryBlock()
{
	//for (int i = 0; i < 250; i++)
	//{
	//	for (int j = 0; j < 512; j++)
	//	{
	//		m_contents[i][j] = '-2';
	//	}

	//}
}


MemoryBlock::~MemoryBlock()
{
}


//write
int MemoryBlock::WriteBlock(int p_blockNumber, char p_content[512])
{
	for (int i = 0; i < 512; i++)
	{
		m_contents[p_blockNumber][i] = p_content[i];
	}
	return 42;
}

char MemoryBlock::GetContent(int block, int byte)
{
	return m_contents[block][byte];
}

//write specifics
void MemoryBlock::WriteType(int p_blockNumber, char p_type)
{
	memcpy(m_contents[p_blockNumber], &p_type, 1);
}
void MemoryBlock::WriteName(int p_blockNumber, char p_name[20])
{
	memcpy(m_contents[p_blockNumber] + NAMEOFFSET, p_name, 20);
}
void MemoryBlock::WriteNextBlock(int p_blockNumber, short p_nextBlocK)
{
	memcpy(m_contents[p_blockNumber] + NEXTOFFSET, &p_nextBlocK, 2);
}
void MemoryBlock::WriteSize(int p_blockNumber, int p_size)
{
	memcpy(m_contents[p_blockNumber] + SIZEOFFSET, &p_size, 4);
}
void MemoryBlock::WriteParentBlock(int p_blockNumber, short p_parentBlock)
{
	memcpy(m_contents[p_blockNumber] + PARENTOFFSET, &p_parentBlock, 2);
}
void MemoryBlock::WriteData(int p_blockNumber, char p_data[])
{
	memcpy(m_contents[p_blockNumber] + DATAOFFSET, p_data, REMAINING);
}

//really specific writes
void MemoryBlock::WriteFolderData(int p_blockNumber, short* p_data)
{
	int t_size = ReadSize(p_blockNumber);
	memcpy(m_contents[p_blockNumber] + DATAOFFSET + t_size*2, p_data, 2); //has to be even because short // Writes to end of data array
}

//read
char* MemoryBlock::ReadBlock(int p_blockNumber)
{
	return m_contents[p_blockNumber];
}

//read specifics
char  MemoryBlock::ReadType(int p_blockNumber)
{
	char t_type;
	memcpy(&t_type, m_contents[p_blockNumber], 1);
	return t_type;
}
char* MemoryBlock::ReadName(int p_blockNumber)
{
	char* t_name = new char[20];
	memcpy(t_name, m_contents[p_blockNumber] + NAMEOFFSET, 20);
	return t_name;
}
short MemoryBlock::ReadNextBlock(int p_blockNumber)
{
	short t_next;
	memcpy(&t_next, m_contents[p_blockNumber] + NEXTOFFSET, 2);
	return t_next;
}
int   MemoryBlock::ReadSize(int p_blockNumber)
{
	int t_size;
	memcpy(&t_size, m_contents[p_blockNumber] + SIZEOFFSET, 4);
	return t_size;
}
short MemoryBlock::ReadParentBlock(int p_blockNumber)
{
	short t_parent;
	memcpy(&t_parent, m_contents[p_blockNumber] + PARENTOFFSET, 2);
	return t_parent;
}
char* MemoryBlock::ReadData(int p_blockNumber)
{
	char* t_data = new char[REMAINING];
	memcpy(t_data, m_contents[p_blockNumber]+DATAOFFSET, REMAINING);
	return t_data;
}

short* MemoryBlock::ReadFolderData(int p_blockNumber)
{
	short* t_data = new short [REMAINING-1];
	memcpy(t_data, m_contents[p_blockNumber] + DATAOFFSET, REMAINING-1); //has to be even because short
	return t_data;
}

