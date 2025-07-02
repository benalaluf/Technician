#pragma once

#include <string>
#include <vector>

typedef struct _UploadFileHeader {
    size_t filePathSize;
    size_t fileSize;
} UploadFileHeader;


void upload(char* &data);

void writeToFile(std::string path, char* data, size_t dataSize);
    
