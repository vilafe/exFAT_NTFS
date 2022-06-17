#include "main.h"
#include "Unit2.h"

HANDLE  createFileHandler(const WCHAR* file_name) {

    HANDLE fileHandler = CreateFileW(
        file_name,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandler == INVALID_HANDLE_VALUE) {
        std::cerr << "Error handle for PhysicalDrive." << std::endl;
        CloseHandle(fileHandler);
        system("PAUSE");
        exit(EXIT_FAILURE);
    }

    return fileHandler;
}

void    setHandlerPosition(HANDLE& fileHandler, UINT32 offset) {
    LARGE_INTEGER cursor;
    cursor.QuadPart = offset;
    );

    if (position != cursor.LowPart) {
        std::cerr << "Error in file handler. Exit." << std::endl;
        CloseHandle(fileHandler);
        system("PAUSE");
        exit(EXIT_FAILURE);
    }
}

void log(char* log) {
	ofstream fout("log.txt", ios::app);
	fout << log << std::endl;
	fout.close();
}

