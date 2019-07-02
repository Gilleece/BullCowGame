#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map


using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
FBullCowCount BullCowCount;

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 	
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	TMap<int32, FString> WordList{ {1,"cat"}, {2,"log"}, {3,"fair"}, {4,"pear"}, {5,"rope"}, {6,"walk"}, {7,"begin"}, {8,"brown"}, {9,"fringe"}, {10,"master"}, {11,"planets"}, {12,"machine"}, };
	CurrentWordNumber++;

	if (CurrentWordNumber == 13) //lets the game loop infinitely
	{
		CurrentWordNumber = 1;
	}

	const FString HIDDEN_WORD = WordList[CurrentWordNumber];
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))	//if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //map setup
	for (auto Letter : word) //for all letters of the word
	{
		Letter = tolower(Letter); // changes to lowercase
		if (LetterSeen[Letter])	{return false;}
		else {LetterSeen[Letter] = true;}
	}


	return true;
}

bool FBullCowGame::IsLowerCase(FString word) const
{
	FString lowercaseletters = "abcdefghijklmnopqrstuvwxyz";

	for (int32 i = -1; i < word.length(); i++)
	{
		if (!lowercaseletters.find(word[i]))
		{
			return false;
		}
	}


	return true;
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	// loop through all letters in the hidden word

	for (int32 MHWCHAR = 0; MHWCHAR < WordLength; MHWCHAR++) {
		// compare letters against the guess
		for (int32 GCHAR = 0; GCHAR < WordLength; GCHAR++) {
			// if they match then
			if (Guess[GCHAR] == MyHiddenWord[MHWCHAR]) {
				if (MHWCHAR == GCHAR) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}