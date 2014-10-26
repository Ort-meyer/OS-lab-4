#pragma once

#include <string>
#include <vector>

#define NAMEOFFSET 1
#define NEXTOFFSET 21
#define SIZEOFFSET 23
#define PARENTOFFSET 27
#define DATAOFFSET 29
#define REMAINING 483

using namespace std;
class MemoryBlock
{
public:
	MemoryBlock();
	~MemoryBlock();

	//member methods
	//write
	int WriteBlock(int p_blockNumber, char p_content[512]);
	//specific writes
	void WriteType(int p_blockNumber, char p_type);
	void WriteName(int p_blockNumber, char p_name[20]);
	void WriteNextBlock(int p_blockNumber, short p_nextBlocK);
	void WriteSize(int p_blockNumber, int p_size);
	void WriteParentBlock(int p_blockNumber, short p_parentBlock);
	void WriteData(int p_blockNumber, char p_data[]);
	//really specific writes
	void WriteFolderData(int p_blockNumber, short* p_data);

	//read
	char* ReadBlock(int p_blockNumber);
	//specific reads
	char ReadType(int p_blockNumber);
	char* ReadName(int p_blockNumber);
	short ReadNextBlock(int p_blockNumber);
	int ReadSize(int p_blockNumber);
	short ReadParentBlock(int p_blockNumber);
	char* ReadData(int p_blockNumber);
	//really specific reads
	short* ReadFolderData(int p_blockNumber);
	char GetContent(int block, int byte);

private:
	char m_contents[250][512];

};

