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

	int addNewline();
	int appendInt(int data, int lineNumber);
	int appendDouble(double data, int lineNumber);
	int appendString(string data, int lineNumber);

	int readInt(int line, int item);
	int readDouble(int line, int item);
	int readString(int line, int item);
};

#endif