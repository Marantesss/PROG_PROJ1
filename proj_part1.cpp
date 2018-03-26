// Export file content.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

void readLine(ifstream &inFile); // Prototipo readLine
bool validLine(string &line); // Prototipo validLine

using namespace std;

int main()
{
	string inputFile_name, outputFile_name;

	cout << "Enter the input file..." << endl;
	cin >> inputFile_name;

	ifstream infile;
	infile.open(inputFile_name);

	if (!infile.is_open())
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}

	readLine(infile);


	cout << "Enter the output file..." << endl;
	cin >> outputFile_name;

	ofstream outfile;


	return 0;
}

void readLine(ifstream &inFile)
{
	string s;
	while (!inFile.eof())
	{
		getline(inFile, s);
		// cout << s << endl; So um teste para ver se dava 
		if (validLine(s))   // Se validLine =  true ----> processar a linha; Else passar para  a proxima 
		{

		}
	}
}

bool validLine(string &line)
{
	int letter;
	bool validLine = false;
	for (size_t i = 0; i < line.length(); i++)
	{
		letter = line[i];
		if ((letter < 91 && letter > 64) || letter == 59 || letter == 39 || letter == 45)   //Tests if char belongs in A-Z or is either ';' , ''' or '-'.... Condicoes complexas... Erro provavel
			validLine = true;
		else
		{
			validLine = false;      // Breaks se um char não pertencer ao grupo acima 
			break;
		}
	}
	return validLine;
}




