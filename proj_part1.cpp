// Export file content.cpp : Defines the entry point for the console application.
//

/*
1- apenas devem ser guardadas no ficheiro resultante as PALAVRAS SIMPLES, isto é, constituídas por letras ('A'-'Z');
2- entradas como AARD-VARK, AARON'S ROD e ATELETS SAUCE devem ser totalmente ignoradas, isto é,
nenhuma das palavras deve ser tida em conta porque surgirão certamente como palavras/entradas isoladas;
3- pode acontecer que haja entradas ("headlines") que ocupem mais do que uma linha, como acontece,
com "CONSOLATION GAME; CONSOLATION MATCH; CONSOLATION POT; CONSOLATION RACE" em que a palavra RACE aparece isolada numa linha;
neste caso não há problema em considerar a palavra RACE, a qual voltará a aparecer nas entradas que começam por "R" mas,
no final, será considerada apenas uma vez, quando forem eliminadas as palavras repetidas.
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

bool validLine(string &line); // Prototipo validLine
void extractWords(string &line, vector<string> &vectorAux);
bool validWord(string &word);
void allocateWord(string &word, vector<string> &vectorAux);

int main()
{
	string inputFile_name, outputFile_name; // Inicializacao das strings (nomes de ficheiros)

	cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
	cout << "=======================================" << endl << endl;

	cout << "Dictionary File ? "; // ficheiro de input
	cin >> inputFile_name;

	ifstream infile;
	infile.open(inputFile_name); // Abre ficheiro de input

	if (!infile.is_open()) // Se o ficheiro de input nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}

	cout << "Word list file ? "; // ficheiro de output
	cin >> outputFile_name;

	ofstream outfile;
	outfile.open(outputFile_name); // Abre ficheiro de output

	if (!outfile.is_open()) // Se o ficheiro de output nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}
	
	string s;
	vector<string> wordsAux;
	while (!infile.eof())
	{
		getline(infile, s);
		if (validLine(s))
		{
			extractWords(s, wordsAux);
		}
	}
	
	infile.close();
	outfile.close();

	return 0;
}

bool validLine(string &line) // Penso que esta tudo bem aqui :)
{
	int letter;
	bool valid_Line = false; // mudei o nome da variavel porque os alunos mais velhos disseram que pode causar erros se for igual ao nome da funcao
	for (size_t i = 0; i < line.length(); i++)
	{
		letter = line[i];
		if ((letter < 91 && letter > 64) || letter == 59 || letter == 39 || letter == 45 || letter == 32)   //Tests if char belongs in A-Z or is either ';' or ''' or '-' or 'space'
			valid_Line = true;
		else
		{
			valid_Line = false;
			break; // para logo o ciclo se vê que algum char nao esteja dentro da gama
		}
	}
	return valid_Line;
}

void extractWords(string &line, vector<string> &vectorAux) // Separa as palavras separadas por "; "
{
	int pos = 0; //posicao do primeiro char de cada word na string
	int index = 0;
	string word;
	while (!line.empty())
	{
		index = line.find_first_of(';', pos);
		if (index != -1) // CASO NAO TENHA NENHUM ";" find_first_of devolve -1, então a linha é de uma só palavra ou expressão
		{
			word = line.substr(pos, index); // substring entre o pos e o index
			pos = pos + index + 2; // pos fica com o numero da posicao do primeiro char da proxima word na line
			if (validWord(word))   // 2 e o espaco ocupado por "; "
				allocateWord(word, vectorAux);
			line = line.substr(pos);
			pos = 0;
		}
		else
		{
			if (validWord(line))
			{
				allocateWord(line, vectorAux);
			}
			break;
		}
	}
}

bool validWord(string &word) // Verifica se a palavra tem (space), ' ou -, se tiver a palavra nao e valida
{
	int letter;
	bool valid = true;
	for (int i = 0; i < word.length(); i++)
	{
		letter = word[i];
		if (letter == 32 || letter == 39 || letter == 45)   //(space), ', -
		{
			valid = false; // Palavra invalida
			break;
		}
	}
	return valid;
}

void allocateWord(string &word, vector<string> &vectorAux) // Alocar em vetor para se poder fazer sort e eliminar duplicadas
{
	cout << word << endl;
}

