#include <iostream>
using namespace std;

enum enGameChoice {Paper = 1, Stone = 2, Scissor = 3};

enum enWinner {Player = 1 , Computer = 2 , Draw = 3};

struct stRound {
	short RoundNumber = 0;
	enGameChoice playerChoice;
	enGameChoice ComputerChoice;
	enWinner winner;
	string winnerName = "";
};

struct stGame {
	short RoundsPlayed = 0;
	short PlayerWins = 0;
	short ComputerWins = 0;
	short Draw = 0;
	enWinner WinnerGame;
	string WinnerName;
};

short RandomNumber(short From , short To) {
	short Number = rand() % (To - From + 1) + From;
	return Number;
}

enGameChoice PlayerChoice() {
	int number = 0;
	do {
		cout << "Choose Your One [1] Paper , [2] Stone , [3] Scissor   ";
		cin >> number;
	} while (number < 1 || number > 3);
	return (enGameChoice)number;
}

enGameChoice ComputerChoice() {
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWinTheRound(stRound RoundInfo) {
	if (RoundInfo.playerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;


	switch (RoundInfo.playerChoice) {

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor) 
			return enWinner::Computer;
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
		break;
		
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
		break;
	}

	return enWinner::Player;
}

string WinnerName(enWinner Winner) {
	string name[3] = { "Player" , "Computer" , "Draw" };
	return name[Winner - 1];
}

string GameChoice(enGameChoice Choice) {
	string choice[3] = { "Paper" , "Stone" , "Scissor" };
	return choice[Choice - 1];
}

short HowManyRounds() {
	short Number = 0;

	do {
		cout << "How Many Round 1 To 10 : ";
		cin >> Number;

	} while (Number < 1 || Number > 10);

	return Number;

}

void ChangeScreenColor(enWinner winner) {
	switch (winner) {
	case enWinner::Player:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}


}

void PrintRoundInfo(stRound RoundInfo) {
	cout << "________________________Round [" << RoundInfo.RoundNumber << "] ________________________\n";
	cout << "Player Choice           : " << GameChoice(RoundInfo.playerChoice) << endl;
	cout << "Computer Choice         : " << GameChoice(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner            : " << WinnerName(RoundInfo.winner) << endl << endl;
	cout << "__________________________________________________________________________________________\n\n";
	ChangeScreenColor(RoundInfo.winner);
}

string Taps(int Number) {
	string taps = "";

	for (int i = 1; i <= Number; i++) {
		taps += "\t";
	}

	return taps;
}

void PrintGameInfo(stGame GameInfo) {
	cout << Taps(2) << "___________________________[Game Results]___________________________\n";
	cout << Taps(2) << "Rounds Played		 : " << GameInfo.RoundsPlayed << endl;
	cout << Taps(2) << "Player Wins Times        : " << GameInfo.PlayerWins << endl;
	cout << Taps(2) << "Computer Wins Times      : " << GameInfo.ComputerWins << endl;
	cout << Taps(2) << "Draw Times	    	 : " << GameInfo.Draw<< endl;
	cout << Taps(2) << "Final Winner		 : " << GameInfo.WinnerName << endl;
	ChangeScreenColor(GameInfo.WinnerGame);

}

enWinner WhoWinGame(short PlayerWins, short ComputerWins) {
	if (PlayerWins > ComputerWins)
		return enWinner::Player;
	else if (ComputerWins > PlayerWins)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGame FillGameResults(short RoundsPlayed, short PlayerWins, short ComputerWins, short Draw) {
	stGame GameInfo;

	GameInfo.RoundsPlayed = RoundsPlayed;
	GameInfo.PlayerWins = PlayerWins;
	GameInfo.ComputerWins = ComputerWins;
	GameInfo.Draw = Draw;
	GameInfo.WinnerGame = WhoWinGame(PlayerWins , ComputerWins);
	GameInfo.WinnerName = WinnerName(GameInfo.WinnerGame);

	return GameInfo;
}

stGame PlayGame(int HowManyRounds) {
	stRound RoundInfo;
	int PlayerWins = 0, ComputerWins = 0, Draw = 0;

	for (int i = 1; i <= HowManyRounds; i++) {

		cout << "Round [" << i << "] Begin\n";
		RoundInfo.RoundNumber = i;
		RoundInfo.playerChoice = PlayerChoice();
		RoundInfo.ComputerChoice = ComputerChoice();
		RoundInfo.winner = WhoWinTheRound(RoundInfo);
		RoundInfo.winnerName = WinnerName(RoundInfo.winner);

		if (RoundInfo.winner == enWinner::Player)
			PlayerWins++;
		else if (RoundInfo.winner == enWinner::Computer)
			ComputerWins++;
		else
			Draw++;

		PrintRoundInfo(RoundInfo);
	}

	return FillGameResults(HowManyRounds, PlayerWins, ComputerWins, Draw);
}

void ShowGameOverScreen() {
	cout << Taps(2) << "_____________________________________________________________________\n\n";
	cout << Taps(4) << "           G A M E  O V E R\n";
	cout << Taps(2) << "_____________________________________________________________________\n";
}

void ResetScreen() {
	system("cls");
		system("color 0F");

}


void StartGame() {
	char Start = 'Y';

	do {
		ResetScreen();
		stGame GameInfo = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		PrintGameInfo(GameInfo);

		cout << "\nDo You Want Play Again Y / N  ";
		cin >> Start;
	} while (Start == 'Y' || Start == 'y');




}


int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
