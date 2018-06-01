#ifndef NGE_FILE_H
#define NGE_FILE_H

using namespace std;

#include "NGE_Master.h"

#include <string>
#include <fstream>

class NGE_File
{
private:
	bool fileOpen;
	bool newline;
	string filename;
	string seperator;

public:
	NGE_File();
	NGE_File(string file);
	int openFile(string file);
	int closeFile();
	int createFile(string file, bool openFile);
	int deleteFile();
	int wipeFile();
	int setSeperator(string seperator);
	string getSeperator();
	bool doesFileExist(string file);
	int linesInFile();
	int itemsInLine(int line);
	int appendInt(int data, bool newLine);
	int appendDouble(double data, bool newLine);
	int appendString(string data, bool newLine);
	int readInt(int line, int item);
	int readDouble(int line, int item);
	int readString(int line, int item);
};

#endif