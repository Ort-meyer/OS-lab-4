#include "FileSystem.h"


FileSystem::FileSystem(MemoryBlock* p_memoryBlock)
{
	m_memoryBlock = p_memoryBlock;
}


FileSystem::~FileSystem()
{

}


//string FileSystem::Format()
//{
//	delete m_memoryBlock;
//	m_memoryBlock = new MemoryBlock();
//}
//string FileSystem::ls(string p_path[])
//{
//	//list content in folder
//}
//string FileSystem::Create(string p_path[], char p_contents[])
//{
//	//create fil
//}
//string FileSystem::Cat(string p_path[])
//{
//	//write content in file
//}
//string FileSystem::Save(string p_path[])
//{
//	//save system on file
//}
//string FileSystem::Read(string p_path[])
//{
//	//read system from file
//}
//string FileSystem::rm(string p_path[])
//{
//	//remove file
//}
//string FileSystem::Copy(string p_source[], string p_destination[])
//{
//	//copy file
//}
//string FileSystem::Append(string p_source[], string p_destination[])
//{
//	//append file
//}
//string FileSystem::Rename(string p_source[], string p_destination[])
//{
//	//rename file
//}
//string FileSystem::mkdir(string p_path[])
//{
//	//create new folder
//}
//string FileSystem::cd(string p_path[])
//{
//	//change folder
//}
//string FileSystem::pwd()
//{
//	//write name of folder
//}