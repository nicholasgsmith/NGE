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
	//Creates a new blank instance for file manipulation
	NGE_File();

	//Creates a new instance for file manipulation and loads the given file into it
	//If the file does not exist it creates it first before loading it
	NGE_File(string file);

	//Opens a file for manipulation
	//This does not edit the contents of the file
	//All methods which do not take a file but edit a files contents require this function to be called beforehand 
	int openFile(string file);

	//Saves the current file which was loaded using openFile
	//Any changes are saved as well
	//This does not close the file, you can continue to edit it without re-opening it
	int saveFile();

	//Closes the currently open file
	//This does not save changes, saveFile shoudl be called beforehand unless you dont want changes saved
	int closeFile();

	//Creates a new blank file
	//Also opens the file if requested
	int createFile(string file, bool openFile);

	//Deletes the currently open file
	//Also closes it
	int deleteFile();

	//Wipes the contents of a file
	//This does not close the file
	int wipeFile();

	//Returns what is currently being used as the seperator in files
	string getSeperator();

	//Returns true if a file exists and false otherwise
	bool doesFileExist(string file);

	//Returns the number of the lines in the currently open file
	int linesInFile();

	//Returns the number of items in a given line
	int itemsInLine(int line);

	//Adds a new line to the file
	int addNewline();

	//Appends the given string as a new item to the end of a line
	//Returns -2 if a file is not open and -1 if your line does not exist
	int appendItem(string data, int lineNumber);

	//Appends the given string as a new item to the end of a line
	//Returns -2 if a file is not open and -1 if your line does not exist
	int readItem(string& data, int lineNumber, int itemNumber);

	//Edits the given item to the previded string
	//Returns -2 if a file is not open and -1 if your line or item does not exist
	int editItem(string data, int lineNumber, int itemNumber);

	//Deletes the given item
	//Returns -2 if a file is not open and -1 if your line or item does not exist
	int deleteItem(int lineNumber, int itemNumber);

	//Deletes the given line
	//Returns -2 if a file is not open and -1 if your line does not exist
	int deleteLine(int lineNumber);

};

#endif