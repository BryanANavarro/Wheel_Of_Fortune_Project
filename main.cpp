// Bryan Navarro
// September 9, 2022
// Exam 1 - The Wheel of Fortune

#include <iostream>
#include "input.h"
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

/*
* PROTOTYPES
*/

int menuOption();
void newGame();
void updateFile();
void updateFile();
int gameMenu(int);
bool isVowel(char);
bool isConsonant(char);
void checkLetter(char*, char*, int, char);
int validateUse(char*, char, int);
void buyVowel(char[], double&, char*, char*, char*, int);
void displayLetter(char* array, int size, char ch);
void spinWheel(char [], double&, char* , char* , char* , int );
void solvePuzzle(char[], char*, double&, int, int, int, int, int, int, int, int);



int main()
{
	do
	{
		switch (menuOption())
		{
		case 1: newGame(); break;
		case 2: updateFile(); break;
		case 0: exit(1); break;
		default: cout << "\n\nERROR - Invalid option. Please re-enter."; break;
		}
		cout << "\n";
		system("cls");

	} while (true);

}

// This functions creates the main menu and returns input of the user for an option
int menuOption()
{
	system("cls");
	cout << "\nA contestant spins the wheel to determine a dollar value and guess a consonant.";
	cout << "\nLanding on a dollar amount and calling a correct letter results in revealing every";
	cout << "\ninstance of that letter; it also awards the value of the spin multiplied by the";
	cout << "\nnnumber of times that the letter appears in the puzzle.Doing so also allows the";
	cout << "\ncontestant to spin again, buy a vowel for a flat rate of $250, or attempt to solve";
	cout << "\nthe puzzle.If a spin lands on(BANKRUPT) wedge, all earned winning will be lost.";
	
	cout << "\t\t\n\nCMPR121 - Exam#1: Wheel of Fortune by Bryan Navarro (September 9, 2022)";
	
	cout << "\t\t\n1. Start a new game";
	cout << "\t\t\n2. Create/Update data text file";
	cout << "\t\t\n0. Exit game";

	return inputInteger("\nOption: ", 0, 2);
    
}

// This function reads in an existing file or creates a file to be read in order to obtain the phrase for the game
void updateFile()
{
	system("cls");
	
	char phrase[80] = "unknown";
	char file[80] = "unknown";
	
	strcpy_s(file, inputString("\t\nEnter the input text file name to randomly retrieve a puzzle phrase: ", true).c_str());

	fstream inputFile;
	inputFile.open(file);

	if (inputFile.fail())
	{
		cout << "\nERROR: Cannot open the file, " << file << ".";
		char choice = inputChar("\nDo you want to create (Y-yes or N-no) the file?", 'Y', 'N');
		if (choice == 'Y')
		{
			fstream newFile(file, ios::out | ios::app);
			cout << "\n" << file << ".txt file was created.";
			strcpy_s(phrase, inputString("\nEnter a new phrase to be added to the file: ", true).c_str());

			for (int i = 0; i < strlen(phrase); i++)
			{
				newFile << phrase[i];
			}
			newFile << "\n";
			newFile.close();
		}
		else if (choice == 'N')
			return;
	}
	else if (file)
	{
		fstream inputFile(file, ios::app | ios::in | ios::out);
		strcpy_s(phrase, inputString("\nEnter a new phrase to be added to the file: ", true).c_str());
		for (int i = 0; i < strlen(phrase); i++)
		{
			inputFile << phrase[i];
		}
		inputFile << "\n";
		cout << "\n" << file << " has been updated\n";
		inputFile.close();
		system("pause");
	}
}

// displays the menu and returns the player's choice 
int gameMenu(int choice)
{
	cout << "\n1. Spin the wheel and call a consonant";
	cout << "\n2. Buy a vowel";
	cout << "\n3. Solve the puzzle";
	cout << "\n0. Quit and return to the main menu";

	return choice = inputInteger("\n\nOption: ", 0, 4);
}

// checks for repeating letters
int validateUse(char* alpha, char ch, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (ch == alpha[i])
		{
			return i;
		}
	}
	return -1;

}

//Determines whether or not the char is a vowel
bool isVowel(char c)
{
	if (toupper((c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')))
		return true;
	else
		return false;
		
}
// determines whether or not the char is a consonannt
bool isConsonant(char c)
{
	if (toupper((c != 'A' || c != 'E' || c != 'I' || c != 'O' || c != 'U')))
		return true;
	else
		return false;
}

// Allows the user to buy a vowel and passes through the puzzle, hidden puzzle and jackpot
void buyVowel(char name[], double &jackPot, char* puzzle, char* hidden, char * alpha, int size)
{	
	if (jackPot <= 250)
	{
		cout << "\nHost: Sorry " << name << ". You don't have enough money to buy a vowel. Please get some money by spinning the wheel and select a consonant.\n\n";
		system("pause");
	}
	else if (jackPot >= 250)
	{
		cout << "\nVowels will cost $250 each.\nWhat vowel letter do you want to buy?";
		
		char ch = inputChar("\nI'd like to buy an ");
		if (!isVowel(ch))
		{
			cout << "\nHost you must used the 'AEIOU' characters";
			system("pause");
			return;
		}
			
		int vowelIndex = validateUse(alpha, ch, size);
		if (vowelIndex == -1)
		{
			cout << "\nHost: Sorry. You have already chosen the letter " << ch << ".\n\n";
			system("pause");
			return;
		}

		jackPot = jackPot - 250;
		int count = 0;

		for (int i = 0; i < strlen(puzzle); i++){
			if (puzzle[i] == ch)
			{
				count++;
				hidden[i] = ch;
			}
		}
		
		if (count == 0)
		{
			cout << "\nHost: Sorry, there were no matches.\n\n";
			checkLetter(alpha, hidden, size, ch);
			system("pause");
			return;
		}
		
		cout << "\nHost: Yes! There is(are) " << count << " '" << ch << "' in the puzzle.\n";
		checkLetter(alpha, hidden, size, ch);
		system("pause");
	}
}

// checks which letters are still avaiable
void checkLetter(char* array, char *hidden, int size, char guessCh)
{
	for (int i = 0; i < size; i++)
	{
		if (guessCh == array[i])
			array[i] = '\0';
	}
}

void displayLetter(char* array, int size, char ch)
{
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
}

// This function spins the wheel and assigns the jackpot, and determines the guess from the user
void spinWheel(char name[], double &jackpot, char *puzzle, char* hidden, char * alpha, int size)
{
	char guess = 0;
	int wheel[24] = { 0, 150, 150, 300, 300, 500, 500 , 0, 750, 750, 1000, 2500, 2500, 1000, 200, 200, 400, 400, 1500, 1500, 1200, 1200, 1350};
	int index = rand() % 24;
	char vowels[] = { 'A', 'E','I','O','U' };
	
	if (wheel[index] == 0)
	{
		cout << "\nUnfortunately the wheel spun and stopped at BANKRUPT.";
		cout << "\nTherefore, you have lost all current amount.\n";
		jackpot = 0;
		system("pause");
		return;
	}
	
	cout << "\nHost: The wheel spun and stopped. Consonants are now worth $" << wheel[index] << " each.";
	guess = inputChar("\nWhat consonant letter do you want to choose?\n");
	char ch = toupper(guess);
	
	int consonantIndex = validateUse(alpha, ch, size);
	if (consonantIndex == -1)
	{
		cout << "\nHost: Sorry. You have already chosen the letter " << ch << ".\n\n";
		system("pause");
		return;
	}
	
	if (isdigit(ch) && !isalpha(ch))
	{
		cout << "\nERROR: Invalid input. Must be one of the 'BCDFGHJKLMNPQRSTVWXYZ' characters.\n";
		system("pause");
		return;
	}
	
	
	for (int i = 0; i < sizeof(vowels); i++)
	{
		if (vowels[i] == ch)
		{
			cout << "\nERROR: Invalid input. Must be one of the 'BCDFGHJKLMNPQRSTVWXYZ' characters.";
			cout << "\nPlease get some money by spinning the wheel and selecting a consonant.\n";
			system("pause");
			return;
		}	
	}

	int count = 0;
	for (int j = 0; j < strlen(puzzle); j++)
	{
		if (ch == puzzle[j])
		{
			count++;
			hidden[j] = ch;
		}
	}
	if (count == 0)
	{
		cout << "\nHost: Sorry, there were no matches.\n\n";
		checkLetter(alpha, hidden, size, ch);
		system("pause");
		return;
	}
	cout << "\nHost: Yes! There is(are) " << count << " '" << ch << "' in the puzzle.\n";
	jackpot = jackpot + (wheel[index] * count);
	
	checkLetter(alpha, hidden, size, ch);
	system("pause");
}

// the user tries to solve the puzzle
void solvePuzzle(char name[], char* puzzle, double &jackPot, int  words, int letters, int vowels, int spaces, int consonants, int digits, int puncts, int others)
{	
	char temp[80];
	
	cout << "\nHost: Ok " << name << ".";
	strcpy_s(temp, inputString("\nTo win the jackpot, please solve the puzzle by correctly entering your answer.\n", true).c_str());

	for (int i = 0; i < strlen(temp); i++)
		temp[i] = toupper(temp[i]);

	if (strcmp(temp, puzzle) == 0)
	{
		cout << "\nThe answer is: " << puzzle << "\n";
		cout << "\nHost: Congratulations " << name << "! \nYou have solved the puzzle and won $" << jackPot << ".";
		cout << "\nYou will also take with you some statistics of the puzzle:\n";
		cout << "\n1. Number of word(s): " << words;
		cout << "\n2. Number of letter(s): " << letters;
		cout << "\n3. Number of vowel(s): " << vowels;
		cout << "\n4. Number of space(s): " << spaces;
		cout << "\n5. Number of consonant(s): " << consonants;
		cout << "\n6. Number of punctuation(s): " << puncts;
		cout << "\n7. Number of digit(s): " << digits;
		cout << "\n8. Number of other(s): " << others;

		cout << '\n';
		system("pause");
		return;
	}
	else
	{
		cout << "\nHost: Sorry, your answer is incorrect. Please try again.\n\n";
		system("pause");
		return;
	}
}
// Starts the new game
void newGame()
{
	srand(time(0)); // Random everytime
	int size = 26;
	char alpha[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	char consonants[] = { 'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z' };
	char vowels[] = { 'A', 'E','I','O', 'U' };
	
	char* choices = new char[size];
	char* modified = new char[size];
	char guess = 0;
	choices = alpha;

	char gameFile[80] = "unknown";
	char name[80] = "unknown";
	char puzzle[80] = "unknown";
	
	int gameChoice = 0;
	double jackPot = 0.0;
	
	int numWords = 1;
	int numLetters = 0;
	int numVowels = 0;
	int numSpaces = 0;
	int numConsonants = 0;
	int digits = 0;
	int puncts = 0;
	int others = 0;

	string line;
	vector <string> lines;
	int totalLines = 0;
	
	strcpy_s(gameFile, inputString("\t\nEnter the input text file name to randomly retrieve a puzzle phrase: ", true).c_str());
	
	fstream file(gameFile, ios::in);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			lines.push_back(line);
		}
		string temp = (lines[rand() % lines.size()]);
		
		for (int i = 0; i < temp.length(); i++)
		{
			temp[i] = toupper(temp[i]);
			if (isalpha(temp[i]))
				numLetters++;
			if (isalpha(temp[i]) && isVowel(temp[i]))
				numVowels++;
			if (isspace(temp[i]))
			{
				numWords++;
				numSpaces++;
			}
			if (isConsonant(temp[i]))
				numConsonants++;
			if (ispunct(temp[i]))
				puncts++;
			if (isdigit(temp[i]))
				digits++;
			else
				others++;
		}
		
		strcpy_s(puzzle, temp.c_str());
		char hiddenPuzzle[80];
		
		strcpy_s(hiddenPuzzle, puzzle); // transform the phrase into *** 
		for (int i = 0; i < strlen(hiddenPuzzle); i++)
		{
			if (isalpha(hiddenPuzzle[i]))
				hiddenPuzzle[i] = '*';
		}
		
		strcpy_s(name, inputString("\nHost: Hello contestant! Pleast state your name.\nContestant: Hi! My name is...", true).c_str());
		cout << "\nHost: Welcome " << name << ". Let's play!\n";
		system("pause");
		system("cls");

		do
		{
			system("cls");
			cout << "\nJackpot: $" << jackPot << "\n";
			cout << "\nPuzzle: " << hiddenPuzzle << "\n"; 
			cout << "\nHint: " << numWords << " word(s) with " << numLetters << " letter(s)\n";
			cout << "\nAvailable letter(s): ";
			displayLetter(choices, size, guess);
			cout << "\n" << name << ", your options are: \n"; 
			
			switch (gameMenu(gameChoice))
			{
			case 0: return; break;
			case 1: spinWheel(name, jackPot, puzzle, hiddenPuzzle, alpha, size); break;
			case 2: buyVowel(name, jackPot, puzzle, hiddenPuzzle, alpha, size); break;
			case 3: solvePuzzle(name, puzzle, jackPot, numWords, numLetters, numVowels, numSpaces, numConsonants, digits, puncts, others); return;
			}
			
		} while (true);
		file.close();
	}

	else if (file.fail())
	{
		cout << "\nThe file does not exist";
		cout << "\nPlease choose an existing text file or option 2 to create a new data text file.\n";
	}
	system("pause");
}