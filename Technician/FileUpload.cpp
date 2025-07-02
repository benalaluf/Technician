#include "Upload.h"

#include <iostream>
#include <Windows.h>

void upload(char* &data) {
    UploadFileHeader *header = reinterpret_cast<UploadFileHeader*>(data);
    std::string filePath = data + sizeof UploadFileHeader;
    filePath = filePath.substr(0, header->filePathSize-1);
    char* fileData = data + sizeof UploadFileHeader + header->filePathSize;

    writeToFile(filePath, fileData, header->fileSize);
    std::cout << "Wrote to file : " << filePath << "\n";
    
}

void writeToFile(std::string path, char* data, size_t dataSize) {
    HANDLE hFile = CreateFileA(path.c_str(), (GENERIC_READ | GENERIC_WRITE), 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL) {
        std::cout << "Faile to get fiel handle\n";
    }

    BOOL result = WriteFile(hFile, data, dataSize, NULL, NULL);
    std::cout << "WriteFile: " << result << GetLastError() <<"\n";
}

