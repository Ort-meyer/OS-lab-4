#pragma once

class MemoryBlock
{
public:
	MemoryBlock();
	~MemoryBlock();

	//member methods
	int WriteBlock(int p_blockNumber, char p_content[]);
	char* ReadBlock(int p_blockNumber);

private:
	char m_contents[250][512];
};

