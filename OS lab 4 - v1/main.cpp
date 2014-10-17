#include "FileSystem.h"
#include "Kjell.h"
#include "MemoryBlock.h"


//"member" variables
MemoryBlock* m_memoryBlock;
FileSystem* m_fileSystem;
Kjell* m_company;


int main()
{
	m_memoryBlock = new MemoryBlock();
	m_fileSystem = new FileSystem(m_memoryBlock);
	m_company = new Kjell(m_fileSystem);
	m_company->Start();
}