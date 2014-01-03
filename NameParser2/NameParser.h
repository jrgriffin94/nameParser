#ifndef NAMEPARSER_H
#define NAMEPARSER_H

#include "Header.h"
#include "BST.h"

using namespace std;


class NameParser
{
private:
	BST<string> names;

public:
	NameParser();
	int parseFile(istream& in);
	bool printToFile(ostream& out);
};


#endif