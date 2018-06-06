#include "NGE_File.h"
using namespace std;

#include "NGE.h"

using namespace std;

NGE_File::NGE_File()
{
	fileOpen = false;
	newline = true;
	filename = "";
	seperator = "\",\"";
	startSeperator = "\"";
	endSeperator = "\"";
}

NGE_File::NGE_File(string file)
{
	NGE_File();

	//Opens the file if it exists, or creates it and then opens it otherwise
	if (doesFileExist(file))
	{
		openFile(file);
	}
	else
	{
		createFile(file, true);
	}
}

int NGE_File::openFile(string file)
{
	//You can only open the file if it exists and a file is not already open
	if (doesFileExist(file) && !fileOpen)
	{
		//Record that the file is open and its path
		filename = file;
		fileOpen = true;

		ifstream reader(filename);
		string line = "";
		string currentItem = "";
		int i = 0, j = 0, k = 0;

		//Loop through and load each line of the file
		while (getline(reader, line, '\n'))
		{
			//Create a new vector for each lines items
			fileContents.push_back(vector<string>());

			//The limit that which upon reaching e dont need to check any more characters in the line
			int limit = line.size() - endSeperator.size();

			//Go through each character, ignoring the start and end characters
			for (j = startSeperator.size(); j < limit; j++)
			{	
				//If possible, check if the next sequence of characters starting from the current one are a seperator
				if (j + seperator.size() < line.size())
				{
					for (k = 0; k < seperator.size(); k++)
					{
						if (line.at(j + k) != seperator.at(k))
						{
							break;
						}
					}
				}
				//This will be true if the current character is the start of a seperator
				if (k == seperator.size())
				{
					//Add the current item to the item list and reset the item recorder
					fileContents[i].push_back(currentItem);
					currentItem = "";
					//Ignore the characters that make up the seperator
					j += k - 1;
				}
				else
				{
					//If the current character is not part of a seperator ass it to the current item recording
					currentItem = currentItem + line.at(j);
				}
			}
			//At the end of a line we need to add the final item, as it wasnt recorded before since it doesnt end in a seperator
			//The exception to this is if the line size if 0, in which case it was an emepty line and we add nothing
			//We can just check if the currentitem is "" as an item may be the empty string
			if (line.size() != 0)
			{
				fileContents[i].push_back(currentItem);
			}
			//Reset for the next line
			currentItem = "";
			i++;
		}

		reader.close();

		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::saveFile()
{
	if (fileOpen)
	{
		//Wipe the file so we can re-add all the information
		wipeFile();

		ofstream saver(filename);
		int lines = linesInFile();

		//Go through each line
		for (int i = 0; i < lines; i++)
		{
			//Check that there is at least 1 item in the line
			//If there isnt, we dont include the start and stop seperators
			if (fileContents[i].size() > 0)
			{
				//Add the start seperator
				saver << startSeperator;
				//Add each item to the file
				for (int j = 0; j != fileContents[i].size(); j++)
				{
					saver << fileContents[i][j];
					//If athe item is no the final item, add a seperator after it
					if (j + 1 != fileContents[i].size())
					{
						saver << seperator;
					}
				}
				//Add the stop seperator
				saver << endSeperator;
			}
			saver << '\n';
		}

		saver.close();
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::closeFile()
{
	if (fileOpen)
	{
		filename = "";
		fileOpen = false;
		fileContents.clear();
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::createFile(string file, bool openFile)
{
	//Only create the file if it doesnt already exist
	if (!doesFileExist(file))
	{
		ofstream createFile(file);
		createFile.close();

		//Open the file for editing as well if requested
		if (openFile)
		{
			this->openFile(file);
		}

		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::deleteFile()
{
	if (fileOpen)
	{
		remove(filename.c_str());
		closeFile();
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::wipeFile()
{
	if (fileOpen)
	{
		//To wipre the file we just delete and then recreate it
		deleteFile();
		createFile(filename, true);
		return 0;
	}
	else
	{
		return -1;
	}
}

string NGE_File::getSeperator()
{
	return seperator;
}

bool NGE_File::doesFileExist(string file)
{
	ifstream canOpen(file);
	if (!canOpen)
	{
		canOpen.close();
		return false;
	}
	else
	{
		canOpen.close();
		return true;
	}
}

int NGE_File::linesInFile()
{
	if (fileOpen)
	{
		return fileContents.size();
	}
	else
	{
		return -1;
	}
}

int NGE_File::itemsInLine(int lineNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile())
		{
			return fileContents[lineNumber].size();
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
}

int NGE_File::addNewline()
{
	if (fileOpen)
	{
		//To add a new line we add a blank vector to out file contenst vector
		fileContents.push_back(vector<string>());
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::readItem(string& data, int lineNumber, int itemNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile() && itemNumber >= 0 && itemNumber < itemsInLine(lineNumber))
		{
			data = fileContents[lineNumber][itemNumber];
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
}

int NGE_File::appendItem(string data, int lineNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile())
		{
			//To add a new item just append a new string to the vector corresponding to the line
			fileContents[lineNumber].push_back(data);
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
}

int NGE_File::editItem(string data, int lineNumber, int itemNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile() && itemNumber >= 0 && itemNumber < itemsInLine(lineNumber))
		{
			fileContents[lineNumber][itemNumber] = data;
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
}

int NGE_File::deleteItem(int lineNumber, int itemNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile() && itemNumber >= 0 && itemNumber < itemsInLine(lineNumber))
		{
			//We erase an element of the lines vector to delete an item
			fileContents[lineNumber].erase(fileContents[lineNumber].begin() + itemNumber);
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
}

int NGE_File::deleteLine(int lineNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile())
		{
			//We delete the vector corresponding to a line to delete the lines
			fileContents.erase(fileContents.begin() + lineNumber);
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -2;
	}
}

