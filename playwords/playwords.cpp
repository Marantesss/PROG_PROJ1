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
void wordFinder(vector<string> &wordVector); //Recebe N letras e imprime as palavras que e possivel formar com as N-letras
bool matching(string const userLetters, string const vectorWord);


int main()
{ 
	string wordFile = "C:\\Users\\tiago\\Desktop\\PROG_PROJ1\\29765-8_w.txt"; //"29765-8_w.txt"; // Colocar diretorio!!! 
	ifstream file;
	vector<string> wordVector;

	file.open(wordFile);

	if (!file.is_open()) // Se o ficheiro de input nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}
	
	while (!file.eof())      // Extracao de palavras para vetor 
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
		break;
	case 2 :
		wordScramble(wordVector);
		break;
	case 3 :
		wordFinder(wordVector);
		break;
	case 4 :
		//...
		break;
	case 5 :
		//...
		break;
	}
}

void wordBelong(vector<string> &wordVector) // Ver se palavra pertence a lista
{
	string word;

	cout << "Enter a word..." << endl;  
	cin >> word;

	bool isInFile = false;
	int position = 0;

	for (unsigned i = 0; i < wordVector.size(); i++)    // Percorrer o vetor 
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

void wordFinder(vector<string> &wordVector)
{
	string userLetters;
	vector<string> auxVector;

	cout << "Enter a N set of letters: ";
	cin >> userLetters;

	if (cin.fail())
		cerr << endl << "Invalid entry" << endl;

	for (unsigned int i = 0; i < wordVector.size(); i++) //Acede a todas as palavras do dicionario(alocadas no vetor)
	{
		if (matching(userLetters, wordVector[i]))   // Se match = true entao coloca a palavra em auxVector
			auxVector.push_back(wordVector[i]);
	}

	if (auxVector.size() == 0)
		cout << endl << "No words can be written using those letters :(" << endl;
	else
		for (unsigned int i = 0; i < auxVector.size(); i++)
			cout << auxVector[i] << endl;

}

bool matching(string const userLetters, string const vectorWord) // Devolve true se as letras da palavra do vetor estiverem todas nas letras inseridas pelo utilizador... false em caso contrario
{
	bool wordMatch = true;
	if (userLetters.length() > vectorWord.length())
		wordMatch = false;
	for (unsigned int i = 0; i < vectorWord.length(); i++)  // 
	{
		bool letterMatch = false;
		for (unsigned int j = 0; j < userLetters.length(); j++) // Se a letra [i] da palvra do vetor estiver em userLetters letterMatch = true
			if (vectorWord[i] == userLetters[j])
			{
				letterMatch = true;
				break;
			}
		if (!letterMatch)   // Se alguma das letras da palavra do vetor nao estiver em userLetters, interrompe o ciclo e sai com match a devolver false
		{
			wordMatch = false;
			break;
		}
	}
	return wordMatch;
}