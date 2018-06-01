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
