// playwords.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>
#include <math.h>
#include <cstring>
#include <iomanip>


using namespace std;

void outInterface(vector<string> wordVector); // Receber vetor para usar nas funcoes
void wordBelong(vector<string> wordVector); // Ver se palavra pertence a lista
void wordScramble(vector<string> wordVector); // Mistura letras e devolve uma palavra com as letras trocadas
void wordConstructor(vector<string> wordVector); //Recebe N letras e imprime as palavras que e possivel formar com as N-letras
bool matching(string const userLetters, string const vectorWord);
void buildWordFromSet(vector<string> wordVector); // O programa manda N letras a sorte, e o utilizador tem que construir uma palavra com essas letras
vector<char> buildLargerSet(vector<string> wordVector); // Constroi o vetor com chars diretamente proporcionais ao char com menos ocorrencias
void wildcard(vector<string> wordVector); // Percorre todas as palavras no vetor e verifica se há alguma que se possa escrever sem os wildcard characters
bool wildcardMatch(const char *str, const char *strWild); // Wildcard match

int main()
{ 
	string wordFile; // = "C:\\Users\\gonca\\Documents\\GitHub\\proj_part1\\proj_part1\\29765-8_w.txt"; "29765-8_w.txt";  Colocar diretorio
	// DIRETORIO DO MARANTES ===> C:\\Users\\gonca\\Documents\\GitHub\\proj_part1\\proj_part1\\29765-8_w.txt
	// DIRETORIO DO TIAGO ===> C:\\Users\\tiago\\Desktop\\PROG_PROJ1\\29765-8_w.txt
	ifstream file;
	vector<string> wordVector;

	cout << "Enter the directory of the word file to use ";
	cin >> wordFile;

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
	wordVector.pop_back(); // Apaga o ultimo elemento que é um paragrafo
	
	outInterface(wordVector);  // Funcao de interface
	
    return 0;
}

void outInterface(vector<string> wordVector) // Receber vetor para usar nas funcoes
{
	int funct = -1;
	while (funct != 0)
	{
		cout << "================== MENU ==================" << endl; // 18 iguais de cada lado
		cout << setw(4) << "Choose between these..." << endl << endl;

		cout << " || 1 - Find if word is in the file" << setw(24) << "||" << endl;
		cout << " || 2 - Word Scramble" << setw(38) << "||" << endl;
		cout << " || 3 - Words that can be written with the chosen letters" << setw(1) << "||" << endl;
		cout << " || 4 - Build a word with randomly chosen letters" << setw(10) << "||" << endl;
		cout << " || 5 - Wildcard words" << setw(37) << "||" << endl;
		cout << " || 0 - Close the program" << setw(34) << "||" << endl << endl;

		cin >> funct; // Escolher funcao
		cin.clear(); // Limpa a error flag de cin 
		cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros

		if (funct != 0 && funct != 1 && funct != 2 && funct != 3 && funct != 4 && funct != 5) // Evitar entrada invalida na selecao de funcoes
			cout << "Not a valid option..." << endl;
		if (funct == 0 || funct == 1 || funct == 2 || funct == 3 || funct == 4 || funct == 5)
		{
			switch (funct) // Opcoes de selecao
			{
			case 1:
				wordBelong(wordVector);
				funct = -1;
				break;
			case 2:
				wordScramble(wordVector);
				funct = -1;
				break;
			case 3:
				wordConstructor(wordVector);
				funct = -1;
				break;
			case 4:
				buildWordFromSet(wordVector);
				funct = -1;
				break;
			case 5:
				wildcard(wordVector);
				funct = -1;
				break;
			}
		}
	}
}

void wordBelong(vector<string> wordVector) // Ver se palavra pertence a lista
{
	string word;
	char answer = 'Y';
	cout << endl << "-------------FIND-------------";
	
	do
	{
		cout << endl << "Enter a word..." << endl;
		cin >> word;
		cin.clear(); 
		cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros
		transform(word.begin(), word.end(), word.begin(), ::toupper); // Transforma a word em upper case

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
			cout << "The word " << word << " is in the file, position no. " << position << endl << endl;  // Se isInFile == true  faz o cout
		else
			cout << "The word " << word << " is not in the file \n \n";  // Else ....
		
		do
		{
			cout << "Would you like to try again?(Y/N) ";
			cin >> answer;
			cin.clear();
			cin.ignore(1000, '\n');
		} while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'); // Ciclo que força o user a responder (y/n)
	
	} while (answer == 'y' || answer == 'Y'); // Correr a funcao enquanto answer == 'y' ou answer == 'Y'
	cout << endl;
}

void wordScramble(vector<string> wordVector)
{
	char answer = 'Y';

	cout << endl << "-------------WORD SCRAMBLE-------------" << endl;
	do
	{
		const unsigned int vectorSize = wordVector.size(); //Tamanho do vetor
		random_device rd;     // only used once to initialise (seed) engine
		mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		uniform_int_distribution<int> uni(0, vectorSize - 1); // guaranteed unbiased

		auto randomIndex = uni(rng); // Numero aleatorio entre 0 e (vectorSize - 1) = 95902

		string word = wordVector[randomIndex]; // Palavra aleatorio do dicionario
		string scrambledWord = word; // Copia da word para ser scrambled

		int x = scrambledWord.length();
		for (int y = x; y > 0; y--) //
		{
			int pos = rand() % x;
			char tmp = scrambledWord[y - 1];
			scrambledWord[y - 1] = scrambledWord[pos];
			scrambledWord[pos] = tmp;
		}
		string guess; // Tentativa do utilizador
		int attempts = 3; // Numero de tentativas
		do
		{
			cout << scrambledWord << endl;
			cout << "Write your guess..." << endl;
			cout << "Remaining Attempts: " << attempts << endl; // mostra no numero de tentaivas restantes
			cin >> guess;
			cin.clear(); 
			cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros
			transform(guess.begin(), guess.end(), guess.begin(), ::toupper); // Transforma o guess em upper case

			if (guess == word)
			{
				cout << "Correct!" << endl << endl;
				break;
			}
			if (attempts > 1)
			{
				cout << "Try again..." << endl << endl;
			}
			else
			{
				cout << endl << "Max attempts reached..." << endl;
				cout << "Your word was: " << word << endl << endl;
			}
			attempts--;
		} while (attempts > 0);

		do
		{
			cout << "Would you like to try again?(Y/N) ";
			cin >> answer;
			cin.clear();
			cin.ignore(1000, '\n');
		} while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'); // Ciclo que força o user a responder (y/n)

	} while (answer == 'y' || answer == 'Y');  // Correr a funcao enquanto answer == 'y' ou answer == 'Y'
	cout << endl;
}

void wordConstructor(vector<string> wordVector)
{
	string userLetters;
	char answer = 'Y';

	cout << endl << "-------------WORD CONTRUCTOR-------------";
	do
	{
		vector<string> auxVector;

		cout << endl << "Enter a N set of letters(With no spaces; Ex. abc): ";
		cin >> userLetters;
		cin.clear(); // Limpa o buffer
		cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros
		transform(userLetters.begin(), userLetters.end(), userLetters.begin(), ::toupper);
		
		if (cin.fail())
			cerr << endl << "Invalid entry" << endl;

		for (unsigned int i = 0; i < wordVector.size(); i++) //Acede a todas as palavras do dicionario(alocadas no vetor)
		{
			if (matching(userLetters, wordVector[i]))   // Se match = true entao coloca a palavra em auxVector
				auxVector.push_back(wordVector[i]);
		}

		if (auxVector.size() == 0)
			cout << endl << "No words can be written using those letters..." << endl;
		else
		{
			cout << endl << "With the letters " << userLetters << " you can write:" << endl;
			for (unsigned int i = 0; i < auxVector.size(); i++)
				cout << " - " << auxVector[i] << endl;
			cout << endl;
		}

		do
		{
			cout << "Would you like to try again?(Y/N) ";
			cin >> answer;
			cin.clear();
			cin.ignore(1000, '\n');
		} while (answer != 'y' && answer != 'Y' && answer != 'n'&& answer != 'N'); // Ciclo que força o user a responder (y/n)

	} while (answer == 'y' || answer == 'Y'); // Correr a funcao enquanto answer == 'y' ou answer == 'Y'
	cout << endl;
}

bool matching(string const userLetters, string const vectorWord)
{
	/* Devolve:
	-true se as letras da palavra do vetor estiverem todas nas letras inseridas pelo utilizador e estas estiverem todas as ser utilizadas

	-false em caso contrario
	*/

	bool wordMatch = true;

	if (userLetters.length() > vectorWord.length())
		wordMatch = false;

	for (unsigned int i = 0; i < vectorWord.length(); i++)  // Verifica se as letras da palavra do dicionario estao nas letras do user
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
	for (unsigned int i = 0; i < userLetters.length(); i++)  // Verifica se todas as letras inseridas pelo user estão a ser utilzadas
		if (vectorWord.find_first_of(userLetters[i]) == -1)
			wordMatch = false;

	return wordMatch;
}

void buildWordFromSet(vector<string> wordVector)
{
	char answer = 'Y';

	cout << endl << "-------------WORD BUILDER-------------";
	do
	{
		vector<char> letterVector = buildLargerSet(wordVector); // Este vetor ira conter o set de letras que é proporcional ao numero de letras do vetor palavras
		vector<char> outputLetter;

		srand(time(NULL));
		int randomNumberOfLetters = (rand() % 20) + 0; // numero aleatorio entre 0 e 20
		
		cout << endl << "Write a word using at least one of the letters given..." << endl;
		
		while (randomNumberOfLetters > 0)
		{
			int randomIndex = (rand() % letterVector.size()); // Numero aleatorio entre 0 e o tamanho do vetor
			if (letterVector[randomIndex] != '*') // Se o char ainda nao tiver saido
			{
				cout << letterVector[randomIndex] << " "; // Faz output da letter
				outputLetter.push_back(letterVector[randomIndex]); // Coloca o char que saiu no vetor
				letterVector[randomIndex] = '*'; // Muda o char porque já saiu
				randomNumberOfLetters--;
			}
		}

		cout << endl;
		string guess;
		cin >> guess;
		cin.clear(); // Limpa o buffer
		cin.ignore(1000, '\n'); // Ignora tudo o que esta para a frente da palavra inicial para evitar erros

		bool validGuess = false;
		for (unsigned int i = 0; i < guess.size(); i++) // Ciclo que ve, char a char do guess, se alguma letra equivale a algum elemento do vetor que tem os chars aleatorios
		{
			char c = toupper(guess[i]); // Garante que o char retirado da palavra esta em letra maiuscula
			for (unsigned int k = 0; k < outputLetter.size(); k++)
			{
				if (c == outputLetter[k]) // se algum c for igual a algum elemento do vetor, o guess e valido
					validGuess = true;
			}
		}

		if (validGuess == true)
			cout << "Valid guess" << endl;
		else
			cout << "Not a valid guess" << endl;

		do
		{
			cout << endl << "Would you like to try again?(Y/N) ";
			cin >> answer;
			cin.clear();
			cin.ignore(1000, '\n');
		} while (answer != 'y' && answer != 'Y' && answer != 'n'&& answer != 'N'); // Ciclo que força o user a responder (y/n)

	} while (answer == 'y' || answer == 'Y'); // Correr a funcao enquanto answer == 'y' ou answer == 'Y'
	cout << endl;
}

vector<char> buildLargerSet(vector<string> wordVector) // Constroi o larger set a partir da proporcao: Letra com menos ocurrencias aparece 2 vezes no larger set
{
	vector<char> largerSet; // Vetor que ira ser retornado e contem todos os chars em numero proporcional ao numero total de chars do wordVector
	
	int count[26]; // Array onde vai ser guardado o numero de ocorrencias de cada char (26 - A a Z)

	for (int i = 0; i < 26; i++) // Ciclo que coloca a 0 todos os elementos do array
		count[i] = 0;
	
	for (unsigned int i = 0; i < wordVector.size(); i++) // Ciclo que percorre todas as palavras do vetor
	{
		string word = wordVector[i];
		for (unsigned int k = 0; k < word.length(); k++) // Ciclo que percorre todos os chars da palavra
		{
			count[(int)(word[k] - 'A')]++; // Incrementa consoante o char retirado
		}
	}

	int smallestIndex = 0;
	for (int i = 0; i < 26; i++) // Ciclo que encontra a posicao do char com menor numero de ocorrencias
		if (count[smallestIndex] > count[i])
			smallestIndex = i;

	char smallestChar = smallestIndex + 'A'; // char que ocorre menos vezes

	long countSum = 0;
	for (int i = 0; i < 26; i++) // Ciclo que soma todas as ocorrencias de todas as palavras
		countSum += count[i];

	double letterProportions[26]; // Array que contem a probabilidade de cada char sair
	for (int i = 0; i < 26; i++) // Ciclo que constroi a probabilidade de sair qualquer letra
		letterProportions[i] = (double)count[i] / countSum; // Tem que ser double senao fica tudo a 0 :(
	
	double directProportion = 2 / letterProportions[smallestIndex]; // Relacao de proporcionalidade direta
	for (int i = 0; i < 26; i++) // Ciclo que constroi o vetor com as probabilidades certas
	{
		int k = directProportion * letterProportions[i]; // numero de vezes que esse char vai aparecer no vetor, declarado int porque arredonda o numero de vezes que o char em questao ira aparecer no vetor
		while (k > 0)
		{
			largerSet.push_back(i + 'A'); // Soma-se 'A' porque o indice 0 corresponde ao char A, 1 corresponde ao char B, ...
			k--;
		}
	}
	return largerSet;
}

void wildcard(vector<string> wordVector)
{
	string wildcardWord;
	char answer = 'Y';
	
	cout << endl << "-------------WILDCARD-------------";
	do
	{
		cout << endl << "Enter a word with characters '?' or '*'..." << endl << "? - one character is missing" << endl << "* - zero or more characters are missing" << endl << "(EX. F?LL matches with FALL, FELL, FILL and FULL)" << endl;
		cin >> wildcardWord;
		bool match = false; // Variavel que muda para true se for encontada algum match


		for (unsigned int i = 0; i < wordVector.size(); i++)
		{
			if (wildcardMatch(wordVector[i].c_str(), wildcardWord.c_str()))
			{
				cout << wordVector[i] << endl;
				match = true;
			}
		}
		if (!match)
			cout << "The word does not match with any in the dictionary..." << endl;
		cout << endl;
		
		do
		{
			cout << "Would you like to try again?(Y/N) ";
			cin >> answer;
			cin.clear();
			cin.ignore(1000, '\n');
		} while (answer != 'y' && answer != 'Y' && answer != 'n'&& answer != 'N'); // Ciclo que força o user a responder (y/n)

	} while (answer == 'y' || answer == 'Y'); // Correr a funcao enquanto answer == 'y' ou answer == 'Y'
	cout << endl;
}

bool wildcardMatch(const char *str, const char *strWild) // Funcao simple wildcard do Anexo C
{
	while (*strWild)
	{
		if (*strWild == '?')
		{
			if (!*str)
				return false;
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			if (wildcardMatch(str, strWild + 1))
				return true;
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			return false;
		}
		else
		{
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	return !*str && !*strWild;
}