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
		int lines = linesInFile();
		int i, j, k;

		for (i = 0; i < lines; i++)
		{
			getline(reader, line, '\n');

			for (j = 0; j != line.size(); j++)
			{
				for (k = 0; k != seperator.size(); k++)
				{
					if (line.at(j + k) != seperator.at(k))
					{
						break;
					}
				}
				if (k == seperator.size())
				{
					fileContents[i].push_back(currentItem);
					currentItem = "";
					j += k - 1;
				}
				else
				{
					currentItem = currentItem + line.at(j);
				}
			}
			fileContents[i].push_back(currentItem);
			currentItem = "";
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
			for (int j = 0; j != fileContents[i].size(); j++)
			{
				saver << fileContents[i][j];
				saver << seperator;
			}
			saver << "\n";
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
		saveFile();
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

