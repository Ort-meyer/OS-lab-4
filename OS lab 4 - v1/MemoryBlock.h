#pragma once

class MemoryBlock
{
public:
	MemoryBlock();
	~MemoryBlock();

	//member methods
	//write
	int WriteBlock(int p_blockNumber, char p_content[512]);

	//read
	char* ReadBlock(int p_blockNumber);

private:
	char m_contents[250][512];
};

