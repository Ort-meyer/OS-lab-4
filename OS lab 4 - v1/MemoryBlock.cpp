#include "MemoryBlock.h"


MemoryBlock::MemoryBlock()
{
}


MemoryBlock::~MemoryBlock()
{
}


int MemoryBlock::WriteBlock(int p_blockNumber, char p_content[512])
{
	for (int i = 0; i < 512; i++)
	{
		m_contents[p_blockNumber][i] = p_content[i];
	}
	return 42;
}

char* MemoryBlock::ReadBlock(int p_blockNumber)
{
	return m_contents[p_blockNumber];
}