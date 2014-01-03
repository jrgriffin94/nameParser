
#include "NameParser.h"


NameParser::NameParser() : names()
{}


int NameParser::parseFile(istream& in)
{
	string name = "";
	int num = 0;

	while (!in.eof() && !in.fail())
	{
		getline(in, name, ',');
		in.ignore(200, '\n');

		if (name == "") break;

		names.insert(name);

		num++;
	}

	return num;
}


bool NameParser::printToFile(ostream& out)
{
	names.inorderDisplay(out);

	return true;
}
