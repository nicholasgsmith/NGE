#include "NGE_File.h"
using namespace std;

#include "NGE.h"

using namespace std;

NGE_File::NGE_File()
{
	fileOpen = false;
	newline = true;
	filename = "";
	seperator = "";
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
	if (doesFileExist(file))
	{
		filename = file;
		fileOpen = true;
		return 0;
	}
	else
	{
		return -1;
	}
}

int NGE_File::saveFile()
{
	return 0;
}

int NGE_File::closeFile()
{
	if (fileOpen)
	{
		filename = "";
		fileOpen = false;
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

int NGE_File::setSeperator(string seperator)
{
	this->seperator = seperator;
	return 0;
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
		int lines = 0;

		string line;
		ifstream counter(filename);
		while (!counter.eof())
		{
			lines++;
			getline(counter, line, '\n');
		}
		counter.close();
		return lines;
	}
	else
	{
		return -1;
	}
}

int NGE_File::itemsInLine(int lineNumber)
{
	if (lineNumber <= 0 || lineNumber > linesInFile() || !fileOpen)
	{
		return -1;
	}
	else
	{
		ifstream reader(filename);
		string line;

		for (int i = 1; i <= lineNumber; i++)
		{
			string line;
			getline(reader, line, '\n');
		}
		reader.close();

		int items = 1;
		int i = 0, j = 0;

		for (i = 0; i != line.size(); i++)
		{
			for (j = 0; j != seperator.size(); j++)
			{
				if (line.at(i+j) != seperator.at(j))
				{
					break;
				}
			}
			if (j == seperator.size())
			{
				items++;
				i += j-1;
			}
		}

		return items;
	}
	return -1;
}

int NGE_File::readString(string& data, int lineNumber, int itemNumber)
{
	return 0;
}

