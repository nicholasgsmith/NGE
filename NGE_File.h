#ifndef NGE_FILE_H
#define NGE_FILE_H

using namespace std;

#include "NGE_Master.h"

#include <string>
#include <fstream>
#include <vector>

class NGE_File
{
private:
	bool fileOpen;
	bool newline;
	string filename;
	string seperator;
	string startSeperator;
	string endSeperator;
	vector< vector <string> > fileContents;

public:
	NGE_File();
	NGE_File(string file);
	int openFile(string file);
	int saveFile();
	int closeFile();
	int createFile(string file, bool openFile);
	int deleteFile();
	int wipeFile();
	string getSeperator();
	bool doesFileExist(string file);

	int linesInFile();
	int itemsInLine(int line);

	int addNewline();
	int appendItem(string data, int lineNumber);
	int readItem(string& data, int lineNumber, int itemNumber);
	int editItem(string data, int lineNumber, int itemNumber);
	int deleteItem(int lineNumber, int itemNumber);
	int deleteLine(int lineNumber);
};

#endif