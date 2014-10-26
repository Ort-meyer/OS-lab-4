#include "FileSystem.h"
#include "Kjell.h"
#include "MemoryBlock.h"
#include <iostream>

//"member" variables
MemoryBlock* m_memoryBlock;
FileSystem* m_fileSystem;
Kjell* m_company;

using namespace std;

//void VoidExperiment()
//{
//	char type = '1';
//	const char* name = "John";
//	int size = 15764;
//	const char* text = "123";
//
//
//
//	unsigned char data[512];
//
//	memccpy(data, &type, 0, 1);
//	memccpy(data, name, 1, 4);
//	memccpy(data, &size, 5, sizeof(int));
//
//	memcpy(data, &type, 1);
//	memcpy(data + 1, name, 4);
//	memcpy(data + 5, &size, sizeof(int));
//
//	int postInt;
//	memcpy(&postInt, data + 5, sizeof(int));
//
//
//	for (int i = 0; i < 5;i++)
//	{
//		cout << data[i];
//	}
//	cout << postInt;
//
//	int derp;
//	derp = 2;
//
//
//
//
//}

int main()
{
	//VoidExperiment();
	m_memoryBlock = new MemoryBlock();
	m_fileSystem = new FileSystem(m_memoryBlock);
	m_company = new Kjell(m_fileSystem);
	m_company->Start();
}