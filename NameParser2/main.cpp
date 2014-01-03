
#include "NameParser.h"


int main()
{
	int nameCount = 0;
	int totalNames = 0;
	double loopTime = 0;
	double totalTime = 0;
	NameParser np;
	stringstream sstrm;
	ofstream myFile;
	ofstream dataFile;
	string currFile;
	myFile.open("FullNameList.txt");
	dataFile.open("dataFile.txt");

	dataFile << "Current File"
		<< ',' << "Names in Current File"
		<< ',' << "Time Taken for Parse" << endl;

	totalTime = clock();

	for (int i = 1880; i <= 2012; i++)
	{
		loopTime = clock();
		sstrm.str(std::string());

		sstrm << "yob" << i << ".txt";

		currFile = sstrm.str();

		ifstream in(currFile);
		nameCount = np.parseFile(in);
		totalNames += nameCount;

		loopTime = clock() - loopTime;

		cout << "Finished: " << currFile
			<< "\t\tParse Time: " << fixed << setprecision(2)
			<< loopTime / 1000 << "s" 
			<< endl;

		dataFile << currFile
			<< ',' << nameCount
			<< ',' << loopTime << endl;
	}

	dataFile << endl << "Total Time: "
		<< fixed << setprecision(2)
		<< (clock() - totalTime) / 1000
		<< "s" << endl
		<< "Total Names Parsed: " << totalNames << endl;

	np.printToFile(myFile);

	return 0;
}

