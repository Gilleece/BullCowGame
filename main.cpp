/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>	
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
		std::cout << "	                                 .a@@@@@a.     ,a@@@@@@@@a,     .a@@@@@a. \n";
		std::cout << "                              .@@@@@@@@@@@a,a@@@@@@@@@@@@@@a,a@@@@@@@@@@@. \n";
		std::cout << "                              @@@@@@@@@@@@a@@@@@@@@@@@@@@@@@@a@@@@@@@@@@@@ \n";
		std::cout << "                               @@@@'    `@a@@@@@@@@@@@@@@@@@@@@a@'   `@@@@ \n";
		std::cout << "                               `@'        @@@@@@@@@@@@@@@@@@@@@@       `@' \n";
		std::cout << "              .########################## @@@@@@@@@a@@@a@@@@@@@@ \n";
		std::cout << "           .##############################`@@@@@@@@a@@@a@@@@@@@' \n";
		std::cout << "         .#####################;;#########,@@@@@@@@@@@@@@@@@@@@, \n";
		std::cout << "       ,;;;;;######;;;;#####;;;;;;;##;;;,@@@@@@@@@@@@@@@@@@@@@@@@, \n";
		std::cout << "     ,;;;;;;;;;;;;;;;;;;###;;;;;;;;;;;;;@@@@@( )@@@@@@@@@@( )@@@@@ \n";
		std::cout << "    ;;';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;`@@@@@@@@@@@@@@@@@@@@@@@@' \n";
		std::cout << "   ;;';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;`@@@@@@@@@@@@@@@@@@@@', \n";
		std::cout << "  ;;' ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; """""""""""""",;;  ', \n";
		std::cout << " ;;'  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;    ',         <-- ...It's a cow. Okay? No idea why it has wheels.\n";
		std::cout << ";;;;  ###;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;####;;;;;;;;;;;;;;      ; \n";
		std::cout << "`;;'  ####;;;##;;;;;;;;;;;;;;;;;;;;;;;;;;###########;;;;;;;;;;;    ,' \n";
		std::cout << "  `   ##########;;;;;;;'''''''''''''''''''''''''''###;;;;;;;;;;    ; \n";
		std::cout << "      #############;;'                            #;;;;;;;;;;;;     `, \n";
		std::cout << "      #############                               ;;;;;;;;;;;;;     () \n";
		std::cout << "      #############                               ;;;;;;;;;;;;; \n";
		std::cout << "      #oOOOOOOOOOo#                               ;oOOOOOOOOOo; \n";
		std::cout << "    oOOOOOOOOOOOOOOOo                           oOOOOOOOOOOOOOOOo \n";
		std::cout << "   OOOOOOOOOOOOOOOOOOO                         OOOOOOOOOOOOOOOOOOO \n";
		std::cout << "   OOOOOOO () OOOOOOOO                         OOOOOOOO () OOOOOOO \n";
		std::cout << "   `OOOOOOOooOOOOOOOO'                         `OOOOOOOOooOOOOOOO' \n";
		std::cout << "     `OOOOOOOOOOOOO'                             `OOOOOOOOOOOOO' \n";
		std::cout << "        """""""""                                   """""""""\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	std::cout << "(Bulls are letters in their correct position. \nCows are letters that are in the word but not in the right place.)\n\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game is NOT won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO summarise game
	PrintGameSummary();
	return;
}

// loop continually until user gives valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Whoops, you moron! That's not an isogram! Haha, you IDIOT. \n Remember, an isogram is a word with no repeated letters. \n For example: 'idiot' is not an isogram because it has two instances of the letter i. \nBut you wouldn't know that because you are STUPID (which is an example of an isogram, good job!)\n\nPlease enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "FFS. ONLY LOWER CASE LETTERS. COME ON. \nPlease enter a " << BCGame.GetHiddenWordLength() << " letter word IN LOWER CASE ONLY.\n";
			break;
		default: 
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with a new word(y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations, you won!\n\n";
	}
	else
	{
		std::cout << "You ran out of tries. :( \n\n Give it another shot!! HAHA!!! TALLY-HO!\n\n";
	}
}