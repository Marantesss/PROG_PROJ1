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

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;

bool validLine(string &line); // Verifica se a linha 'line' e valida
int extractWords(string &line, vector<string> &vectorAux); // Separa as palavras separadas por "; "  e retorna o numero de palavras extraidas
bool validWord(string &word); // Verifica se a palavra tem (space), ' ou -, se tiver a palavra nao e valida
void allocateWord(string &word, vector<string> &vectorAux); // Coloca a palavra num vetor auxiliar
vector<string> wordOrganizer(vector<string> &vectorAux); // Organiza o vetor auxiliar

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

	cout << endl << "Extracting words from " << inputFile_name << endl << "Beginning with letter..." << endl;

	string s;
	vector<string> wordsAux;
	int numberOfStoredWords = 0;
	int letter = 65; // Codigo ASCII letra A
	
	cout << endl << 'A' << endl;

	while (!infile.eof())
	{
		getline(infile, s);
		if (validLine(s))
		{
			numberOfStoredWords += extractWords(s, wordsAux);
			if ((int)s[0] < 91 && (int)s[0] > 64) // Primeiro char da string esta entre A-Z
			{
				if ((letter + 1) == (int)s[0]) // Verifica se o char da linha e igual ao proximo char da variavel letter
				{
					letter = s[0];
					cout << endl << s[0] << endl;
				}

				if (numberOfStoredWords % 100 == 0) // Escreve um ponto de 100 em 100 palavras extraidas
					cout << ".";
			}
		}
	}

	cout << endl << "Number of simple words = " << numberOfStoredWords << endl;

	vector<string> organizedWords = wordOrganizer(wordsAux); // Vetor final organizado e sem palavras repetidas

	int numberOfCleanWords = organizedWords.size(); // numero de palavras organizadas e nao duplicadas

	cout << "Number os non-duplicate simple words = " << numberOfCleanWords << endl;
	cout << "Saving words into file " << outputFile_name << " ..." << endl;

	for (size_t i = 0; i < organizedWords.size(); i++) //escreve as palavras no ficheiro output separadas por paragrafo
	{
		outfile << organizedWords[i] << endl;
	}

	infile.close();< endl;

	return 0;
}


bool validLine(string &line) // Verifica se a linha 's' e valida
{
	int letter; // codigo ASCII dos chars
	bool valid_Line = false; // variavel de retorno
	for (size_t i = 0; i < l
	outfile.close();

	cout << "End of processing." <ine.length(); i++)
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

int extractWords(string &line, vector<string> &vectorAux) // Separa as palavras separadas por "; "  e retorna o numero de palavras extraidas 
{
	int numberOfExtractedWords = 0;
	int pos = 0; //posicao do primeiro char de cada word na string
	int index = 0;
	string word;
	
	if (line[line.length() - 1] == ';')					// SE A LINHA ACABAR EM ; PEGA NELE E REMOVE-O :)
		line = line.substr(0, line.length() - 1);
	
	while (!line.empty())
	{
		index = line.find_first_of(';', pos);
		if (index != -1) // CASO NAO TENHA NENHUM ";" find_first_of devolve -1 (npos) , então a linha só contém uma palavra ou expressão
		{
			word = line.substr(pos, index); // substring entre o pos e o index
			pos = pos + index + 2; // pos fica com o numero da posicao do primeiro char da proxima word na line
			if (validWord(word))   // 2 e o espaco ocupado por "; "
				allocateWord(word, vectorAux);
			line = line.substr(pos);  // Uma line p.e. CONSOLATION GAME; CONSOLATION MATCH; CONSOLATION POT  torna-se   CONSOLATION MATCH; CONSOLATION POT
			pos = 0;
			numberOfExtractedWords++;
		}
		else
		{
			if (validWord(line))
			{
				allocateWord(line, vectorAux);
				numberOfExtractedWords++;
			}
			break;
		}
	}

	return numberOfExtractedWords;
}

bool validWord(string &word) // Verifica se a palavra tem (space), ' ou -, se tiver a palavra nao e valida
{
	if ((int)word[word.length() - 1] == 32) // Se a palavra acabar em (space) palavra com erro - ALFA
	{
		word = word.substr(0, word.length() - 1);
	}
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
	vectorAux.push_back(word);
	// cout << word << " "; TESTE (FUNCIONA)
}

vector<string> wordOrganizer(vector<string> &vectorAux) // Organiza o vetor auxiliar
{
	vector<string> organizedWords;
	string word, next;

	cout << "Sorting words ..." << endl;
	sort(vectorAux.begin(), vectorAux.end()); // Coloca as palavras por ordem alfabetica

	cout << "Removing duplicate words ..." << endl;

	for (size_t i = 0; i < vectorAux.size(); i++) // Escolhe uma palavra e ve se a que esta a frente é igual, se for passa para a proxima, se nao for escreve no novo vetor
	{
		word = vectorAux[i];
		if (word == vectorAux[vectorAux.size() - 1]) // Verifica se e a ultima string do vetor
		{
			organizedWords.push_back(word);
			break;
		}
		next = vectorAux[i + 1];
		
		if (word != next) // Apenas escreve se a string i se a string i+1 for diferente
		{
			organizedWords.push_back(word);
		}
	}

	return organizedWords;
}