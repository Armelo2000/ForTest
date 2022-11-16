/*
 * MemoryManager.cpp
 *
 *  Created on: 14.11.2022
 *      Author: melah
 */

#include "MemoryManager.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <filesystem>

namespace fs = std::filesystem;

void MemoryManager::init(){
	m_file = new FileObject(FileObject::Location::SD,
							1,
							"Logs",
							"log",
							"txt",
							1 /* 10KB */,
							4);
	if(m_file != nullptr)
	m_file->m_log = "Das ist nur ein Test\n";
}
void MemoryManager::save(FileObject* file){

	if(file != nullptr){
		auto p = "C:\\Users\\melah\\Downloads\\" + file->m_folder;
		auto f = p + "\\" + file->m_fileName + "_" + to_string(file->m_index) + "." + file->m_extension;
		const fs::path dir{p};
		ofstream oFile;
		if(fs::exists(dir)){
			const fs::path dirFile{f};
			if(fs::exists(dirFile)){
				//Check the size;
				if(fs::file_size(f) < file->m_fileSize){
					oFile.open(f, ios::app);
					// write to file
					oFile << m_file->m_log;

					oFile.close();
				}else{
					//size is exceeded
					if(m_file->m_isRingBuffer){
						if(m_file->m_index < m_file->m_numberOfFile){
							m_file->m_index++;
							f = p + "\\" + file->m_fileName + "_" + to_string(file->m_index) + "." + file->m_extension;
							oFile.open(f);
							// write to file
							oFile << m_file->m_log;

							oFile.close();

						}else{
							//override or delete the last created file
							uint32_t lastIndex = m_file->m_index - m_file->m_numberOfFile + 1;
							m_file->m_index++;
							f = p + "\\" + file->m_fileName + "_" + to_string(lastIndex) + "." + file->m_extension;
							fs::remove(f);
							f = p + "\\" + file->m_fileName + "_" + to_string(m_file->m_index) + "." + file->m_extension;
							oFile.open(f);
							// write to file
							oFile << m_file->m_log;

							oFile.close();

						}
					}
				}
			}else{
				//file do not exist
				//create and write to it
				oFile.open(f);
				// write to file
				oFile << m_file->m_log;

				oFile.close();
			}



		}else{
			fs::create_directories(dir);

			oFile.open(f);
			// write to file
			oFile << m_file->m_log;

			oFile.close();
		}


	}

}

void MemoryManager::restore(FileObject* file){

}
