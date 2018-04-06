// playwords.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

void outInterface(vector<string> &wordVector); // Receber vetor para usar nas funcoes
void wordBelong(vector<string> &wordVector); // Ver se palavra pertence a lista
void wordScramble(vector<string> &wordVector); // Mistura letras e devolve uma poalavra com as letras trocadas

int main()
{ 
	string wordFile = "29765-8_w.txt"; // Colocar diretorio!!! 
	ifstream file;
	vector<string> wordVector;

	file.open(wordFile);

	if (!file.is_open()) // Se o ficheiro de input nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}
	
	while (!file.eof)      // Extracao de palavras para vetor 
	{
		string word;
		getline(file, word);
		wordVector.push_back(word);
	}
	
	outInterface(wordVector);  // Funcao de interface
	
    return 0;
}

void outInterface(vector<string> &wordVector) // Receber vetor para usar nas funcoes
{
	int funct;
	
	cout << "Choose between these..." << endl;

	cout << "1 - Find if word is in the file" << endl;
	cout << "2 - Word Scramble" << endl;
	cout << "3 - Words that can be written with the chosen letters" << endl;
	cout << "4 - Build a word with randomly chosen letters" << endl;
	cout << "5 - Wildcard words" << endl;

	cin >> funct;  // Escolher funcao
	
	switch (funct)
	{
	case 1 :
		wordBelong(wordVector);
	case 2 :
		wordScramble(wordVector);
	case 3 :
		//...
	case 4 :
		//...
	case 5 :
		//...
	}
}

void wordBelong(vector<string> &wordVector) // Ver se palavra pertence a lista
{
	string word;

	cout << "Enter a word..." << endl;  
	cin >> word;

	bool isInFile = false;
	int position = 0;

	for (int i = 0; i < wordVector.size(); i++)    // Percorrer o vetor 
	{

		if (word == wordVector[i])  // Se a palavra for igual a do vetor break com isInFile = true 
		{
			isInFile = true;
			position = i + 1; // Posicao da palavra no vetor
			break;
		}
	}

	if (isInFile)
		cout << "The word is in the file, position no. " << position << endl;  // Se isInFile == true  faz o cout
	else
		cout << "The word is not in the file" << endl;  // Else ....
}

void wordScramble(vector<string> &wordVector)
{

}
