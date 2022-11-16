/*
 * MemoryManager.h
 *
 *  Created on: 14.11.2022
 *      Author: melah
 */

#ifndef MEMORYMANAGER_MEMORYMANAGER_H_
#define MEMORYMANAGER_MEMORYMANAGER_H_

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

//#include "TFileObject.h"

using namespace std;
namespace fs = std::filesystem;

class FileObject{

public:
	enum class Location{
		Flash,
		SD
	};
public:
	FileObject(Location location, uint32_t id, string folder, string filename, string ext, uint32_t filesize, uint16_t numberofFile):
		m_location(location), m_bufferId(id), m_folder(folder), m_fileName(filename),
		m_extension(ext), m_fileSize(filesize), m_numberOfFile(numberofFile){
		if(numberofFile > 1) m_isRingBuffer = true;
	}
	Location m_location;
	uint32_t m_bufferId;
	string m_folder;
	string m_fileName;
	uint32_t m_index{1};
	string m_extension;
	uint32_t m_fileSize;		// in MB

	string m_log;

	/*
	 * Information for the ring buffer
	 */
	uint16_t m_numberOfFile{1};
	bool m_isRingBuffer{false};

};

class Memory{

public:

	enum class Location{
		EEPROM = 0x01,
		FLASH = 0x02,
		SD = 0x03
	};

	Memory(Location location, uint64_t id, uint32_t size):
		m_location(location), m_id(id), m_size(size){

	}
	~Memory(){};

protected:
	Location m_location;
	uint64_t m_id;
	uint32_t m_size;



};


class FileSys{

public:
	FileSys(){};
	~FileSys(){};


private:
	vector<FileObject> m_files;
	uint32_t m_numberOfFile = 1;
	bool m_isRingBuffer;
	uint32_t m_readIndex;
	uint32_t m_writeIndex;

};

class MemoryManager{

public:
	FileObject* m_file;
	void init();

	void save(FileObject* file);
	void restore(FileObject* file);

};



#endif /* MEMORYMANAGER_MEMORYMANAGER_H_ */
