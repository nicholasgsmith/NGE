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
	if (doesFileExist(file) && !fileOpen)
	{
		filename = file;
		fileOpen = true;

		ifstream reader(filename);
		string line = "";
		string currentItem = "";
		signed int i = 0, j = 0, k = 0;

		while (getline(reader, line, '\n'))
		{
			fileContents.push_back(vector<string>());
			int limit = line.size() - endSeperator.size();

			for (j = startSeperator.size(); j < limit; j++)
			{	
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
				if (k == seperator.size())
				{
					fileContents[i].push_back(currentItem);
					currentItem = "";
					j += k - 1;
					k = 0;
				}
				else
				{
					currentItem = currentItem + line.at(j);
				}
			}
			if (line.size() != 0)
			{
				fileContents[i].push_back(currentItem);
			}
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
		ofstream saver(filename);
		int lines = linesInFile();

		for (int i = 0; i < lines; i++)
		{
			if (fileContents[i].size() > 0)
			{
				saver << startSeperator;
				for (int j = 0; j != fileContents[i].size(); j++)
				{
					saver << fileContents[i][j];
					if (j + 1 != fileContents[i].size())
					{
						saver << seperator;
					}
				}
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
	if (!doesFileExist(file))
	{
		ofstream createFile(file);
		createFile.close();

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
		fileContents.push_back(vector<string>());
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::readString(string& data, int lineNumber, int itemNumber)
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

int NGE_File::appendString(string data, int lineNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile())
		{
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

int NGE_File::editString(string data, int lineNumber, int itemNumber)
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

int NGE_File::deleteString(int lineNumber, int itemNumber)
{
	if (fileOpen)
	{
		if (lineNumber >= 0 && lineNumber < linesInFile() && itemNumber >= 0 && itemNumber < itemsInLine(lineNumber))
		{
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

