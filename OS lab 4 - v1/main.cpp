#include "FileSystem.h"
#include "Kjell.h"
#include "MemoryBlock.h"
#include <iostream>

//"member" variables
MemoryBlock* m_memoryBlock;
FileSystem* m_fileSystem;
Kjell* m_company;

using namespace std;

void VoidExperiment()
{
	char* type = "1";
	char* name = "John";
	int* size = 0;
	char* text = "123";

	void* data;
	data = size;
	cout << sizeof(data)<<endl;
	int* poststring = (int*)data;

	//cout << *poststring;




}

int main()
{
	VoidExperiment();
	m_memoryBlock = new MemoryBlock();
	m_fileSystem = new FileSystem(m_memoryBlock);
	m_company = new Kjell(m_fileSystem);
	m_company->Start();
}